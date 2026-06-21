#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

/**
 * @brief 最近共通祖先 (LCA: Lowest Common Ancestor)
 * をダブリングにより求める構造体
 *
 * 使用方法:
 * 1. lowest_common_ancestor lca(n, root); で初期化
 * 2. lca.add_edge(u, v); で木を構築 (無向辺が追加されます)
 * 3. lca.build(); を呼び出してダブリングテーブルを構築 (※必須)
 * 4. lca.lca(u, v) や lca.get_dist(u, v) でクエリを処理
 */
struct lowest_common_ancestor {
public:
  int n;     // 頂点数
  int log_n; // ダブリングテーブルの最大乗数 (log2(n) 程度)
  std::vector<std::vector<int>> graph; // 内部で保持する隣接リスト
  std::vector<int> depth;              // 各頂点の深さ（根からの距離）
  std::vector<std::vector<int>>
      parent; // parent[k][v]: 頂点 v の 2^k
              // 個上の親の頂点番号（存在しない場合は -1）

  /**
   * @brief コンストラクタ
   * @param n 頂点数
   */
  lowest_common_ancestor(int n)
      : n(n), log_n(32 - __builtin_clz(n)), graph(n), depth(n),
        parent(log_n, std::vector<int>(n, -1)) {}

  /**
   * @brief 木に無向辺を追加する
   * @param u 頂点番号
   * @param v 頂点番号
   */
  void add_edge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  /**
   * @brief テーブルを構築する (辺をすべて追加した後に必ず1回呼び出してください)
   * @param root 木の根の番号 (デフォルトは 0)
   */
  void build(int root = 0) {
    // DFSで直近の親(2^0 = 1個上)と各頂点の深さを求める
    dfs(root);
    // ダブリングテーブルの構築
    for (int k = 0; k < log_n - 1; ++k) {
      for (int i = 0; i < n; ++i) {
        if (parent[k][i] == -1) {
          parent[k + 1][i] = -1;
        } else {
          parent[k + 1][i] = parent[k][parent[k][i]];
        }
      }
    }
  }

  /**
   * @brief 頂点 u と v の最近共通祖先 (LCA) を取得する
   * @param u 頂点番号
   * @param v 頂点番号
   * @return LCAとなる頂点の番号
   */
  int lca(int u, int v) const {
    // u と v の深さを揃える（常に v の方が深くなるようにする）
    if (depth[u] > depth[v]) {
      std::swap(u, v);
    }
    for (int i = log_n - 1; i >= 0; --i) {
      if (((depth[v] - depth[u]) >> i) & 1) {
        v = parent[i][v];
      }
    }
    if (u == v) {
      return u;
    }
    // 2冪を上から降りつつ、共通祖先を持たない（親が異なる）場合は即座にその深さまで移動する
    // （LCA判定を愚直に二分探索すると O(log^2 N) かかるが、この方法により O(log
    // N) でLCAの直前まで遡れる）
    for (int i = log_n - 1; i >= 0; --i) {
      if (parent[i][u] != parent[i][v]) {
        u = parent[i][u];
        v = parent[i][v];
      }
    }
    return parent[0][u];
  }

  /**
   * @brief 2点 u, v 間の最短パス上の辺の数（距離）を取得する
   * @param u 頂点番号
   * @param v 頂点番号
   * @return 距離
   */
  int get_dist(int u, int v) const {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
  }

private:
  void dfs(int cur, int par = -1, int d = 0) {
    parent[0][cur] = par;
    depth[cur] = d;
    for (int next_node : graph[cur]) {
      if (next_node != par) {
        dfs(next_node, cur, d + 1);
      }
    }
  }
};