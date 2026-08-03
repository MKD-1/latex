/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * enDescription: Disjoint-set data structure.
 * Description: 并查集数据结构。0-index.
 * Time: $O(\alpha(N))$
 */
#pragma once

struct UF {
	vi p;
	UF(int n) : p(n, -1) {}
	int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
	bool merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (p[a] > p[b]) swap(a, b);
		p[a] += p[b]; p[b] = a;
		return true;
	}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -p[find(x)]; }
};
