#!/usr/bin/env python3
# encoding: utf-8

# Semantic token support for KACTL listings.
# License: CC0

import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import time


TOKEN_MACROS = {
    "namespace": "kactlTokNamespace",
    "type": "kactlTokType",
    "class": "kactlTokStruct",
    "enum": "kactlTokType",
    "interface": "kactlTokType",
    "struct": "kactlTokStruct",
    "typeParameter": "kactlTokType",
    "parameter": "kactlTokParameter",
    "variable": "kactlTokLocal",
    "property": "kactlTokField",
    "enumMember": "kactlTokField",
    "function": "kactlTokFunction",
    "method": "kactlTokFunction",
    "macro": "kactlTokMacro",
    "keyword": "kactlTokKeyword",
}

SKIPPED_TOKEN_TYPES = {
    "comment",
    "string",
    "number",
    "operator",
    "regexp",
    "decorator",
    "modifier",
}

CXX_SEMANTIC_PRELUDE = """\
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
#define rep(i,a,b) for (int i = (a); i < (b); ++i)
#define per(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define trav(a,x) for (auto& a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)(x).size()
"""


class SemanticHighlightError(Exception):
    pass


def _path_to_uri(path):
    return Path(path).resolve().as_uri()


def _default_clangd_path():
    env_path = os.environ.get("KACTL_CLANGD")
    if env_path:
        return env_path
    bundled = Path(r"D:\software\LLVM\bin\clangd.exe")
    if bundled.exists():
        return str(bundled)
    return "clangd"


def _repo_root():
    return Path(__file__).resolve().parents[2]


def _default_compile_flags(source_path):
    root = _repo_root()
    source_dir = Path(source_path).resolve().parent
    return [
        "-std=c++17",
        "-xc++",
        "-I" + str(root),
        "-I" + str(root / "content" / "contest"),
        "-I" + str(source_dir),
    ]


# Add KACTL's common aliases and short macros only to clangd's temporary input.
def _analysis_prelude(language):
    if language in ["C++", "cpp", "rawcpp"]:
        return CXX_SEMANTIC_PRELUDE
    return ""


# Generate a temporary translation unit without modifying the original source.
def build_translation_unit(source_path, source_text, language="C++"):
    root = _repo_root()
    cache_dir = root / "build" / "semantic-cache"
    cache_dir.mkdir(parents=True, exist_ok=True)
    stem = Path(source_path or "stdin").stem or "snippet"
    digest = hashlib.sha256((str(source_path) + "\0" + source_text).encode("utf-8")).hexdigest()[:16]
    suffix = ".cpp" if language in ["C++", "cpp", "rawcpp"] else ".txt"
    temp_path = cache_dir / ("%s-%s%s" % (stem, digest, suffix))
    prelude = _analysis_prelude(language)
    analysis_text = prelude + source_text
    line_offset = len(prelude.splitlines())
    temp_path.write_text(analysis_text, encoding="utf-8", newline="\n")
    return temp_path, analysis_text, line_offset


