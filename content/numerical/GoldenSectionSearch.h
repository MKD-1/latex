/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-17
 * License: CC0
 * Source: Numeriska algoritmer med matlab, Gerd Eriksson, NADA, KTH
 * enDescription: Finds the argument minimizing the function $f$ in the interval $[a,b]$
 * assuming $f$ is unimodal on the interval, i.e. has only one local minimum and no local
 * maximum. The maximum error in the result is $eps$. Works equally well for maximization
 * with a small change in the code. See TernarySearch.h in the Various chapter for a
 * discrete version.
 * Description:
 * 在区间$[a,b]$中寻找使得$f(x)$最小化的$x$，
 * 假设$f$在该区间上是单峰的，即只有一个局部最小值且没有局部最大值。
 * 结果的最大误差为$eps$。对于最大化问题，只需在代码中稍作修改即可。
 * 离散版本参见Various章节中的TernarySearch.h。	
 * Usage:
	double func(double x) { return 4+x+.3*x*x; }
	double xmin = gss(-1000,1000,func);
 * Time: O(\log((b-a) / \epsilon))
 * Status: tested
 */
#pragma once

/// 重要的是 r 必须足够精确，否则不能保证 a < x1 < x2 < b 这个不等式始终成立。
template<class F>
double gss(double a, double b, F f) {
	double r = (sqrt(5)-1)/2, eps = 1e-7;
	double x1 = b - r*(b-a), x2 = a + r*(b-a);
	double f1 = f(x1), f2 = f(x2);
	while (b-a > eps)
		if (f1 < f2) { // 改为 f1 > f2 则为最大化
			b = x2; x2 = x1; f2 = f1;
			x1 = b - r*(b-a); f1 = f(x1);
		} else {
			a = x1; x1 = x2; f1 = f2;
			x2 = a + r*(b-a); f2 = f(x2);
		}
	return a;
}
