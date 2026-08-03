/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * enDescription: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Description: 计算树的LCA的数据结构。
 * 树以1为根。C为树的邻接表，可以有向可以无向。
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCA {
  int T = 0;
  vi time, path, ret;
  RMQ<int> rmq;

  LCA(vector<vi> &adj):time(sz(adj)),rmq((dfs(adj,1,-1),ret)){}
  void dfs(vector<vi> &adj, int u, int fa) {
    time[u] = T++;
    for (int v: adj[u]) if (v != fa) {
			path.push_back(u), ret.push_back(time[u]);
			dfs(adj, v, u);
		}// tout[u] = T; size_of_subtree[u] = tout[u] - time[u];
  }

  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
  //dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};
