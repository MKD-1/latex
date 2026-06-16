#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll mod_pow(ll a, ll b, ll mod) {
    a %= mod;
    if (a < 0) a += mod;

    ll res = 1 % mod;
    while (b > 0) {
        if (b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}
