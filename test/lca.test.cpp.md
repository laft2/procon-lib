---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/lca.hpp
    title: tree/lca.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/lca.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\
    \n\n#line 1 \"tree/lca.hpp\"\n#include <vector>\n\nusing namespace std;\nstruct\
    \ lowest_common_ancestor {\n  const vector<vector<int>> graph;\n  const int sz,\
    \ width;\n  vector<int> depth;\n  vector<vector<int>> par_table;\n  int root;\n\
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
    \ }\n};\n#line 4 \"test/lca.test.cpp\"\n#include <iostream>\n\nusing namespace\
    \ std;\n\nint main() {\n  int n, q;\n  cin >> n >> q;\n  vector<int> p(n);\n \
    \ vector<vector<int>> graph(n);\n  for (int i = 0; i < n - 1; ++i) {\n    int\
    \ tmp;\n    cin >> tmp;\n    graph[i + 1].emplace_back(tmp);\n    graph[tmp].emplace_back(i\
    \ + 1);\n  }\n  auto lca = lowest_common_ancestor(graph, 0);\n  for (int i = 0;\
    \ i < q; ++i) {\n    int u, v;\n    cin >> u >> v;\n    cout << lca.query(u, v)\
    \ << '\\n';\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include \"../tree/lca.hpp\"\
    \n#include <iostream>\n\nusing namespace std;\n\nint main() {\n  int n, q;\n \
    \ cin >> n >> q;\n  vector<int> p(n);\n  vector<vector<int>> graph(n);\n  for\
    \ (int i = 0; i < n - 1; ++i) {\n    int tmp;\n    cin >> tmp;\n    graph[i +\
    \ 1].emplace_back(tmp);\n    graph[tmp].emplace_back(i + 1);\n  }\n  auto lca\
    \ = lowest_common_ancestor(graph, 0);\n  for (int i = 0; i < q; ++i) {\n    int\
    \ u, v;\n    cin >> u >> v;\n    cout << lca.query(u, v) << '\\n';\n  }\n}"
  dependsOn:
  - tree/lca.hpp
  isVerificationFile: true
  path: test/lca.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 01:37:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/lca.test.cpp
layout: document
redirect_from:
- /verify/test/lca.test.cpp
- /verify/test/lca.test.cpp.html
title: test/lca.test.cpp
---
