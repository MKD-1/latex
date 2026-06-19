uint64_t seed = chrono::steady_clock::now()
	.time_since_epoch().count() ^ random_device{}();
mt19937 rng(seed);
template<class T>
T randi(T l,T r){return uniform_int_distribution<T>(l,r)(rng);}
vi randvi(int n, int l, int r) {
	vi v(n);
	rep(i, 0, sz(v))v[i] = randi(l, r);
	return v;
}
vi randp(int n) {
	vi p(n);
	iota(all(p), 1);
	shuffle(all(p), rng);
	return p;
}
int main(int argc, char *argv[]) {
	if (argc >= 2)
		seed = stoull(argv[1]), rng.seed(seed);
	cerr << seed << endl;
	return 0;
}
