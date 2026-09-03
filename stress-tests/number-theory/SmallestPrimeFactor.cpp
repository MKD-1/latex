#include "../utilities/template.h"

#include "../../content/number-theory/SmallestPrimeFactor.h"

int naiveSmallestPrimeFactor(int x) {
	if (x < 2) return 0;
	for (int p = 2; p <= x / p; ++p)
		if (x % p == 0) return p;
	return x;
}

int main() {
	vi pr;
	assert(SPF(0, pr) == vi{0});
	assert(pr.empty());
	pr.clear();
	assert(SPF(1, pr) == vi({0, 0}));
	assert(pr.empty());
	pr.clear();
	assert(SPF(2, pr) == vi({0, 0, 2}));
	assert(pr == vi{2});
	for (int lim = 0; lim <= 10'000; ++lim) {
		pr.clear();
		vi spf = SPF(lim, pr), wantPr;
		assert(sz(spf) == lim + 1);
		for (int x = 0; x <= lim; ++x) {
			assert(spf[x] == naiveSmallestPrimeFactor(x));
			if (x >= 2 && spf[x] == x) wantPr.push_back(x);
		}
		assert(pr == wantPr);
	}
	mt19937 rng(123456789);
	for (int it = 0; it < 1'000; ++it) {
		int lim = uniform_int_distribution<int>(0, 100'000)(rng);
		pr.clear();
		vi spf = SPF(lim, pr), wantPr;
		for (int q = 0; q < 100; ++q) {
			int x = uniform_int_distribution<int>(0, lim)(rng);
			assert(spf[x] == naiveSmallestPrimeFactor(x));
		}
		for (int x = 2; x <= lim; ++x)
			if (naiveSmallestPrimeFactor(x) == x) wantPr.push_back(x);
		assert(pr == wantPr);
	}
	cout << "Tests passed!" << endl;
}
