#pragma once
#include <iostream>
#include <vector>
using ll = long long;
using namespace std;

template <ll Mod> struct modint {
  static const ll mod = Mod;
  ll val;
  modint(ll sig = 0) {
    sig %= mod;
    if (sig < 0)
      sig += mod;
    val = sig;
  }

  constexpr modint operator-() const { return val ? mod - val : 0; }
  constexpr modint &operator+=(const modint &that) {
    if ((val += that.val) >= mod)
      val -= mod;
    return *this;
  }
  constexpr modint &operator-=(const modint &that) {
    if ((val += mod - that.val) >= mod)
      val -= mod;
    return *this;
  }
  constexpr modint &operator*=(const modint &that) {
    val = (unsigned long long)val * that.val % mod;
    return *this;
  }
  constexpr modint &operator/=(const modint &r) noexcept {
    ll a = r.val, b = Mod, u = 1, v = 0;
    while (b) {
      ll t = a / b;
      a -= t * b;
      swap(a, b);
      u -= t * v;
      swap(u, v);
    }
    val = val * u % Mod;
    if (val < 0)
      val += Mod;
    return *this;
  }
  constexpr modint operator+(const modint &that) const {
    return modint(*this) += that;
  }
  constexpr modint operator-(const modint &that) const {
    return modint(*this) -= that;
  }
  constexpr modint operator*(const modint &that) const {
    return modint(*this) *= that;
  }
  constexpr modint operator/(const modint &that) const {
    return modint(*this) /= that;
  }
  constexpr bool operator==(const modint &that) const noexcept {
    return this->val == that.val;
  }
  constexpr bool operator!=(const modint &that) const noexcept {
    return this->val != that.val;
  }
  friend constexpr ostream &operator<<(ostream &os, const modint &x) noexcept {
    return os << x.val;
  }
  friend constexpr istream &operator>>(istream &is, modint &x) noexcept {
    return is >> x.val;
  }

  friend modint power(const modint &a, long long n) noexcept {
    modint res = 1, r = a;
    for (; n > 0; n >>= 1, r *= r)
      res *= (n & 1 ? r : 1);
    return res;
  }
  static int sz;
};

using modint1000000007 = modint<1000000007>;
using modint998244353 = modint<998244353>;
