/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * enDescription: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $V^2 \max |w_i| < \tilde{} 2^{63}$.
 * Description: 计算可能含$\textbf{负权边}$的图中从 s 出发的最短路。
 * 不可达点的距离为 inf；能经由负权环到达的点距离为 -inf。
 * 假设 $V^2 \max |w_i| < \tilde{} 2^{63}$。
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
#pragma once

constexpr ll infl = LLONG_MAX;
struct Ed { int u, v, w, s() { return u < v ? u : -u; }};
struct Node { ll dist = infl; int prev = -1; };

void bellmanFord(vector<Node>& nodes, vector<Ed>& eds, int s) {
  nodes[s].dist = 0;
  sort(all(eds), [](Ed a, Ed b) { return a.s() < b.s(); });

  int lim = sz(nodes) / 2 + 2; // /3+100 with shuffled vertices
  rep(i,0,lim) for (Ed ed : eds) {
    Node cur = nodes[ed.u], &dest = nodes[ed.v];
    if (abs(cur.dist) == infl) continue;
    ll d = cur.dist + ed.w;
    if (d < dest.dist) {
      dest.prev = ed.u;
      dest.dist = (i < lim-1 ? d : -infl);
    }
  }
  rep(i,0,lim) for (Ed e : eds) {
    if (nodes[e.u].dist == -infl)
      nodes[e.v].dist = -infl;
  }
}
