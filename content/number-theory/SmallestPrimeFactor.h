/**
 * Author: 未确认
 * Date: 2026-08-05
 * License: 未确认
 * Source: 未确认
 * enDescription: Eratosthenes sieve. Returns spf with spf[x] equal to the
 * smallest prime factor of x for every x in [2, lim], and appends all primes
 * in [2, lim] to pr. spf[0] = spf[1] = 0. Requires lim >= 0; clear pr before
 * calling if it is not empty.
 * Description: 埃拉托斯特尼筛。返回数组 spf；对每个 x $\in$ [2, lim]，spf[x] 为
 * x 的最小质因子，并将 [2, lim] 中的全部质数追加到 pr。spf[0] = spf[1] = 0。
 * 要求 lim >= 0；若 pr 非空，调用前须先清空。
 * Time: $O(\mathrm{lim}\log\log\mathrm{lim})$ time, $O(\mathrm{lim})$ memory.
 * Status: stress-tested
 */
#pragma once

vi SPF(int lim, vi& pr) {
	vi spf(lim + 1);
	for (int i = 2; i <= lim; i++) if (!spf[i]) {
		spf[i] = i, pr.push_back(i);
		for (int j = i * i; j <= lim; j += i)
			if (!spf[j]) spf[j] = i;
	}
	return spf;
}
