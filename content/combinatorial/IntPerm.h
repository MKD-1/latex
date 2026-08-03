/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * enDescription: Permutation -> integer conversion. (Not order preserving.)
 * Integer -> permutation can use a lookup table.
 * Description: 排列 -> 整数转换（不保持顺序）。
 * 整数 -> 排列可以查表。
 * Time: O(n)
 */
#pragma once

int permToInt(vi& v) {
	int use = 0, i = 0, r = 0;
	for(int x:v) r = r * ++i + __builtin_popcount(use & -(1<<x)),
		use |= 1 << x;                     // (note: minus, not ~!)
	return r;
}
