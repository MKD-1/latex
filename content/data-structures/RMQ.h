/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * enDescription: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Description: 区间最小值查询。返回min(V[a], V[a + 1], ... V[b - 1])。
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

template<class T> struct RMQ {
  vector<vector<T> > tbl;
  RMQ(const vector<T> &val) : tbl(1, val) {// pw = 2^{k-1}
    for (int pw = 1, k = 1; pw * 2 <= sz(val); pw *= 2, k++) {
      tbl.emplace_back(sz(val) - pw * 2 + 1);
      rep(j, 0, sz(tbl[k]))
        tbl[k][j] = min(tbl[k - 1][j], tbl[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b); // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(tbl[dep][a], tbl[dep][b - (1 << dep)]);
  }
};
