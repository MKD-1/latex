/**
 * Author: Johan Sannemo
 * License: CC0
 * enDescription: Compute indices for the longest increasing subsequence.
 * Description: 返回最长上升(非降)子序列的下标。
 * Time: $O(N \log N)$
 * Status: Tested on kattis:longincsubseq, stress-tested
 */
#pragma once

template<class I> vi lis(const vector<I> &S) {
  if (S.empty()) return {};
  vi prev(sz(S));
  using p = pair<I, int>;
  vector<p> res;
  rep(i, 0, sz(S)) {
    // 把lower_bound中的 0 -> i 以求最长非降子序列
    auto it = lower_bound(all(res), p{S[i], 0});
    if (it == res.end()) res.emplace_back(), it = res.end()-1;
    *it = {S[i], i};
    prev[i] = it == res.begin() ? 0 : (it - 1)->second;
  }
  int L = sz(res), cur = res.back().second;
  vi ans(L);
  while (L--) ans[L] = cur, cur = prev[cur];
  return ans;
}