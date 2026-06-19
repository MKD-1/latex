#!/usr/bin/env bash
set -u
cd "$(dirname "$0")"
g++ gen.cpp -o gen -std=c++17 -O2
g++ std.cpp -o std -std=c++17 -O2
g++ sol.cpp -o sol -std=c++17 -O2
cnt=0
while true; do
	cnt=$((cnt + 1))
	echo "Testing case #$cnt"
	./gen "${1-}" > in.txt
	./std < in.txt > out1.txt
	./sol < in.txt > out2.txt
	if ! diff -q out1.txt out2.txt > /dev/null; then
		echo "WA on case #$cnt"
		diff out1.txt out2.txt
		read -r -p "Press Enter to continue..."
	fi
done
