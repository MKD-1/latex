/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * enDescription: Returns where $p$ is as seen from $s$ towards $e$. 1/0/-1 $\Leftrightarrow$ left/on line/right.
 * If the optional argument $eps$ is given 0 is returned if $p$ is within distance $eps$ from the line.
 * P is supposed to be Point<T> where T is e.g. double or long long.
 * It uses products in intermediate steps so watch out for overflow if using int or long long.
 * Description: 返回点$p$相对于线段$se$的位置。1/0/-1 $\Leftrightarrow$ 左侧/在线上/右侧。
 * 如果给定了可选参数$eps$，则当点$p$距离线段$se$的距离小于$eps$时，返回0。
 * P应该是Point<T>类型，其中T可以是double或long long等类型。
 * 在中间步骤中使用了乘积运算，因此如果使用int或long long类型，请注意溢出。
 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1;
 * Status: tested
 */
#pragma once

#include "Point.h"

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
	auto a = (e-s).cross(p-s); // 避免 s==e
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}
