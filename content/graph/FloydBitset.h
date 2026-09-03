/**
 * Author: 未确认
 * Date: 2026-09-03
 * License: 未确认
 * Source: 用户提供的 bitset Floyd 传递闭包代码（来源/许可证未确认）
 * enDescription: Computes the transitive closure of a directed graph in-place.
 * Input reach has one bitset per vertex; reach[u][v] should be true for each
 * direct edge u -> v. Vertices are 0-indexed, and the vector size n must satisfy
 * n <= LEN. The diagonal is set, so every vertex is reachable from itself.
 * After the call, reach[u][v] is true iff v is reachable from u (possibly by
 * a path of length zero).
 * Description: 原地计算有向图的传递闭包。输入 reach 每行一个顶点的 bitset，
 * reach[u][v] 初始表示直接边 u -> v；顶点从 0 开始编号，顶点数 n 必须满足
 * n <= LEN。函数会设置对角线，因此每个点都可到达自身。调用后 reach[u][v]
 * 当且仅当 v 从 u 可达（允许长度为零的路径）。
 * Time: O(N^3 / W), where W is the machine word size used by bitset; O(N^2 / W) space.
 * Status: stress-tested
 */
#pragma once

template <size_t LEN>
void floydBitset(vector<bitset<LEN>>& reach) {
	int n = sz(reach);
	assert(n <= (int)LEN);
	rep(i,0,n) reach[i].set(i);
	rep(k,0,n) rep(i,0,n) if (reach[i][k])
		reach[i] |= reach[k];
}
