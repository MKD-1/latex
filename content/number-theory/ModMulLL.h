/**
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Date: 2019-04-24
 * License: CC0
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b \le c \le 7.2\cdot 10^{18}$.
 * Time: O(1) for \texttt{modmul}, O(\log b) for \texttt{modpow}
 * Status: stress-tested, proven correct
 * Details:
 * This runs ~2x faster than the naive (__int128_t)a * b % M.
 * A proof of correctness is in doc/modmul-proof.tex. An earlier version of the proof,
 * from when the code used a * b / (long double)M, is in doc/modmul-proof.md.
 * The proof assumes that long doubles are implemented as x87 80-bit floats; if they
 * are 64-bit, as on e.g. MSVC, the implementation is only valid for
 * $0 \le a, b \le c < 2^{52} \approx 4.5 \cdot 10^{15}$.
 */
#pragma once

using ull = unsigned long long;

// // 浮点数估计商，整数修正余数，快，需要long double至少有64位有效精度
static_assert(std::numeric_limits<long double>::digits >= 64,
              "long double precision is not enough for this modmul");
ull modmul(ull a, ull b, ull mod) {
  ll ret = a * b - mod * ull(1.L / mod * a * b);
  return ret + mod * (ret < 0) - mod * (ret >= (ll) mod);
}
// O(log),慢
ull modmul(ull x, ull y, ull mod) {
  ull res = 0;
  for (res %= mod; y; y >>= 1, x += x >= mod - x ? x - mod : x)
    if (y & 1)res += res >= mod - x ? x - mod : x;
  return res;
}

// 需要 __uint128_t
ull modmul(ull a, ull b, ull mod) {
  return (__uint128_t) a * b % mod;
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
