#include "../utilities/template.h"

#include "../../content/data-structures/WeightedUnionFind.h"

int main() {
	{
		wUF uf(1);
		assert(uf.size(0) == 1);
		assert(uf.dist(0, 0) == 0);
		assert(uf.merge(0, 0, 0));
		assert(!uf.merge(0, 0, 1));
	}
	{
		wUF uf(3);
		// merge(a, b, d) means weight(b) - weight(a) = d.
		// dist(a, b) returns weight(b) - weight(a).
		assert(uf.merge(0, 1, -5));
		assert(uf.merge(1, 2, 7));
		assert(uf.dist(0, 2) == 2);
		assert(uf.dist(2, 0) == -2);
		assert(uf.merge(0, 2, 2));
		assert(!uf.merge(0, 2, 3));
	}
	{
		wUF uf(4);
		assert(uf.merge(0, 1, 3));
		assert(uf.merge(2, 3, -4));
		assert(uf.merge(1, 3, 5));
		assert(uf.dist(0, 3) == 8);
		assert(uf.dist(2, 0) == -12);
		assert(uf.size(0) == 4);
		assert(uf.sameSet(0, 2));
		assert(!uf.merge(2, 0, -11));
	}

	srand(2);
	rep(it,0,20000) {
		int N = 1 + rand() % 9;
		wUF uf(N);
		vector<vector<int>> known(N, vector<int>(N));
		vector<vector<int>> dist(N, vector<int>(N));
		rep(i,0,N) known[i][i] = 1;

		rep(q,0,200) {
			int a = rand() % N, b = rand() % N;
			int d = (rand() % 41) - 20;
			bool ok = uf.merge(a, b, d);
			bool expected = !known[a][b] || dist[a][b] == d;
			assert(ok == expected);

			if (expected && !known[a][b]) {
				vector<int> A, B;
				rep(i,0,N) if (known[i][a]) A.push_back(i);
				rep(j,0,N) if (known[b][j]) B.push_back(j);
				for (int i : A) for (int j : B) {
					int nd = dist[i][a] + d + dist[b][j];
					known[i][j] = known[j][i] = 1;
					dist[i][j] = nd;
					dist[j][i] = -nd;
				}
			}

			rep(i,0,N) rep(j,0,N) if (known[i][j]) {
				assert(uf.sameSet(i, j));
				assert(uf.dist(i, j) == dist[i][j]);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
