/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * enDescription: Pre-computation of modular inverses. Assumes LIM $\le$ mod and that mod is a prime.
 * Description: 预计算模逆元，假设LIM $\le$ mod且mod是质数。
 * Status: Works
 */
#pragma once


// constexpr ll MOD = 1000000007, LIM = 200000; ///include-line
vector<int> inv(LIM + 1, 0);inv[1] = 1;
for (int i = 2; i <= LIM; i++)
  inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;