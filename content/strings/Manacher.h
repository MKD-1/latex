/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * enDescription: For each position in a string, computes p[0][i] = half length of
 *  longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
 * Description: 对于字符串中的每个位置 i ，
 * p[0][i] = 中心在 i-1 与 i 之间的最长偶回文半长，
 * p[1][i] = 中心在 i 的最长奇回文半长(向下取整)(不包括 i)
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

array<vi, 2> manacher(const string &s) {
  int n = sz(s);
  array<vi, 2> p = {vi(n + 1, 0), vi(n, 0)};
  rep(id, 0, 2)for (int i = 0, l = 0, r = 0; i < n; i++) {
    int t = r - i + !id;
    if (i < r) p[id][i] = min(t, p[id][l + t]);
    int L = i - p[id][i], R = i + p[id][i] - !id;
    while (L - 1 >= 0 && R + 1 <= n - 1 && s[L - 1] ==s[R + 1])
      p[id][i]++, L--, R++;
    if (R > r) l = L, r = R;
  }
  return p;
}
