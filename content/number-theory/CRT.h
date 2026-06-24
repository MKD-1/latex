/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * enDescription: Chinese Remainder Theorem.
 *
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$.
 * Assumes $mn < 2^{62}$.
 * Description: 中国剩余定理。
 * 
 * \texttt{crt(a, m, b, n)} 计算 $x$，使得 $x\equiv a \pmod m$, $x\equiv b \pmod n$。
 * 如果 $|a| < m$ 且 $|b| < n$， 则 $x$ 将满足 $0 \le x < \text{lcm}(m, n)$。
 * 假设 $mn < 2^{62}$。
 * Time: $\log(n)$
 * Status: Works
 */
#pragma once

#include "euclid.h"

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}
