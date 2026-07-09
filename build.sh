#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

if command -v cygpath >/dev/null 2>&1; then
	export PATH="/usr/bin:$PATH"
fi

LATEX="${LATEX:-xelatex}"
LATEXCMD="$LATEX -shell-escape -output-directory build/"
LECTUREFLAGS=""
LATEXMAIN="./content/kactl.tex"
if command -v cygpath >/dev/null 2>&1 && "$LATEX" --version 2>/dev/null | head -n 1 | grep -q "TeX Live"; then
	TEX_ROOT="$(cygpath -w "$PWD")"
	export TEXINPUTS="${TEX_ROOT};${TEX_ROOT}\\content\\tex\\;"
else
	export TEXINPUTS=".:content/tex/:"
fi
export max_print_line=1048576
export PYTHONUTF8=1
export LC_ALL=C.UTF-8
export LANG=C.UTF-8

cmd="${1:-help}"
if [ "$#" -gt 0 ]; then
	shift
fi

while [ "$#" -gt 0 ]; do
	case "$1" in
		--no-notes)
			LECTUREFLAGS="-jobname=kactl"
			LATEXMAIN='\def\hidelectures{}\input{./content/kactl.tex}'
			shift
			;;
		--semantic-highlight)
			# Semantic highlighting is opt-in so default builds do not depend on clangd.
			export KACTL_SEMANTIC_HIGHLIGHT=1
			shift
			;;
		--no-semantic-highlight)
			unset KACTL_SEMANTIC_HIGHLIGHT
			shift
			;;
		--clangd)
			if [ "$#" -lt 2 ]; then
				echo "Missing path after --clangd"
				exit 1
			fi
			export KACTL_CLANGD="$2"
			shift 2
			;;
		*)
			echo "Unknown option: $1"
			echo "Run 'bash build.sh help' for available commands."
			exit 1
			;;
	esac
done

needs_rebuild() {
	local target="$1"
	shift
	if [ ! -e "$target" ]; then
		return 0
	fi
	local dep
	for dep in "$@"; do
		if [ "$dep" -nt "$target" ]; then
			return 0
		fi
	done
	return 1
}

build_test_session_pdf() {
	mkdir -p build/
	$LATEXCMD ./content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf
}

clean_build() {
	cd build && rm -f kactl.aux kactl.log kactl.tmp kactl.toc kactl.pdf kactl.ptc
}

case "$cmd" in
	help)
		echo "This script builds KACTL (KTH Algorithm Competition Template Library)"
		echo ""
		echo "Available commands are:"
		echo "	bash build.sh fast		- to build KACTL, quickly (only runs LaTeX once)"
		echo "	bash build.sh fast --no-notes	- to build KACTL without lecture notes"
		echo "	bash build.sh fast --semantic-highlight --clangd PATH"
		echo "					- to build KACTL with clangd semantic highlighting"
		echo "	bash build.sh kactl		- to build KACTL"
		echo "	bash build.sh kactl --no-notes	- to build KACTL without lecture notes"
		echo "	bash build.sh kactl --semantic-highlight --clangd PATH"
		echo "					- to fully build KACTL with clangd semantic highlighting"
		echo "	bash build.sh clean		- to clean up the build process"
		echo "	bash build.sh veryclean		- to clean up and remove kactl.pdf"
		echo "	bash build.sh test		- to run all the stress tests in stress-tests/"
		echo "	bash build.sh test-compiles	- to test compiling all headers"
		echo "	bash build.sh help		- to show this information"
		echo "	bash build.sh showexcluded	- to show files that are not included in the doc"
		echo ""
		echo "For more information see the file 'doc/README'"
		;;

	fast)
		mkdir -p build/
		$LATEXCMD $LECTUREFLAGS "$LATEXMAIN" </dev/null
		cp build/kactl.pdf kactl.pdf
		;;

	kactl)
		mkdir -p build/
		if needs_rebuild test-session.pdf content/test-session/test-session.tex content/test-session/chapter.tex; then
			build_test_session_pdf
		fi
		$LATEXCMD $LECTUREFLAGS "$LATEXMAIN" && $LATEXCMD $LECTUREFLAGS "$LATEXMAIN"
		cp build/kactl.pdf kactl.pdf
		;;

	clean)
		clean_build
		;;

	veryclean)
		clean_build
		rm -f kactl.pdf test-session.pdf
		;;

	test-session.pdf)
		mkdir -p build/
		if needs_rebuild test-session.pdf content/test-session/test-session.tex content/test-session/chapter.tex; then
			build_test_session_pdf
		fi
		;;

	test)
		./doc/scripts/run-all.sh .
		;;

	test-compiles)
		./doc/scripts/compile-all.sh .
		;;

	showexcluded)
		mkdir -p build/
		grep -RoPh '^\s*\\kactlimport{\K.*' content/ | sed 's/.$//' > build/headers_included
		find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included
		;;

	*)
		echo "Unknown command: $cmd"
		echo "Run 'bash build.sh help' for available commands."
		exit 1
		;;
esac
