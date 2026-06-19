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
  bundledCode: "#line 2 \"math/factrial.hpp\"\n#include<vector>\nusing namespace std;\n\
    \ntemplate<typename T>\nstruct factrial{\n  int sz_f=1, sz_i=1;\n  vector<T> m_fact\
    \ = {1};\n  vector<T> m_infact = {1};\n\n  void update_fact(int n){\n    if(sz_f\
    \ > n) return;\n    m_fact.resize(n+1, 1);\n    for(int i = sz_f; i<n+1; ++i){\n\
    \      m_fact[i] = m_fact[i-1] * i;\n    }\n    sz_f = n+1;\n  }\n  void update_infact(int\
    \ n){\n    if(sz_i > n) return;\n    m_infact.resize(n+1, 1);\n    for(int i =\
    \ sz_i; i<n+1; ++i){\n      m_infact[i] = m_infact[i-1] / i;\n    }\n    sz_i\
    \ = n+1;\n  }\n\n  // n!\u3092\u6C42\u3081\u308B\n  T fact(int n){\n    update_fact(n);\n\
    \    return m_fact[n];\n  }\n  // (1/n!)\u3092\u6C42\u3081\u308B\u3002\n  T infact(int\
    \ n){\n    update_infact(n);\n    return m_infact[n];\n  }\n  // nPk\u3092\u6C42\
    \u3081\u308B\u3002\n  T perm(int n, int k){\n    if(n < k) return 0;\n    return\
    \ fact(n) * infact(n-k);\n  }\n  // nCk\u3092\u6C42\u3081\u308B\u3002\n  T comb(int\
    \ n, int k){\n    if(n < k) return 0;\n    return perm(n,k) * infact(k);\n  }\n\
    \  // nHk\u3092\u6C42\u3081\u308B\u3002\n  T comb_rep(int n, int k){\n    return\
    \ comb(n+k-1, k);\n  }\n};\n\n// usage:\n// factrial<mint> fc();\n// fc.fact(10);\
    \ // 10!\u3092\u8A08\u7B97\u3059\u308B\u3002\n// fc.comb(10,3); // 10C3\u3092\u8A08\
    \u7B97\u3059\u308B\u3002\n"
  code: "#pragma once\n#include<vector>\nusing namespace std;\n\ntemplate<typename\
    \ T>\nstruct factrial{\n  int sz_f=1, sz_i=1;\n  vector<T> m_fact = {1};\n  vector<T>\
    \ m_infact = {1};\n\n  void update_fact(int n){\n    if(sz_f > n) return;\n  \
    \  m_fact.resize(n+1, 1);\n    for(int i = sz_f; i<n+1; ++i){\n      m_fact[i]\
    \ = m_fact[i-1] * i;\n    }\n    sz_f = n+1;\n  }\n  void update_infact(int n){\n\
    \    if(sz_i > n) return;\n    m_infact.resize(n+1, 1);\n    for(int i = sz_i;\
    \ i<n+1; ++i){\n      m_infact[i] = m_infact[i-1] / i;\n    }\n    sz_i = n+1;\n\
    \  }\n\n  // n!\u3092\u6C42\u3081\u308B\n  T fact(int n){\n    update_fact(n);\n\
    \    return m_fact[n];\n  }\n  // (1/n!)\u3092\u6C42\u3081\u308B\u3002\n  T infact(int\
    \ n){\n    update_infact(n);\n    return m_infact[n];\n  }\n  // nPk\u3092\u6C42\
    \u3081\u308B\u3002\n  T perm(int n, int k){\n    if(n < k) return 0;\n    return\
    \ fact(n) * infact(n-k);\n  }\n  // nCk\u3092\u6C42\u3081\u308B\u3002\n  T comb(int\
    \ n, int k){\n    if(n < k) return 0;\n    return perm(n,k) * infact(k);\n  }\n\
    \  // nHk\u3092\u6C42\u3081\u308B\u3002\n  T comb_rep(int n, int k){\n    return\
    \ comb(n+k-1, k);\n  }\n};\n\n// usage:\n// factrial<mint> fc();\n// fc.fact(10);\
    \ // 10!\u3092\u8A08\u7B97\u3059\u308B\u3002\n// fc.comb(10,3); // 10C3\u3092\u8A08\
    \u7B97\u3059\u308B\u3002"
  dependsOn: []
  isVerificationFile: false
  path: math/factrial.hpp
  requiredBy: []
  timestamp: '2026-06-20 04:01:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/factorial.test.cpp
documentation_of: math/factrial.hpp
layout: document
redirect_from:
- /library/math/factrial.hpp
- /library/math/factrial.hpp.html
title: math/factrial.hpp
---
