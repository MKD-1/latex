/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * enDescription: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 * Description: 找到两个整数 $x$ 和 $y$，使得 $ax+by=\gcd(a,b)$。如果你只需要 gcd，可以使用内置的 \texttt{\_\_gcd}。
 * 如果 $a$ 和 $b$ 互质，那么 $x$ 就是 $a \pmod{b}$ 的逆元。
 * Time: O(\log\min(a,b))
 */
#pragma once

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}
