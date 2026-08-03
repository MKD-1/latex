/**
 * Author: chilli, c1729, Simon Lindholm
 * Date: 2019-03-28
 * License: CC0
 * Source: Wikipedia, https://miller-rabin.appspot.com/
 * enDescription: Deterministic Miller-Rabin primality test.
 * Guaranteed to work for numbers up to $7 \cdot 10^{18}$; for larger numbers, use Python and extend A randomly.
 * Description: 确定性的 Miller-Rabin 素性测试。
 * 保证对不超过 $7\cdot 10^{18}$ 的数有效；
 * 更大的数建议使用 Python 并随机扩展测试底数集合 A。
 * Time: 7 times the complexity of $a^b \mod c$.
 * Status: Stress-tested
 */
#pragma once

#include "ModMulLL.h"

bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  vector<ull> A = {2,325,9375,28178,450775,9780504,1795265022};
  ull s = __builtin_ctzll(n - 1), d = n >> s;
  for (ull a: A) {
    ull p = modpow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--)
      p = modmul(p, p, n);
    if (p != n - 1 && i != s) return false;
  }
  return true;
}
