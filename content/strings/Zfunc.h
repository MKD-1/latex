/**
 * Author: chilli
 * License: CC0
 * enDescription: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Description: 维护 [l, r) 表示当前已知最靠右的匹配区间 s[l..r-1] == s[0..r-l-1]。
 * z[i] 计算 s[i:] 与 s 的最长公共前缀，
 * 但 z[0] = 0 除外。(abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vi Z(const string& S) {
	vi z(sz(S));
	int l = -1, r = -1;
	rep(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}
