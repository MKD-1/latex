#include "../utilities/template.h"

#include "../../content/data-structures/Treap.h"

pair<int, int> split2(Treap& tr, int n, int v) {
	if (!n) return {};
	if (tr.adj[n].val >= v) {
		auto pa = split2(tr, tr.adj[n].l, v);
		tr.adj[n].l = pa.second;
		tr.recalsiz(n);
		return {pa.first, n};
	} else {
		auto pa = split2(tr, tr.adj[n].r, v);
		tr.adj[n].r = pa.first;
		tr.recalsiz(n);
		return {n, pa.second};
	}
}

int ra() {
	static unsigned x;
	x *= 4176481;
	x += 193861934;
	return x >> 1;
}

int main() {
	srand(3);
	rep(it,0,1000) {
		Treap tr;
		vi exp;
		rep(i,0,10) {
			exp.emplace_back(i*2+2);
		}
		int n = 0;
		rep(i,0,10)
			n = tr.merge(n, tr.add(i*2+2));

		int v = rand() % 25;
		int left = tr.size(split2(tr, n, v).first);
		int rleft = (int)(lower_bound(all(exp), v) - exp.begin());
		assert(left == rleft);
	}

	rep(it,0,10000) {
		Treap tr;
		vi exp;
		rep(i,0,10) exp.emplace_back(i);
		int n = 0;
		rep(i,0,10)
			n = tr.merge(n, tr.add(i));

		int i = ra() % 11, j = ra() % 11;
		if (i > j) swap(i, j);
		int k = ra() % 11;
		if (i < k && k < j) continue;

		tr.move(n, i, j, k);
		// cerr << i << ' ' << j << ' ' << k << endl;

		int nk = (k >= j ? k - (j - i) : k);
		vi iv(exp.begin() + i, exp.begin() + j);
		exp.erase(exp.begin() + i, exp.begin() + j);
		exp.insert(exp.begin() + nk, all(iv));

		int ind = 0;
		tr.each(n, [&](int x) {
			// cerr << x << ' ';
			assert(x == exp[ind++]);
		});
		// cerr << endl;
	}
	cout<<"Tests passed!"<<endl;
}
