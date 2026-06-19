#define dbg(...) cerr<<"DEBUG:["<<#__VA_ARGS__<<"] = [",\
    _print(__VA_ARGS__),cerr<<"]\n"
template<class T, class=void>struct cntr : false_type {};
template<class T>struct cntr<T,
		void_t<decltype(declval<T>().begin()),
		decltype(declval<T>().end()),
    typename T::value_type> > : true_type {};
template<class T>using raw=remove_cv_t<remove_reference_t<T> >;
template<class T>enable_if_t<!cntr<T>::value>
    _print(const T &x) { cerr << x; }
template<class T>enable_if_t<cntr<T>::value>_print(const T &v){
    cerr << "["; bool f = false;
    for (const auto &x: v)
      f ? cerr << (cntr<raw<decltype(x)> >::value ?",\n":", "):
		    cerr, f = true, _print(x);
    cerr << "]";
}
template<class T, class... A>
void _print(const T &x, const A &... a) {
    _print(x);((cerr << ", ", _print(a)), ...);}
		