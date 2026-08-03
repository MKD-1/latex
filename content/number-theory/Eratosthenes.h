/**
 * Author: Håkan Terelius
 * Date: 2009-08-26
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * enDescription: Prime sieve for generating all primes up to a certain limit. isprime$[i]$ is true iff $i$ is a prime.
 * Description: 生成不超过给定上界的所有质数的质数筛。isprime[i] 为真当且仅当 i 是质数。
 * Time: lim=100'000'000 $\approx$ 0.8 s. Runs 30\% faster if only odd indices are stored.
 * Status: Tested
 */
#pragma once

constexpr int pmx = 5'000'000;
bitset<pmx> isp;
vi eratosthenesSieve(int lim) {
  isp.set(); isp[0] = isp[1] = 0;
  for (int i = 4; i < lim; i += 2) isp[i] = 0;
  for (int i = 3; i*i < lim; i += 2) if (isp[i])
    for (int j = i*i; j < lim; j += i*2) isp[j] = 0;
  vi ret;
  rep(i,2,lim) if (isp[i]) ret.push_back(i);
  return ret;
}
