/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * enDescription:\\
	\begin{minipage}{75mm}
	If a unique intersection point of the lines going through s1,e1 and s2,e2 exists \{1, point\} is returned.
	If no intersection point exists \{0, (0,0)\} is returned and if infinitely many exists \{-1, (0,0)\} is returned.
	The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
	Products of three coordinates are used in intermediate steps so watch out for overflow if using int or ll.
	\end{minipage}
	\begin{minipage}{15mm}
	\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
	\end{minipage}
 * Description:\\
	\begin{minipage}{75mm}
	如果存在唯一的交点，返回\{1, 交点\}；如果不存在交点，返回\{0, (0,0)\}；如果存在无数个交点，返回\{-1, (0,0)\}。
	如果使用\texttt{Point<ll>}，且交点坐标不全为整数，则返回错误的结果。
	中间步骤使用了三个坐标的乘积，因此如果使用\texttt{int}或\texttt{ll}，请注意可能的溢出。
	\end{minipage}
	\begin{minipage}{15mm}
	\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
	\end{minipage}
 * Usage:
 * 	auto res = lineInter(s1,e1,s2,e2);
 * 	if (res.first == 1)
 * 		cout << "intersection point at " << res.second << endl;
 * Status: stress-tested, and tested through half-plane tests
 */
#pragma once

#include "Point.h"

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}
