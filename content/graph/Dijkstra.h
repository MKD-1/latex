/**
 * Author: 未确认
 * Date: 2026-09-02
 * License: 未确认
 * Source: 未确认
 * enDescription: Calculates single-source shortest paths in a directed graph with non-negative edge weights.
 * Vertices are 0-indexed; adj[u] contains {v, w} for an edge u -> v. Requires non-negative weights,
 * a valid s for a non-empty graph, and no overflow of path lengths. Returns distances from s, with unreachable
 * vertices equal to infl. An empty graph returns an empty vector.
 * Description: 计算非负边权有向图的单源最短路。顶点从 0 开始编号；adj[u] 中的 {v, w} 表示边 u -> v。
 * 非空图要求 s 合法且路径长度不溢出。返回从 s 出发的距离，不可达顶点为 infl；空图返回空 vector。
 * Time: O((V + E) log V)
 * Status: stress-tested
 */
#pragma once

constexpr ll infl = LLONG_MAX;
using pll = pair<ll, ll>;
vector<ll> dijkstra(const vector<vector<pll>>& adj, int s) {
	if (adj.empty()) return {};
	vector<ll> dist(sz(adj), infl);
	priority_queue<pll, vector<pll>, greater<pll>> pq;
	pq.push({dist[s] = 0, s});
	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if (d != dist[u]) continue;
		for (auto [v, w] : adj[u]) if (d + w < dist[v])
			pq.push({dist[v] = d + w, v});
	}
	return dist;
}
