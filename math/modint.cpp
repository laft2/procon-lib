#include <iostream>
#include <vector>
using ll = long long;
using namespace std;

constexpr ll MOD = 1e9 + 7;

template<ll Mod>
struct mod_int {
  static const ll mod = Mod;
  ll val;
  mod_int(ll sig = 0) { sig%=mod; if(sig<0) sig+=mod; val = sig; }

  constexpr mod_int operator- () const {return val?mod-val:0;}
  constexpr mod_int &operator+=(const mod_int &that) { if ((val += that.val) >= mod) val -= mod; return *this; }
  constexpr mod_int &operator-=(const mod_int &that) { if ((val += mod - that.val) >= mod) val -= mod; return *this; }
  constexpr mod_int &operator*=(const mod_int &that) { val = (unsigned long long)val * that.val % mod; return *this; }
  constexpr mod_int &operator/= (const mod_int& r) noexcept {
    ll a = r.val, b = Mod, u = 1, v = 0;
    while (b) { ll t = a / b; a -= t * b; swap(a, b); u -= t * v; swap(u, v); }
    val = val * u % Mod; if (val < 0) val += Mod;
    return *this;
  }
  constexpr mod_int operator+(const mod_int &that) const { return mod_int(*this) += that; }
  constexpr mod_int operator-(const mod_int &that) const { return mod_int(*this) -= that; }
  constexpr mod_int operator*(const mod_int &that) const { return mod_int(*this) *= that; }
  constexpr mod_int operator/(const mod_int &that) const { return mod_int(*this) /= that; }
  constexpr bool operator==(const mod_int &that) const noexcept{ return this->val == that.val; }
  constexpr bool operator!=(const mod_int &that) const noexcept{ return this->val != that.val; }
  friend constexpr ostream& operator << (ostream &os, const mod_int &x) noexcept { return os << x.val; }
  friend constexpr istream& operator >> (istream &is, mod_int& x) noexcept { return is >> x.val; }

  friend mod_int power(const mod_int &a, long long n) noexcept {
    mod_int res = 1, r = a; for(;n>0;n>>=1,r*=r) res*=(n&1?r:1); return res;
  }
  static int sz;
  static vector<mod_int> fact, infact;
};
using mint = mod_int<MOD>;

