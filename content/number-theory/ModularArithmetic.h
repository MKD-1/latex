/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"

constexpr ll MOD = 17; // change to something else
struct Mod {    
  ll x;    
  Mod(ll _x) : x((_x % MOD + MOD) % MOD) {}    
  Mod operator+(Mod b) { return Mod(((x + b.x) % MOD + MOD) % MOD); }
  Mod operator-(Mod b) { return Mod(((x - b.x) % MOD + MOD) % MOD); }
  Mod operator*(Mod b) { return Mod((x * b.x % MOD + MOD) % MOD); }
	Mod operator/(Mod b) { return *this * invert(b); }    
	Mod invert(Mod a) {    
    ll x, y, g = euclid(a.x, MOD, x, y);    
    assert(g == 1);return Mod((x % MOD + MOD) % MOD);    
  }    
  Mod operator^(ll e) {    
    if (!e) return Mod(1);    
    Mod r = *this ^ (e / 2); r = r * r;    
    return e & 1 ? *this * r : r;    
  }    
};
