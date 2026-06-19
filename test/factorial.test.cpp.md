---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/factrial.hpp
    title: math/factrial.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: math/modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/DPL/5/DPL_5_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/DPL/5/DPL_5_D
  bundledCode: "#line 1 \"test/factorial.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/DPL/5/DPL_5_D\"\
    \n\n#line 2 \"math/modint.hpp\"\n#include <iostream>\n#include <vector>\nusing\
    \ ll = long long;\nusing namespace std;\n\nconstexpr ll MOD = 1e9 + 7;\n\ntemplate<ll\
    \ Mod>\nstruct mod_int {\n  static const ll mod = Mod;\n  ll val;\n  mod_int(ll\
    \ sig = 0) { sig%=mod; if(sig<0) sig+=mod; val = sig; }\n\n  constexpr mod_int\
    \ operator- () const {return val?mod-val:0;}\n  constexpr mod_int &operator+=(const\
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
    \ vector<mod_int> fact, infact;\n};\nusing mint = mod_int<MOD>;\n\n#line 3 \"\
    math/factrial.hpp\"\nusing namespace std;\n\ntemplate<typename T>\nstruct factrial{\n\
    \  int sz_f=1, sz_i=1;\n  vector<T> m_fact = {1};\n  vector<T> m_infact = {1};\n\
    \n  void update_fact(int n){\n    if(sz_f > n) return;\n    m_fact.resize(n+1,\
    \ 1);\n    for(int i = sz_f; i<n+1; ++i){\n      m_fact[i] = m_fact[i-1] * i;\n\
    \    }\n    sz_f = n+1;\n  }\n  void update_infact(int n){\n    if(sz_i > n) return;\n\
    \    m_infact.resize(n+1, 1);\n    for(int i = sz_i; i<n+1; ++i){\n      m_infact[i]\
    \ = m_infact[i-1] / i;\n    }\n    sz_i = n+1;\n  }\n\n  // n!\u3092\u6C42\u3081\
    \u308B\n  T fact(int n){\n    update_fact(n);\n    return m_fact[n];\n  }\n  //\
    \ (1/n!)\u3092\u6C42\u3081\u308B\u3002\n  T infact(int n){\n    update_infact(n);\n\
    \    return m_infact[n];\n  }\n  // nPk\u3092\u6C42\u3081\u308B\u3002\n  T perm(int\
    \ n, int k){\n    if(n < k) return 0;\n    return fact(n) * infact(n-k);\n  }\n\
    \  // nCk\u3092\u6C42\u3081\u308B\u3002\n  T comb(int n, int k){\n    if(n < k)\
    \ return 0;\n    return perm(n,k) * infact(k);\n  }\n  // nHk\u3092\u6C42\u3081\
    \u308B\u3002\n  T comb_rep(int n, int k){\n    return comb(n+k-1, k);\n  }\n};\n\
    \n// usage:\n// factrial<mint> fc();\n// fc.fact(10); // 10!\u3092\u8A08\u7B97\
    \u3059\u308B\u3002\n// fc.comb(10,3); // 10C3\u3092\u8A08\u7B97\u3059\u308B\u3002\
    \n#line 6 \"test/factorial.test.cpp\"\n\nusing namespace std;\n\nint main() {\n\
    \    int n, k;\n    if (!(cin >> n >> k)) return 0;\n\n    // modint (10^9+7)\
    \ \u3092\u4F7F\u3063\u3066\u968E\u4E57\u30FB\u7D44\u5408\u305B\u30E9\u30A4\u30D6\
    \u30E9\u30EA\u3092\u521D\u671F\u5316\n    factrial<mint> fc;\n\n    // n\u500B\
    \u306E\u533A\u5225\u3067\u304D\u306A\u3044\u30DC\u30FC\u30EB\u3092 k\u500B\u306E\
    \u533A\u5225\u3067\u304D\u308B\u7BB1\u306B\u5165\u308C\u308B\u65B9\u6CD5\u306E\
    \u6570 = k H n (\u91CD\u8907\u7D44\u5408\u305B)\n    cout << fc.comb_rep(k, n)\
    \ << endl;\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/DPL/5/DPL_5_D\"\
    \n\n#include \"../math/modint.hpp\"\n#include \"../math/factrial.hpp\"\n#include\
    \ <iostream>\n\nusing namespace std;\n\nint main() {\n    int n, k;\n    if (!(cin\
    \ >> n >> k)) return 0;\n\n    // modint (10^9+7) \u3092\u4F7F\u3063\u3066\u968E\
    \u4E57\u30FB\u7D44\u5408\u305B\u30E9\u30A4\u30D6\u30E9\u30EA\u3092\u521D\u671F\
    \u5316\n    factrial<mint> fc;\n\n    // n\u500B\u306E\u533A\u5225\u3067\u304D\
    \u306A\u3044\u30DC\u30FC\u30EB\u3092 k\u500B\u306E\u533A\u5225\u3067\u304D\u308B\
    \u7BB1\u306B\u5165\u308C\u308B\u65B9\u6CD5\u306E\u6570 = k H n (\u91CD\u8907\u7D44\
    \u5408\u305B)\n    cout << fc.comb_rep(k, n) << endl;\n\n    return 0;\n}\n"
  dependsOn:
  - math/modint.hpp
  - math/factrial.hpp
  isVerificationFile: true
  path: test/factorial.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 04:01:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/factorial.test.cpp
layout: document
redirect_from:
- /verify/test/factorial.test.cpp
- /verify/test/factorial.test.cpp.html
title: test/factorial.test.cpp
---
