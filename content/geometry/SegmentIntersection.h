/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * enDescription:\\
\begin{minipage}{75mm}
If a unique intersection point between the line segments going from s1 to e1 and from s2 to e2 exists then it is returned.
If no intersection point exists an empty vector is returned.
If infinitely many exist a vector with 2 elements is returned, containing the endpoints of the common line segment.
The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Description:\\
\begin{minipage}{75mm}
若从 s1 到 e1 的线段与从 s2 到 e2 的线段存在唯一交点，则返回该交点。
若不存在交点，则返回空 vector。
若存在无限多个交点，则返回一个包含 2 个元素的 vector，其中存放公共线段的两个端点。
如果 P 是 Point<ll> 且交点坐标不是整数，返回的位置会是错误的。
中间步骤会用到三个坐标的乘积，因此使用 int 或 long long 时要注意溢出。
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Usage:
 * vector<P> inter = segInter(s1,e1,s2,e2);
 * if (sz(inter)==1)
 *   cout << "segments intersect at " << inter[0] << endl;
 * Status: stress-tested, tested on kattis:intersection
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

template<class P> vector<P> segInter(P s1, P e1, P s2, P e2) {
  auto os1 = s2.cross(e2, s1), oe1 = s2.cross(e2, e1),
       os2 = s1.cross(e1, s2), oe2 = s1.cross(e1, e2);
  // 判断交点是否为唯一的非端点交点。
  if (sgn(os1) * sgn(oe1) < 0 && sgn(os2) * sgn(oe2) < 0)
    return {(s1 * oe1 - e1 * os1) / (oe1 - os1)};
  set<P> res;
  if (onSegment(s2, e2, s1)) res.insert(s1);
  if (onSegment(s2, e2, e1)) res.insert(e1);
  if (onSegment(s1, e1, s2)) res.insert(s2);
  if (onSegment(s1, e1, e2)) res.insert(e2);
  return {all(res)};
}
