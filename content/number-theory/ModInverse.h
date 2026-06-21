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

// const ll mod = 1000000007, LIM = 200000; ///include-line
ll* inv = new ll[LIM] - 1; inv[1] = 1;
rep(i,2,LIM) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
