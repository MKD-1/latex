/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * enDescription:\\
\begin{minipage}{75mm}
Returns the signed distance between point p and the line containing points a and b.
Positive value on left side and negative on right as seen from a towards b. a==b gives nan.
P is supposed to be Point<T> or Point3D<T> where T is e.g. double or long long.
It uses products in intermediate steps so watch out for overflow if using int or long long.
Using Point3D will always give a non-negative distance. For Point3D, call .dist on the result of the cross product.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Description:\\
\begin{minipage}{75mm}
返回点p到包含点a和b的直线的有符号距离。
从a到b看，左侧为正值，右侧为负值。a==b时返回nan。
P应该是Point<T>或Point3D<T>类型，其中	T可以是double或long long等类型。
在中间步骤中使用了乘积运算，因此如果使用int或long long类型，请注意溢出。
使用Point3D将始终给出非负距离。对于Point3D，请在叉积的结果上调用.dist。
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"

template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return (double)(b-a).cross(p-a)/(b-a).dist();
}
