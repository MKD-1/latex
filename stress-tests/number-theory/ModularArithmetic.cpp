#include "../utilities/template.h"

#include "../../content/number-theory/ModularArithmetic.h"

int main() {
	rep(a,0,MOD) rep(b,1,MOD) {
		Mod ma(a);
		Mod mb(b);
		Mod mc = ma / mb;
		assert((mc * mb).x == a);
	}
	Mod a = 2;
	ll cur=1;
	rep(i, 0, MOD) {
		assert((a ^ i).x == cur);
		cur = (cur * 2) % MOD;
		// cout << i << ": " << (a ^ i).x << endl;
	}
	cout<<"Tests passed!"<<endl;
}
