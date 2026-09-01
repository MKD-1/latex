/**
 * Author: chilli
 * License: CC0
 * Source: Own work
 * enDescription: Read an integer from stdin. Usage requires your program to pipe in
 * input from file.
 * Description: 终极形态快读
 * Usage: ./a.out < input.txt
 * Time: About 5x as fast as cin/scanf.
 * Status: tested on SPOJ INTEST, unit tested
 */
#pragma once

inline char gc() { // like getchar()
	static char buf[1 << 16];
	static size_t bc, be;
	if (bc >= be) {
		buf[0] = 0, bc = 0;
		be = fread(buf, 1, sizeof(buf), stdin);
	}
	return buf[bc++]; // returns 0 on EOF
}

int readInt() {
	int a, c;
	while ((a = gc()) < 40);
	if (a == '-') return -readInt();
	while ((c = gc()) >= 48) a = a * 10 + c - 480;
	return a - 48;
}

string readStr() {
	string s;
	for (char c; (c = gc()) != '\n';) s += c;
	return s;
}
