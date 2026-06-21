---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/factorial.test.cpp
    title: test/factorial.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"math/modint.hpp\"\n#include <iostream>\n#include <utility>\n\
    \ntemplate <long long Mod> struct modint {\n  using ll = long long;\n  static\
    \ const ll mod = Mod;\n  ll val;\n  modint(ll sig = 0) {\n    sig %= mod;\n  \
    \  if (sig < 0)\n      sig += mod;\n    val = sig;\n  }\n\n  constexpr modint\
    \ operator-() const { return val ? mod - val : 0; }\n  constexpr modint &operator+=(const\
    \ modint &that) {\n    if ((val += that.val) >= mod)\n      val -= mod;\n    return\
    \ *this;\n  }\n  constexpr modint &operator-=(const modint &that) {\n    if ((val\
    \ += mod - that.val) >= mod)\n      val -= mod;\n    return *this;\n  }\n  constexpr\
    \ modint &operator*=(const modint &that) {\n    val = (unsigned long long)val\
    \ * that.val % mod;\n    return *this;\n  }\n  constexpr modint &operator/=(const\
    \ modint &r) noexcept {\n    ll a = r.val, b = Mod, u = 1, v = 0;\n    while (b)\
    \ {\n      ll t = a / b;\n      a -= t * b;\n      std::swap(a, b);\n      u -=\
    \ t * v;\n      std::swap(u, v);\n    }\n    val = val * u % Mod;\n    if (val\
    \ < 0)\n      val += Mod;\n    return *this;\n  }\n  constexpr modint operator+(const\
    \ modint &that) const {\n    return modint(*this) += that;\n  }\n  constexpr modint\
    \ operator-(const modint &that) const {\n    return modint(*this) -= that;\n \
    \ }\n  constexpr modint operator*(const modint &that) const {\n    return modint(*this)\
    \ *= that;\n  }\n  constexpr modint operator/(const modint &that) const {\n  \
    \  return modint(*this) /= that;\n  }\n  constexpr bool operator==(const modint\
    \ &that) const noexcept {\n    return this->val == that.val;\n  }\n  constexpr\
    \ bool operator!=(const modint &that) const noexcept {\n    return this->val !=\
    \ that.val;\n  }\n  friend constexpr std::ostream &operator<<(std::ostream &os,\
    \ const modint &x) noexcept {\n    return os << x.val;\n  }\n  friend constexpr\
    \ std::istream &operator>>(std::istream &is, modint &x) noexcept {\n    return\
    \ is >> x.val;\n  }\n\n  friend modint power(const modint &a, long long n) noexcept\
    \ {\n    modint res = 1, r = a;\n    for (; n > 0; n >>= 1, r *= r)\n      res\
    \ *= (n & 1 ? r : 1);\n    return res;\n  }\n};\n\nusing modint1000000007 = modint<1000000007>;\n\
    using modint998244353 = modint<998244353>;\n"
  code: "#pragma once\n#include <iostream>\n#include <utility>\n\ntemplate <long long\
    \ Mod> struct modint {\n  using ll = long long;\n  static const ll mod = Mod;\n\
    \  ll val;\n  modint(ll sig = 0) {\n    sig %= mod;\n    if (sig < 0)\n      sig\
    \ += mod;\n    val = sig;\n  }\n\n  constexpr modint operator-() const { return\
    \ val ? mod - val : 0; }\n  constexpr modint &operator+=(const modint &that) {\n\
    \    if ((val += that.val) >= mod)\n      val -= mod;\n    return *this;\n  }\n\
    \  constexpr modint &operator-=(const modint &that) {\n    if ((val += mod - that.val)\
    \ >= mod)\n      val -= mod;\n    return *this;\n  }\n  constexpr modint &operator*=(const\
    \ modint &that) {\n    val = (unsigned long long)val * that.val % mod;\n    return\
    \ *this;\n  }\n  constexpr modint &operator/=(const modint &r) noexcept {\n  \
    \  ll a = r.val, b = Mod, u = 1, v = 0;\n    while (b) {\n      ll t = a / b;\n\
    \      a -= t * b;\n      std::swap(a, b);\n      u -= t * v;\n      std::swap(u,\
    \ v);\n    }\n    val = val * u % Mod;\n    if (val < 0)\n      val += Mod;\n\
    \    return *this;\n  }\n  constexpr modint operator+(const modint &that) const\
    \ {\n    return modint(*this) += that;\n  }\n  constexpr modint operator-(const\
    \ modint &that) const {\n    return modint(*this) -= that;\n  }\n  constexpr modint\
    \ operator*(const modint &that) const {\n    return modint(*this) *= that;\n \
    \ }\n  constexpr modint operator/(const modint &that) const {\n    return modint(*this)\
    \ /= that;\n  }\n  constexpr bool operator==(const modint &that) const noexcept\
    \ {\n    return this->val == that.val;\n  }\n  constexpr bool operator!=(const\
    \ modint &that) const noexcept {\n    return this->val != that.val;\n  }\n  friend\
    \ constexpr std::ostream &operator<<(std::ostream &os, const modint &x) noexcept\
    \ {\n    return os << x.val;\n  }\n  friend constexpr std::istream &operator>>(std::istream\
    \ &is, modint &x) noexcept {\n    return is >> x.val;\n  }\n\n  friend modint\
    \ power(const modint &a, long long n) noexcept {\n    modint res = 1, r = a;\n\
    \    for (; n > 0; n >>= 1, r *= r)\n      res *= (n & 1 ? r : 1);\n    return\
    \ res;\n  }\n};\n\nusing modint1000000007 = modint<1000000007>;\nusing modint998244353\
    \ = modint<998244353>;\n"
  dependsOn: []
  isVerificationFile: false
  path: math/modint.hpp
  requiredBy: []
  timestamp: '2026-06-21 13:05:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/factorial.test.cpp
documentation_of: math/modint.hpp
layout: document
redirect_from:
- /library/math/modint.hpp
- /library/math/modint.hpp.html
title: math/modint.hpp
---
