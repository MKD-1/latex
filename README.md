# ACM LaTeX Template

This repository is a LaTeX learning workspace and ACM template source
repository. It is designed for maintaining algorithm notes and C++ templates as
source files, then compiling them into a compact PDF.

## Build

Recommended compiler:

```powershell
xelatex main.tex
```

For repeated builds, install and use `latexmk`:

```powershell
latexmk -xelatex main.tex
```

Generated PDFs and LaTeX build artifacts are ignored by Git.

## Repository Layout

```text
main.tex              Root LaTeX entry point
styles/acm.sty        Shared compact ACM template style
sections/             Algorithm category chapters
code/                 Standalone C++ template source files
```

## Add A New Template

1. Add the C++ source file under `code/`.
2. Add or update the matching chapter file under `sections/`.
3. Use `\AlgorithmEntry{...}` for the algorithm block.
4. Use `\lstinputlisting{code/name.cpp}` to include source code.
5. Compile with `xelatex main.tex`.

## Two-Week Learning Plan

### Week 1: Minimum Working ACM Template

- Day 1: Learn the LaTeX workflow and compile `main.tex`.
- Day 2: Map Markdown concepts to LaTeX: headings, lists, emphasis, links.
- Day 3: Practice inline, display, and aligned math formulas.
- Day 4: Learn `listings` and configure C++ code display.
- Day 5: Split content with `\input{}` into `sections/`.
- Day 6: Add table of contents, labels, and references.
- Day 7: Finish a small template with graph, math, and string sections.

### Week 2: Maintainable Source Repository

- Day 8: Keep one category per section file and one algorithm per source file.
- Day 9: Use small custom commands to reduce repeated markup.
- Day 10: Tune compact layout with margins, spacing, and code style.
- Day 11: Use `xelatex` for Chinese and English mixed content.
- Day 12: Include standalone C++ files with `\lstinputlisting`.
- Day 13: Commit each new algorithm as source plus section update.
- Day 14: Review the full template and document the build workflow.
