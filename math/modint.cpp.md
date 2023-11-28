---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/modint.cpp\"\n#include <iostream>\n#include <vector>\n\
    using ll = long long;\nusing namespace std;\n\nconstexpr ll MOD = 1e9 + 7;\n\n\
    template<ll Mod>\nstruct mod_int {\n  static const ll mod = Mod;\n  ll val;\n\
    \  mod_int(ll sig = 0) { sig%=mod; if(sig<0) sig+=mod; val = sig; }\n\n  constexpr\
    \ mod_int operator- () const {return val?mod-val:0;}\n  constexpr mod_int &operator+=(const\
    \ mod_int &that) { if ((val += that.val) >= mod) val -= mod; return *this; }\n\
    \  constexpr mod_int &operator-=(const mod_int &that) { if ((val += mod - that.val)\
    \ >= mod) val -= mod; return *this; }\n  constexpr mod_int &operator*=(const mod_int\
    \ &that) { val = (unsigned long long)val * that.val % mod; return *this; }\n \
    \ constexpr mod_int &operator/= (const mod_int& r) noexcept {\n    ll a = r.val,\
    \ b = Mod, u = 1, v = 0;\n    while (b) { ll t = a / b; a -= t * b; swap(a, b);\
    \ u -= t * v; swap(u, v); }\n    val = val * u % Mod; if (val < 0) val += Mod;\n\
    \    return *this;\n  }\n  constexpr mod_int operator+(const mod_int &that) const\
    \ { return mod_int(*this) += that; }\n  constexpr mod_int operator-(const mod_int\
    \ &that) const { return mod_int(*this) -= that; }\n  constexpr mod_int operator*(const\
    \ mod_int &that) const { return mod_int(*this) *= that; }\n  constexpr mod_int\
    \ operator/(const mod_int &that) const { return mod_int(*this) /= that; }\n  constexpr\
    \ bool operator==(const mod_int &that) const noexcept{ return this->val == that.val;\
    \ }\n  constexpr bool operator!=(const mod_int &that) const noexcept{ return this->val\
    \ != that.val; }\n  friend constexpr ostream& operator << (ostream &os, const\
    \ mod_int &x) noexcept { return os << x.val; }\n  friend constexpr istream& operator\
    \ >> (istream &is, mod_int& x) noexcept { return is >> x.val; }\n\n  friend mod_int\
    \ power(const mod_int &a, long long n) noexcept {\n    mod_int res = 1, r = a;\
    \ for(;n>0;n>>=1,r*=r) res*=(n&1?r:1); return res;\n  }\n  static int sz;\n  static\
    \ vector<mod_int> fact, infact;\n};\nusing mint = mod_int<MOD>;\n\n"
  code: "#include <iostream>\n#include <vector>\nusing ll = long long;\nusing namespace\
    \ std;\n\nconstexpr ll MOD = 1e9 + 7;\n\ntemplate<ll Mod>\nstruct mod_int {\n\
    \  static const ll mod = Mod;\n  ll val;\n  mod_int(ll sig = 0) { sig%=mod; if(sig<0)\
    \ sig+=mod; val = sig; }\n\n  constexpr mod_int operator- () const {return val?mod-val:0;}\n\
    \  constexpr mod_int &operator+=(const mod_int &that) { if ((val += that.val)\
    \ >= mod) val -= mod; return *this; }\n  constexpr mod_int &operator-=(const mod_int\
    \ &that) { if ((val += mod - that.val) >= mod) val -= mod; return *this; }\n \
    \ constexpr mod_int &operator*=(const mod_int &that) { val = (unsigned long long)val\
    \ * that.val % mod; return *this; }\n  constexpr mod_int &operator/= (const mod_int&\
    \ r) noexcept {\n    ll a = r.val, b = Mod, u = 1, v = 0;\n    while (b) { ll\
    \ t = a / b; a -= t * b; swap(a, b); u -= t * v; swap(u, v); }\n    val = val\
    \ * u % Mod; if (val < 0) val += Mod;\n    return *this;\n  }\n  constexpr mod_int\
    \ operator+(const mod_int &that) const { return mod_int(*this) += that; }\n  constexpr\
    \ mod_int operator-(const mod_int &that) const { return mod_int(*this) -= that;\
    \ }\n  constexpr mod_int operator*(const mod_int &that) const { return mod_int(*this)\
    \ *= that; }\n  constexpr mod_int operator/(const mod_int &that) const { return\
    \ mod_int(*this) /= that; }\n  constexpr bool operator==(const mod_int &that)\
    \ const noexcept{ return this->val == that.val; }\n  constexpr bool operator!=(const\
    \ mod_int &that) const noexcept{ return this->val != that.val; }\n  friend constexpr\
    \ ostream& operator << (ostream &os, const mod_int &x) noexcept { return os <<\
    \ x.val; }\n  friend constexpr istream& operator >> (istream &is, mod_int& x)\
    \ noexcept { return is >> x.val; }\n\n  friend mod_int power(const mod_int &a,\
    \ long long n) noexcept {\n    mod_int res = 1, r = a; for(;n>0;n>>=1,r*=r) res*=(n&1?r:1);\
    \ return res;\n  }\n  static int sz;\n  static vector<mod_int> fact, infact;\n\
    };\nusing mint = mod_int<MOD>;\n\n"
  dependsOn: []
  isVerificationFile: false
  path: math/modint.cpp
  requiredBy: []
  timestamp: '2023-11-29 04:11:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/modint.cpp
layout: document
redirect_from:
- /library/math/modint.cpp
- /library/math/modint.cpp.html
title: math/modint.cpp
---
