/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * enDescription: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Description: 一种简短的自平衡树。
 * 顺序容器，支持对数时间split/merge，并且容易扩展额外信息。
 * Usage: rt = tr.merge(rt, tr.add(val));
 * rt = tr.insert(rt, tr.add(val), pos);
 * tr.each(rt, [](int x) {cout << x << ' ';});
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

struct Treap {
	struct Node {
		int l = 0, r = 0;
		int val = 0, pr = 0, siz = 1;
		Node(int val) : val(val), pr(rand()) {}
	};
	vector<Node> adj{Node(0)};
	int size(int x) { return x ? adj[x].siz : 0; }
	void recalsiz(int x) {
		if (x) adj[x].siz = size(adj[x].l) + size(adj[x].r) + 1;
	}
	int add(int val) {
		adj.push_back(Node(val));
		return sz(adj) - 1;
	}
	template<class F> void each(int x, F f) {
		if (x) each(adj[x].l, f), f(adj[x].val), each(adj[x].r, f);
	}
	pair<int, int> split(int x, int k) {
		if (!x) return {0, 0};
		if (size(adj[x].l)>=k){//"adj[x].val>=k" for lower_bound(k)
			auto [L,R] = split(adj[x].l, k);
			adj[x].l = R;
			recalsiz(x);
			return {L, x};
		} else { // and just "k"
			auto [L,R] = split(adj[x].r, k - size(adj[x].l) - 1);
			adj[x].r = L;
			recalsiz(x);
			return {x, R};
		}
	}
	int merge(int l, int r) {
		if (!l || !r) return l | r;
		if (adj[l].pr > adj[r].pr) {
			adj[l].r = merge(adj[l].r, r);
			return recalsiz(l), l;
		} else {
			adj[r].l = merge(l, adj[r].l);
			return recalsiz(r), r;
		}
	}
	int insert(int rt, int x, int pos) {
		auto [l,r] = split(rt, pos);
		return merge(merge(l, x), r);
	}
	// Example application: move the range [l, r) to index k
	void move(int& rt, int l, int r, int k) {
		int a, b, c;
		tie(a,b) = split(rt, l); tie(b,c) = split(b, r - l);
		if (k <= l) rt = merge(insert(a, b, k), c);
		else rt = merge(a, insert(c, b, k - r));
	}
};
