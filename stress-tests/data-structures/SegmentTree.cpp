#include "../utilities/template.h"

#include "../../content/data-structures/SegmentTree.h"

static unsigned RA = 1231231;
int ra() {
	RA *= 574841;
	RA += 14;
	return RA >> 1;
}

namespace maximum {

struct Info {
	int val = INT_MIN;
	static Info merge(const Info& a, const Info& b) {
		return {max(a.val, b.val)};
	}
};

}

namespace nonabelian {

// https://en.wikipedia.org/wiki/Dihedral_group_of_order_6
const int lut[6][6] = {
	{0, 1, 2, 3, 4, 5},
	{1, 0, 4, 5, 2, 3},
	{2, 5, 0, 4, 3, 1},
	{3, 4, 5, 0, 1, 2},
	{4, 3, 1, 2, 5, 0},
	{5, 2, 3, 1, 0, 4}
};

struct Info {
	int val = 0;
	static Info merge(const Info& a, const Info& b) {
		return {lut[a.val][b.val]};
	}
};

}

int main() {
	{
		vector<maximum::Info> v;
		SegmentTree<maximum::Info> t(v);
		assert(t.query(0, 0).val == INT_MIN);
	}

	if (0) {
		const int N = 10000;
		vector<maximum::Info> v(N);
		SegmentTree<maximum::Info> tr(v);
		ll sum = 0;
		rep(it,0,1000000) {
			tr.update(ra() % N, {ra()});
			int i = ra() % N;
			int j = ra() % N;
			if (i > j) swap(i, j);
			int x = tr.query(i, j+1).val;
			sum += x;
		}
		cout << sum << endl;
		// return 0;
	}

	rep(n,1,10) {
		vector<maximum::Info> init(n);
		SegmentTree<maximum::Info> tr(init);
		vi v(n, INT_MIN);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % (n+2);

			int r = rand() % 100;
			if (r < 30) {
				int ma = INT_MIN;
				rep(k,i,j) ma = max(ma, v[k]);
				assert(ma == tr.query(i,j).val);
			}
			else {
				i = min(i, n-1);
				tr.update(i, {x});
				v[i] = x;
			}
		}
	}

	rep(n,1,10) {
		vector<nonabelian::Info> init(n);
		SegmentTree<nonabelian::Info> tr(init);
		vi v(n);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % 6;

			int r = rand() % 100;
			if (r < 30) {
				int ma = 0;
				rep(k,i,j) ma = nonabelian::lut[ma][v[k]];
				assert(ma == tr.query(i,j).val);
			}
			else {
				i = min(i, n-1);
				tr.update(i, {x});
				v[i] = x;
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
