/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * enDescription: Returns true iff p lies on the line segment from s to e.
 * Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using Point<double>.
 * Description: 当且仅当 p 位于线段 se 上时返回 true。
 * 使用 Point<double> 时改用 \texttt{(segDist(s,e,p)<=epsilon)}。
 * Status:
 */
#pragma once

#include "Point.h"
#include "SegmentDistance.h"

template<class P> bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> bool onSegment(P s, P e, P p, double eps) {
  return segDist(s, e, p) <= eps;
}
