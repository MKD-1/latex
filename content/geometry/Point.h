/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * enDescription: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Description: 平面点类。
 * 	T为double或long long等类型(避免int)。
 * Status: Works fine, used a lot
 */
#pragma once

constexpr double eps = 0;
template<class T> int sgn(T x) { return (x > eps)-(x < -eps); }
template<class T> struct Point {
	using P = Point;
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  bool approxEq(P p) const { return !(sgn(x-p.x)|sgn(y-p.y)); }
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	P operator*(T d) const { return P(x * d, y * d); }
	P operator/(T d) const { return P(x / d, y / d); }
	T dot(P p) const { return x * p.x + y * p.y; } // 点乘
	T cross(P p) const { return x * p.y - y * p.x; } // 叉乘
	// Oa与Ob叉乘
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x * x + y * y; } // 到原点距离平方
	double dist()const{return sqrt((double)dist2());}//到原点距离
	// 与x轴夹角，范围[-pi,pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // 单位化
	P perp() const { return P(-y, x); } // 绕原点逆时针旋转九十度
	P normal() const { return perp().unit(); } // 法向量
	// 绕原点逆时针旋转a弧度
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
