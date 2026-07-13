/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * enDescription:\\
\begin{minipage}{75mm}
Returns the shortest distance between point p and the line segment from point s to e.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Description: \\
\begin{minipage}{75mm}
返回点 p 到线段 se 的最短距离。
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Usage: 
 * 	Point<double> a, b(2,2), p(1,1);
 * 	bool onSegment = segDist(a,b,p) < 1e-10;
 * Status: tested
 */
#pragma once

#include "Point.h"

using P = Point<double>;
double segDist(P &s, P &e, P &p) {
  if (s == e) return (p - s).dist();
  auto d = (e-s).dist2(), t = max(.0, min(d, (p-s).dot(e-s)));
  // t = clamp((p - s).dot(e - s), 0, d);
  return ((p - s) * d - (e - s) * t).dist() / d;
}