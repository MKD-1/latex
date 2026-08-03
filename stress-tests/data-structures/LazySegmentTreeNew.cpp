#include "../utilities/template.h"

const ll MOD = 1000000007LL;

#include "../../content/data-structures/LazySegmentTreeNew.h"

static unsigned RA = 1231231;
int ra() {
	RA *= 574841;
	RA += 14;
	return RA >> 1;
}

int main() {
	rep(n, 1, 15) {
		vector<Info> init(n);
		Seg<Info, Tag> tr(init);
		vi v(n, 0);
		rep(it, 0, 200000) {
			int l = ra() % (n + 1);
			int r = ra() % (n + 1);
			if (l > r) swap(l, r);
			int typ = ra() % 100;
			if (typ < 35) {
				ll ans = 0;
				rep(i, l, r) ans = (ans + v[i]) % MOD;
				assert(ans == tr.query(0, n, l, r, 1).val);
			} else {
				Tag t;
				t.mul = ra() % 7;
				t.add = ra() % 11;
				tr.update(0, n, l, r, 1, t);
				rep(i, l, r) v[i] = (v[i] * t.mul + t.add) % MOD;
			}
		}
	}
	cout << "Tests passed!" << endl;
}
