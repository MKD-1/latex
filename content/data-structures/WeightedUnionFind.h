/**
 * Author: Unknown
 * Date: 2026-06-14
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with potentials.
 *  join(a, b, w) adds the constraint weight(a) - weight(b) = w.
 *  diff(a, b) returns weight(a) - weight(b).
 * Time: $O(\alpha(N))$
 */
#pragma once

template<class T = int>
struct WeightedUF {
	vi e;
	vector<T> w;
	WeightedUF(int n) : e(n, -1), w(n, T(0)) {}
	int find(int x) {
		if (e[x] < 0) return x;
		int p = e[x], r = find(p);
		w[x] += w[p];
		return e[x] = r;
	}
	T weight(int x) { return find(x), w[x]; }
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	T diff(int a, int b) {
		assert(sameSet(a, b));
		return weight(a) - weight(b);
	}
	bool join(int a, int b, T d) {
		int ra = find(a), rb = find(b);
		if (ra == rb) return false;
		T x = d + weight(b) - weight(a);
		if (e[ra] > e[rb]) swap(ra, rb), x = -x;
		e[ra] += e[rb]; e[rb] = ra; w[rb] = x;
		return true;
	}
};
