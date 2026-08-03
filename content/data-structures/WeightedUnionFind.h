/**
 * Author: Unknown
 * Date: 2026-07-18
 * License: CC0
 * Source: folklore, AtCoder Library-style weighted DSU (license not confirmed)
 * enDescription: Disjoint-set data structure with additive potentials, 0-index.
 *  dt[x] is weight(root) - weight(x) after find(x). merge(a, b, d) adds the
 *  constraint weight(b) - weight(a) = d and returns false iff it contradicts
 *  existing constraints. dist(a, b) returns weight(b) - weight(a), and requires
 *  a and b to be connected.
 *  Works for signed additive types without overflow.
 * Description: 带权并查集数据结构，0-index.
 *  find(x) 后 dt[x] 表示 weight(x) - weight(root)。
 *  merge(a, b, d) 添加约束 weight(b) - weight(a) = d，若与已有约束矛盾则返回 false。
 *  dist(a, b) 返回 weight(b) - weight(a), 即 dt[b] - dt[a]，要求 a 和 b 已连通。
 *  适用于有符号的加法类型，且不会溢出。
 * Time: $O(\alpha(N))$
 * Status: stress-tested
 */
#pragma once

struct wUF {
  vi p, dt;
  wUF(int n) : p(n, -1), dt(n, 0) {}
  int find(int x) {  
    if (p[x] < 0) return x;
    int rt = find(p[x]);
    dt[x] += dt[p[x]];
    return p[x] = rt;
  }
  bool merge(int a, int b, int d) {
    int ra = find(a), rb = find(b);
    if (ra == rb) return dt[b] - dt[a] == d;
    d -= dt[b] - dt[a];
    if (p[ra] > p[rb]) swap(ra, rb), d = -d;
    p[ra] += p[rb]; p[rb] = ra; dt[rb] = d;
    return true;
  }
	int dist(int a, int b) {
    assert(sameSet(a, b));
    return dt[b] - dt[a];
  }
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -p[find(x)]; }
};
