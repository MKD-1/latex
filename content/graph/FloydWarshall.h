/**
 * Author: Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * enDescription: Calculates all-pairs shortest path in a directed graph that might have negative edge weights.
 * Input is an distance matrix $m$, where $m[i][j] = \texttt{inf}$ if $i$ and $j$ are not adjacent.
 * As output, $m[i][j]$ is set to the shortest distance between $i$ and $j$, \texttt{inf} if no path,
 * or \texttt{-inf} if the path goes through a negative-weight cycle.
 * Description: 计算可能含负权边的有向图的全源最短路。
 * 输入为距离矩阵 m，若 i 与 j 不相邻则 m[i][j] = infl。
 * 输出时，m[i][j] 为两点间最短距离；不可达为 infl；若路径经过负权环则为 -infl。
 * Time: O(N^3)
 * Status: slightly tested
 */
#pragma once

constexpr ll infl = LLONG_MAX;
void floydWarshall(vector<vector<ll>>& m) {
  int n = sz(m);
  rep(i,0,n) m[i][i] = min(m[i][i], 0LL);
  rep(k,0,n) rep(i,0,n) rep(j,0,n)
    if (m[i][k] != infl && m[k][j] != infl) {
      auto newDist = max(m[i][k] + m[k][j], -infl);
      m[i][j] = min(m[i][j], newDist);
    }
  rep(k,0,n) if (m[k][k] < 0) rep(i,0,n) rep(j,0,n)
    if (m[i][k] != infl && m[k][j] != infl) m[i][j] = -infl;
}
