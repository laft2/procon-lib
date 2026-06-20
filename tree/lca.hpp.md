---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lca.test.cpp
    title: test/lca.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/lca.hpp\"\n#include <vector>\n\nusing namespace std;\n\
    struct lowest_common_ancestor {\n  const vector<vector<int>> graph;\n  const int\
    \ sz, width;\n  vector<int> depth;\n  vector<vector<int>> par_table;\n  int root;\n\
    \n  lowest_common_ancestor(const vector<vector<int>> &graph, int root = 0)\n \
    \     : graph(graph), sz(graph.size()), width(32 - __builtin_clz(graph.size())),\n\
    \        depth(graph.size()), par_table(width, vector<int>(graph.size(), -1)),\n\
    \        root(root) {\n    build();\n  }\n\n  void dfs(int cur, int par = -1,\
    \ int d = 0) {\n    par_table[0][cur] = par;\n    depth[cur] = d;\n    for (auto\
    \ &&e : graph[cur])\n      if (e != par) {\n        dfs(e, cur, d + 1);\n    \
    \  }\n  }\n  void build() {\n    dfs(root);\n    for (int k = 0; k < width - 1;\
    \ ++k)\n      for (int i = 0; i < sz; ++i) {\n        if (par_table[k][i] == -1)\n\
    \          par_table[k + 1][i] = -1;\n        else\n          par_table[k + 1][i]\
    \ = par_table[k][par_table[k][i]];\n      }\n  }\n  int query(int u, int v) {\n\
    \    if (depth[u] > depth[v])\n      swap(u, v);\n    for (int i = width - 1;\
    \ i >= 0; --i) {\n      if ((depth[v] - depth[u]) >> i & 1)\n        v = par_table[i][v];\n\
    \    }\n    if (u == v)\n      return u;\n    for (int i = width - 1; i >= 0;\
    \ --i) {\n      if (par_table[i][u] != par_table[i][v]) {\n        u = par_table[i][u];\n\
    \        v = par_table[i][v];\n      }\n    }\n    return par_table[0][u];\n \
    \ }\n};\n"
  code: "#include <vector>\n\nusing namespace std;\nstruct lowest_common_ancestor\
    \ {\n  const vector<vector<int>> graph;\n  const int sz, width;\n  vector<int>\
    \ depth;\n  vector<vector<int>> par_table;\n  int root;\n\n  lowest_common_ancestor(const\
    \ vector<vector<int>> &graph, int root = 0)\n      : graph(graph), sz(graph.size()),\
    \ width(32 - __builtin_clz(graph.size())),\n        depth(graph.size()), par_table(width,\
    \ vector<int>(graph.size(), -1)),\n        root(root) {\n    build();\n  }\n\n\
    \  void dfs(int cur, int par = -1, int d = 0) {\n    par_table[0][cur] = par;\n\
    \    depth[cur] = d;\n    for (auto &&e : graph[cur])\n      if (e != par) {\n\
    \        dfs(e, cur, d + 1);\n      }\n  }\n  void build() {\n    dfs(root);\n\
    \    for (int k = 0; k < width - 1; ++k)\n      for (int i = 0; i < sz; ++i) {\n\
    \        if (par_table[k][i] == -1)\n          par_table[k + 1][i] = -1;\n   \
    \     else\n          par_table[k + 1][i] = par_table[k][par_table[k][i]];\n \
    \     }\n  }\n  int query(int u, int v) {\n    if (depth[u] > depth[v])\n    \
    \  swap(u, v);\n    for (int i = width - 1; i >= 0; --i) {\n      if ((depth[v]\
    \ - depth[u]) >> i & 1)\n        v = par_table[i][v];\n    }\n    if (u == v)\n\
    \      return u;\n    for (int i = width - 1; i >= 0; --i) {\n      if (par_table[i][u]\
    \ != par_table[i][v]) {\n        u = par_table[i][u];\n        v = par_table[i][v];\n\
    \      }\n    }\n    return par_table[0][u];\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: tree/lca.hpp
  requiredBy: []
  timestamp: '2026-06-21 01:37:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lca.test.cpp
documentation_of: tree/lca.hpp
layout: document
redirect_from:
- /library/tree/lca.hpp
- /library/tree/lca.hpp.html
title: tree/lca.hpp
---
