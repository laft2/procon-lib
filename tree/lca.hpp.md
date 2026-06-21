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
    document_title: "\u6700\u8FD1\u5171\u901A\u7956\u5148 (LCA: Lowest Common Ancestor)"
    links: []
  bundledCode: "#line 2 \"tree/lca.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n/**\n * @brief \u6700\u8FD1\u5171\u901A\
    \u7956\u5148 (LCA: Lowest Common Ancestor)\n * \u3092\u30C0\u30D6\u30EA\u30F3\u30B0\
    \u306B\u3088\u308A\u6C42\u3081\u308B\u69CB\u9020\u4F53\n *\n * \u4F7F\u7528\u65B9\
    \u6CD5:\n * 1. lowest_common_ancestor lca(n, root); \u3067\u521D\u671F\u5316\n\
    \ * 2. lca.add_edge(u, v); \u3067\u6728\u3092\u69CB\u7BC9 (\u7121\u5411\u8FBA\u304C\
    \u8FFD\u52A0\u3055\u308C\u307E\u3059)\n * 3. lca.build(); \u3092\u547C\u3073\u51FA\
    \u3057\u3066\u30C0\u30D6\u30EA\u30F3\u30B0\u30C6\u30FC\u30D6\u30EB\u3092\u69CB\
    \u7BC9 (\u203B\u5FC5\u9808)\n * 4. lca.lca(u, v) \u3084 lca.get_dist(u, v) \u3067\
    \u30AF\u30A8\u30EA\u3092\u51E6\u7406\n */\nstruct lowest_common_ancestor {\npublic:\n\
    \  int n;     // \u9802\u70B9\u6570\n  int log_n; // \u30C0\u30D6\u30EA\u30F3\u30B0\
    \u30C6\u30FC\u30D6\u30EB\u306E\u6700\u5927\u4E57\u6570 (log2(n) \u7A0B\u5EA6)\n\
    \  std::vector<std::vector<int>> graph; // \u5185\u90E8\u3067\u4FDD\u6301\u3059\
    \u308B\u96A3\u63A5\u30EA\u30B9\u30C8\n  std::vector<int> depth;              //\
    \ \u5404\u9802\u70B9\u306E\u6DF1\u3055\uFF08\u6839\u304B\u3089\u306E\u8DDD\u96E2\
    \uFF09\n  std::vector<std::vector<int>>\n      parent; // parent[k][v]: \u9802\
    \u70B9 v \u306E 2^k\n              // \u500B\u4E0A\u306E\u89AA\u306E\u9802\u70B9\
    \u756A\u53F7\uFF08\u5B58\u5728\u3057\u306A\u3044\u5834\u5408\u306F -1\uFF09\n\n\
    \  /**\n   * @brief \u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n   * @param n\
    \ \u9802\u70B9\u6570\n   */\n  lowest_common_ancestor(int n)\n      : n(n), log_n(32\
    \ - __builtin_clz(n)), graph(n), depth(n),\n        parent(log_n, std::vector<int>(n,\
    \ -1)) {}\n\n  /**\n   * @brief \u6728\u306B\u7121\u5411\u8FBA\u3092\u8FFD\u52A0\
    \u3059\u308B\n   * @param u \u9802\u70B9\u756A\u53F7\n   * @param v \u9802\u70B9\
    \u756A\u53F7\n   */\n  void add_edge(int u, int v) {\n    assert(0 <= u && u <\
    \ n);\n    assert(0 <= v && v < n);\n    graph[u].push_back(v);\n    graph[v].push_back(u);\n\
    \  }\n\n  /**\n   * @brief \u30C6\u30FC\u30D6\u30EB\u3092\u69CB\u7BC9\u3059\u308B\
    \ (\u8FBA\u3092\u3059\u3079\u3066\u8FFD\u52A0\u3057\u305F\u5F8C\u306B\u5FC5\u305A\
    1\u56DE\u547C\u3073\u51FA\u3057\u3066\u304F\u3060\u3055\u3044)\n   * @param root\
    \ \u6728\u306E\u6839\u306E\u756A\u53F7 (\u30C7\u30D5\u30A9\u30EB\u30C8\u306F 0)\n\
    \   */\n  void build(int root = 0) {\n    // DFS\u3067\u76F4\u8FD1\u306E\u89AA\
    (2^0 = 1\u500B\u4E0A)\u3068\u5404\u9802\u70B9\u306E\u6DF1\u3055\u3092\u6C42\u3081\
    \u308B\n    dfs(root);\n    // \u30C0\u30D6\u30EA\u30F3\u30B0\u30C6\u30FC\u30D6\
    \u30EB\u306E\u69CB\u7BC9\n    for (int k = 0; k < log_n - 1; ++k) {\n      for\
    \ (int i = 0; i < n; ++i) {\n        if (parent[k][i] == -1) {\n          parent[k\
    \ + 1][i] = -1;\n        } else {\n          parent[k + 1][i] = parent[k][parent[k][i]];\n\
    \        }\n      }\n    }\n  }\n\n  /**\n   * @brief \u9802\u70B9 u \u3068 v\
    \ \u306E\u6700\u8FD1\u5171\u901A\u7956\u5148 (LCA) \u3092\u53D6\u5F97\u3059\u308B\
    \n   * @param u \u9802\u70B9\u756A\u53F7\n   * @param v \u9802\u70B9\u756A\u53F7\
    \n   * @return LCA\u3068\u306A\u308B\u9802\u70B9\u306E\u756A\u53F7\n   */\n  int\
    \ lca(int u, int v) const {\n    // u \u3068 v \u306E\u6DF1\u3055\u3092\u63C3\u3048\
    \u308B\uFF08\u5E38\u306B v \u306E\u65B9\u304C\u6DF1\u304F\u306A\u308B\u3088\u3046\
    \u306B\u3059\u308B\uFF09\n    if (depth[u] > depth[v]) {\n      std::swap(u, v);\n\
    \    }\n    for (int i = log_n - 1; i >= 0; --i) {\n      if (((depth[v] - depth[u])\
    \ >> i) & 1) {\n        v = parent[i][v];\n      }\n    }\n    if (u == v) {\n\
    \      return u;\n    }\n    // 2\u51AA\u3092\u4E0A\u304B\u3089\u964D\u308A\u3064\
    \u3064\u3001\u5171\u901A\u7956\u5148\u3092\u6301\u305F\u306A\u3044\uFF08\u89AA\
    \u304C\u7570\u306A\u308B\uFF09\u5834\u5408\u306F\u5373\u5EA7\u306B\u305D\u306E\
    \u6DF1\u3055\u307E\u3067\u79FB\u52D5\u3059\u308B\n    // \uFF08LCA\u5224\u5B9A\
    \u3092\u611A\u76F4\u306B\u4E8C\u5206\u63A2\u7D22\u3059\u308B\u3068 O(log^2 N)\
    \ \u304B\u304B\u308B\u304C\u3001\u3053\u306E\u65B9\u6CD5\u306B\u3088\u308A O(log\n\
    \    // N) \u3067LCA\u306E\u76F4\u524D\u307E\u3067\u9061\u308C\u308B\uFF09\n \
    \   for (int i = log_n - 1; i >= 0; --i) {\n      if (parent[i][u] != parent[i][v])\
    \ {\n        u = parent[i][u];\n        v = parent[i][v];\n      }\n    }\n  \
    \  return parent[0][u];\n  }\n\n  /**\n   * @brief 2\u70B9 u, v \u9593\u306E\u6700\
    \u77ED\u30D1\u30B9\u4E0A\u306E\u8FBA\u306E\u6570\uFF08\u8DDD\u96E2\uFF09\u3092\
    \u53D6\u5F97\u3059\u308B\n   * @param u \u9802\u70B9\u756A\u53F7\n   * @param\
    \ v \u9802\u70B9\u756A\u53F7\n   * @return \u8DDD\u96E2\n   */\n  int get_dist(int\
    \ u, int v) const {\n    return depth[u] + depth[v] - 2 * depth[lca(u, v)];\n\
    \  }\n\nprivate:\n  void dfs(int cur, int par = -1, int d = 0) {\n    parent[0][cur]\
    \ = par;\n    depth[cur] = d;\n    for (int next_node : graph[cur]) {\n      if\
    \ (next_node != par) {\n        dfs(next_node, cur, d + 1);\n      }\n    }\n\
    \  }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n/**\n * @brief \u6700\u8FD1\u5171\u901A\u7956\u5148 (LCA:\
    \ Lowest Common Ancestor)\n * \u3092\u30C0\u30D6\u30EA\u30F3\u30B0\u306B\u3088\
    \u308A\u6C42\u3081\u308B\u69CB\u9020\u4F53\n *\n * \u4F7F\u7528\u65B9\u6CD5:\n\
    \ * 1. lowest_common_ancestor lca(n, root); \u3067\u521D\u671F\u5316\n * 2. lca.add_edge(u,\
    \ v); \u3067\u6728\u3092\u69CB\u7BC9 (\u7121\u5411\u8FBA\u304C\u8FFD\u52A0\u3055\
    \u308C\u307E\u3059)\n * 3. lca.build(); \u3092\u547C\u3073\u51FA\u3057\u3066\u30C0\
    \u30D6\u30EA\u30F3\u30B0\u30C6\u30FC\u30D6\u30EB\u3092\u69CB\u7BC9 (\u203B\u5FC5\
    \u9808)\n * 4. lca.lca(u, v) \u3084 lca.get_dist(u, v) \u3067\u30AF\u30A8\u30EA\
    \u3092\u51E6\u7406\n */\nstruct lowest_common_ancestor {\npublic:\n  int n;  \
    \   // \u9802\u70B9\u6570\n  int log_n; // \u30C0\u30D6\u30EA\u30F3\u30B0\u30C6\
    \u30FC\u30D6\u30EB\u306E\u6700\u5927\u4E57\u6570 (log2(n) \u7A0B\u5EA6)\n  std::vector<std::vector<int>>\
    \ graph; // \u5185\u90E8\u3067\u4FDD\u6301\u3059\u308B\u96A3\u63A5\u30EA\u30B9\
    \u30C8\n  std::vector<int> depth;              // \u5404\u9802\u70B9\u306E\u6DF1\
    \u3055\uFF08\u6839\u304B\u3089\u306E\u8DDD\u96E2\uFF09\n  std::vector<std::vector<int>>\n\
    \      parent; // parent[k][v]: \u9802\u70B9 v \u306E 2^k\n              // \u500B\
    \u4E0A\u306E\u89AA\u306E\u9802\u70B9\u756A\u53F7\uFF08\u5B58\u5728\u3057\u306A\
    \u3044\u5834\u5408\u306F -1\uFF09\n\n  /**\n   * @brief \u30B3\u30F3\u30B9\u30C8\
    \u30E9\u30AF\u30BF\n   * @param n \u9802\u70B9\u6570\n   */\n  lowest_common_ancestor(int\
    \ n)\n      : n(n), log_n(32 - __builtin_clz(n)), graph(n), depth(n),\n      \
    \  parent(log_n, std::vector<int>(n, -1)) {}\n\n  /**\n   * @brief \u6728\u306B\
    \u7121\u5411\u8FBA\u3092\u8FFD\u52A0\u3059\u308B\n   * @param u \u9802\u70B9\u756A\
    \u53F7\n   * @param v \u9802\u70B9\u756A\u53F7\n   */\n  void add_edge(int u,\
    \ int v) {\n    assert(0 <= u && u < n);\n    assert(0 <= v && v < n);\n    graph[u].push_back(v);\n\
    \    graph[v].push_back(u);\n  }\n\n  /**\n   * @brief \u30C6\u30FC\u30D6\u30EB\
    \u3092\u69CB\u7BC9\u3059\u308B (\u8FBA\u3092\u3059\u3079\u3066\u8FFD\u52A0\u3057\
    \u305F\u5F8C\u306B\u5FC5\u305A1\u56DE\u547C\u3073\u51FA\u3057\u3066\u304F\u3060\
    \u3055\u3044)\n   * @param root \u6728\u306E\u6839\u306E\u756A\u53F7 (\u30C7\u30D5\
    \u30A9\u30EB\u30C8\u306F 0)\n   */\n  void build(int root = 0) {\n    // DFS\u3067\
    \u76F4\u8FD1\u306E\u89AA(2^0 = 1\u500B\u4E0A)\u3068\u5404\u9802\u70B9\u306E\u6DF1\
    \u3055\u3092\u6C42\u3081\u308B\n    dfs(root);\n    // \u30C0\u30D6\u30EA\u30F3\
    \u30B0\u30C6\u30FC\u30D6\u30EB\u306E\u69CB\u7BC9\n    for (int k = 0; k < log_n\
    \ - 1; ++k) {\n      for (int i = 0; i < n; ++i) {\n        if (parent[k][i] ==\
    \ -1) {\n          parent[k + 1][i] = -1;\n        } else {\n          parent[k\
    \ + 1][i] = parent[k][parent[k][i]];\n        }\n      }\n    }\n  }\n\n  /**\n\
    \   * @brief \u9802\u70B9 u \u3068 v \u306E\u6700\u8FD1\u5171\u901A\u7956\u5148\
    \ (LCA) \u3092\u53D6\u5F97\u3059\u308B\n   * @param u \u9802\u70B9\u756A\u53F7\
    \n   * @param v \u9802\u70B9\u756A\u53F7\n   * @return LCA\u3068\u306A\u308B\u9802\
    \u70B9\u306E\u756A\u53F7\n   */\n  int lca(int u, int v) const {\n    // u \u3068\
    \ v \u306E\u6DF1\u3055\u3092\u63C3\u3048\u308B\uFF08\u5E38\u306B v \u306E\u65B9\
    \u304C\u6DF1\u304F\u306A\u308B\u3088\u3046\u306B\u3059\u308B\uFF09\n    if (depth[u]\
    \ > depth[v]) {\n      std::swap(u, v);\n    }\n    for (int i = log_n - 1; i\
    \ >= 0; --i) {\n      if (((depth[v] - depth[u]) >> i) & 1) {\n        v = parent[i][v];\n\
    \      }\n    }\n    if (u == v) {\n      return u;\n    }\n    // 2\u51AA\u3092\
    \u4E0A\u304B\u3089\u964D\u308A\u3064\u3064\u3001\u5171\u901A\u7956\u5148\u3092\
    \u6301\u305F\u306A\u3044\uFF08\u89AA\u304C\u7570\u306A\u308B\uFF09\u5834\u5408\
    \u306F\u5373\u5EA7\u306B\u305D\u306E\u6DF1\u3055\u307E\u3067\u79FB\u52D5\u3059\
    \u308B\n    // \uFF08LCA\u5224\u5B9A\u3092\u611A\u76F4\u306B\u4E8C\u5206\u63A2\
    \u7D22\u3059\u308B\u3068 O(log^2 N) \u304B\u304B\u308B\u304C\u3001\u3053\u306E\
    \u65B9\u6CD5\u306B\u3088\u308A O(log\n    // N) \u3067LCA\u306E\u76F4\u524D\u307E\
    \u3067\u9061\u308C\u308B\uFF09\n    for (int i = log_n - 1; i >= 0; --i) {\n \
    \     if (parent[i][u] != parent[i][v]) {\n        u = parent[i][u];\n       \
    \ v = parent[i][v];\n      }\n    }\n    return parent[0][u];\n  }\n\n  /**\n\
    \   * @brief 2\u70B9 u, v \u9593\u306E\u6700\u77ED\u30D1\u30B9\u4E0A\u306E\u8FBA\
    \u306E\u6570\uFF08\u8DDD\u96E2\uFF09\u3092\u53D6\u5F97\u3059\u308B\n   * @param\
    \ u \u9802\u70B9\u756A\u53F7\n   * @param v \u9802\u70B9\u756A\u53F7\n   * @return\
    \ \u8DDD\u96E2\n   */\n  int get_dist(int u, int v) const {\n    return depth[u]\
    \ + depth[v] - 2 * depth[lca(u, v)];\n  }\n\nprivate:\n  void dfs(int cur, int\
    \ par = -1, int d = 0) {\n    parent[0][cur] = par;\n    depth[cur] = d;\n   \
    \ for (int next_node : graph[cur]) {\n      if (next_node != par) {\n        dfs(next_node,\
    \ cur, d + 1);\n      }\n    }\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: tree/lca.hpp
  requiredBy: []
  timestamp: '2026-06-21 13:10:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lca.test.cpp
documentation_of: tree/lca.hpp
layout: document
redirect_from:
- /library/tree/lca.hpp
- /library/tree/lca.hpp.html
title: "\u6700\u8FD1\u5171\u901A\u7956\u5148 (LCA: Lowest Common Ancestor)"
---
