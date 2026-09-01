/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * enDescription: Topological sorting. Given is an oriented graph.
 * Output is an ordering of vertices, such that there are edges only from left to right.
 * If there are cycles, the returned list will have size smaller than $n$ -- nodes reachable
 * from cycles will not be returned.
 * Description: 拓扑排序。
 * 给定一个有向图，输出一个顶点排列，使得所有边都从排列左侧指向右侧。
 * 如果图中存在环，返回列表的大小会小于 n，从环可达的点不会被返回。
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
#pragma once

vi topoSort(const vector<vi>& adj) {
  vi indeg(sz(adj), 0), tfn;
  for (auto& u : adj) for (int v : u) indeg[v]++;
  rep(i,1,sz(adj)) if (indeg[i] == 0) tfn.push_back(i);
  rep(i,0,sz(tfn)) for (int v : adj[tfn[i]])
    if (--indeg[v] == 0) tfn.push_back(v);
  return tfn;
}