class LspClient:
    def __init__(self, argv, timeout=20):
        self.proc = subprocess.Popen(
            argv,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        self.next_id = 1
        self.timeout = timeout

    def close(self):
        if self.proc.poll() is None:
            try:
                self.proc.kill()
            except OSError:
                pass

    def _send_payload(self, payload):
        body = json.dumps(payload, separators=(",", ":")).encode("utf-8")
        header = ("Content-Length: %d\r\n\r\n" % len(body)).encode("ascii")
        self.proc.stdin.write(header + body)
        self.proc.stdin.flush()

    def request(self, method, params=None):
        request_id = self.next_id
        self.next_id += 1
        payload = {
            "jsonrpc": "2.0",
            "id": request_id,
            "method": method,
            "params": params or {},
        }
        self._send_payload(payload)
        return request_id

    def notify(self, method, params=None):
        self._send_payload({
            "jsonrpc": "2.0",
            "method": method,
            "params": params or {},
        })

    def respond(self, request_id, result=None):
        self._send_payload({
            "jsonrpc": "2.0",
            "id": request_id,
            "result": result,
        })

    def read_message(self):
        headers = {}
        while True:
            line = self.proc.stdout.readline()
            if not line:
                raise SemanticHighlightError("clangd exited before sending a response")
            line = line.strip()
            if not line:
                break
            key, _, value = line.decode("ascii", errors="replace").partition(":")
            headers[key.lower()] = value.strip()
        length = int(headers.get("content-length", "0"))
        if length <= 0:
            raise SemanticHighlightError("invalid LSP content length")
        body = self.proc.stdout.read(length)
        return json.loads(body.decode("utf-8"))

    def wait_for(self, request_id):
        deadline = time.monotonic() + self.timeout
        while time.monotonic() < deadline:
            message = self.read_message()
            if message.get("id") == request_id:
                if "error" in message:
                    raise SemanticHighlightError(str(message["error"]))
                return message.get("result")
            if "id" in message and "method" in message:
                self.respond(message["id"], None)
        raise SemanticHighlightError("timed out waiting for clangd response")


def _utf16_col_to_index(text, utf16_col):
    if utf16_col <= 0:
        return 0
    units = 0
    for index, char in enumerate(text):
        units += 2 if ord(char) > 0xFFFF else 1
        if units >= utf16_col:
            return index + 1
    return len(text)


def _span_from_utf16(line_text, start_col, length):
    start = _utf16_col_to_index(line_text, start_col)
    end = _utf16_col_to_index(line_text, start_col + length)
    return start, end


def _decode_modifier_bits(bits, token_modifiers):
    return [name for index, name in enumerate(token_modifiers) if bits & (1 << index)]


def _macro_for_token(kind, modifiers):
    if kind in SKIPPED_TOKEN_TYPES:
        return None
    if kind == "variable" and "parameter" in modifiers:
        return "kactlTokParameter"
    if kind == "variable" and "static" in modifiers:
        return "kactlTokVariable"
    return TOKEN_MACROS.get(kind)


# Normalize clangd's delta-encoded UTF-16 tokens to source line/column ranges.
def normalize_tokens(raw_tokens, legend, source_text, line_offset=0):
    token_types = legend.get("tokenTypes", [])
    token_modifiers = legend.get("tokenModifiers", [])
    lines = source_text.splitlines()
    decoded = []
    line = 0
    col = 0
    data = raw_tokens.get("data", [])
    for i in range(0, len(data), 5):
        delta_line, delta_start, length, token_type, modifier_bits = data[i:i + 5]
        line += delta_line
        col = col + delta_start if delta_line == 0 else delta_start
        source_line = line - line_offset
        if line < 0 or line >= len(lines) or source_line < 0 or token_type >= len(token_types):
            continue
        start, end = _span_from_utf16(lines[line], col, length)
        if start >= end:
            continue
        kind = token_types[token_type]
        modifiers = _decode_modifier_bits(modifier_bits, token_modifiers)
        macro = _macro_for_token(kind, modifiers)
        text = lines[line][start:end]
        if not macro or not text or "\n" in text or "\r" in text:
            continue
        decoded.append({
            "line": source_line,
            "start": start,
            "end": end,
            "kind": kind,
            "modifiers": modifiers,
            "macro": macro,
            "text": text,
        })
    return decoded


# Ask clangd for semantic tokens while keeping semantic analysis separate from rendering.
def collect_semantic_tokens_with_clangd(temp_path, source_text, compile_flags=None, clangd_path=None, timeout=20, line_offset=0):
    clangd = clangd_path or _default_clangd_path()
    compile_flags = compile_flags or _default_compile_flags(temp_path)
    client = LspClient([clangd, "--background-index=false", "--log=error"], timeout=timeout)
    uri = _path_to_uri(temp_path)
    try:
        init_id = client.request("initialize", {
            "processId": os.getpid(),
            "rootUri": _path_to_uri(_repo_root()),
            "capabilities": {
                "textDocument": {
                    "semanticTokens": {
                        "dynamicRegistration": False,
                        "requests": {"range": False, "full": True},
                        "tokenTypes": list(TOKEN_MACROS.keys()),
                        "tokenModifiers": [],
                        "formats": ["relative"],
                        "overlappingTokenSupport": False,
                        "multilineTokenSupport": False,
                    }
                }
            },
            "initializationOptions": {
                "fallbackFlags": compile_flags,
            },
        })
        init_result = client.wait_for(init_id)
        legend = init_result.get("capabilities", {}).get("semanticTokensProvider", {}).get("legend")
        if not legend:
            raise SemanticHighlightError("clangd did not return a semantic token legend")
        client.notify("initialized", {})
        client.notify("textDocument/didOpen", {
            "textDocument": {
                "uri": uri,
                "languageId": "cpp",
                "version": 1,
                "text": source_text,
            }
        })
        token_id = client.request("textDocument/semanticTokens/full", {
            "textDocument": {"uri": uri}
        })
        raw_tokens = client.wait_for(token_id)
        shutdown_id = client.request("shutdown", {})
        try:
            client.wait_for(shutdown_id)
        except SemanticHighlightError:
            pass
        client.notify("exit", {})
        return normalize_tokens(raw_tokens or {}, legend, source_text, line_offset=line_offset)
    finally:
        client.close()


# Preserve lexical token priority so semantic coloring does not override comments or strings.
def merge_lexical_and_semantic_tokens(source_text, semantic_tokens):
    lines = source_text.splitlines()
    merged = {}
    for token in sorted(semantic_tokens, key=lambda t: (t["line"], t["start"], t["end"])):
        line_tokens = merged.setdefault(token["line"], [])
        if token["line"] >= len(lines):
            continue
        if any(not (token["end"] <= old["start"] or old["end"] <= token["start"]) for old in line_tokens):
            continue
        line_tokens.append(token)
    return merged


# Escape only macro arguments, leaving raw listing text untouched for stable layout.
def latex_escape_preserving_layout(text):
    replacements = {
        "\\": r"\textbackslash{}",
        "{": r"\{",
        "}": r"\}",
        "_": r"\_",
        "&": r"\&",
        "%": r"\%",
        "$": r"\$",
        "#": r"\#",
        "~": r"\textasciitilde{}",
        "^": r"\textasciicircum{}",
        "<": r"\ensuremath{<}",
        ">": r"\ensuremath{>}",
    }
    return "".join(replacements.get(char, char) for char in text)


def _caption_escape(text):
    return latex_escape_preserving_layout(text).replace("/", r"/")


# Render only the code block with semantic escape macros; surrounding text stays outside.
def render_semantic_listing(source_text, tokens, caption, language="C++"):
    token_map = merge_lexical_and_semantic_tokens(source_text, tokens)
    output = [
        r"\begin{lstlisting}[caption={%s}, language=%s, escapeinside={(*@}{@*)}]" % (
            _caption_escape(caption),
            language,
        )
    ]
    for line_no, line in enumerate(source_text.splitlines()):
        rendered = []
        pos = 0
        for token in token_map.get(line_no, []):
            if token["start"] < pos:
                continue
            rendered.append(line[pos:token["start"]])
            escaped = latex_escape_preserving_layout(line[token["start"]:token["end"]])
            rendered.append("(*@\\%s{%s}@*)" % (token["macro"], escaped))
            pos = token["end"]
        rendered.append(line[pos:])
        output.append("".join(rendered))
    output.append(r"\end{lstlisting}")
    return "\n".join(output)


# Fall back to current listings output so semantic failures never break PDF builds.
def fallback_to_listings(caption, source_text, language="C++", reason=None):
    if reason:
        print("semantic highlight fallback for %s: %s" % (caption, reason), file=sys.stderr)
    return "\n".join([
        r"\begin{lstlisting}[caption={%s}, language=%s]" % (_caption_escape(caption), language),
        source_text,
        r"\end{lstlisting}",
    ])


def try_render_semantic_listing(source_path, source_text, caption, language="C++", clangd_path=None):
    try:
        temp_path, analysis_text, line_offset = build_translation_unit(source_path or caption, source_text, language)
        tokens = collect_semantic_tokens_with_clangd(
            temp_path,
            analysis_text,
            compile_flags=_default_compile_flags(source_path or temp_path),
            clangd_path=clangd_path,
            line_offset=line_offset,
        )
        if not tokens:
            raise SemanticHighlightError("clangd returned no renderable semantic tokens")
        return render_semantic_listing(source_text, tokens, caption, language)
    except Exception as err:
        print("semantic highlight fallback for %s: %s" % (caption, err), file=sys.stderr)
        return None


def _dump_tokens(input_path, clangd_path=None):
    source_path = Path(input_path)
    source_text = source_path.read_text(encoding="utf-8")
    temp_path, analysis_text, line_offset = build_translation_unit(source_path, source_text, "C++")
    tokens = collect_semantic_tokens_with_clangd(
        temp_path,
        analysis_text,
        compile_flags=_default_compile_flags(source_path),
        clangd_path=clangd_path,
        line_offset=line_offset,
    )
    print(json.dumps(tokens, indent=2, ensure_ascii=False))


def main():
    parser = argparse.ArgumentParser(description="Generate KACTL semantic highlight tokens.")
    parser.add_argument("input", nargs="?", help="C++ source file to inspect")
    parser.add_argument("--dump-tokens", action="store_true", help="print semantic tokens as JSON")
    parser.add_argument("--clangd", help="path to clangd executable")
    args = parser.parse_args()
    if args.dump_tokens:
        if not args.input:
            parser.error("--dump-tokens requires an input file")
        _dump_tokens(args.input, args.clangd)
        return 0
    parser.error("no action requested")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
