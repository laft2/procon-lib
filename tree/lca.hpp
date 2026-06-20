#include <vector>

using namespace std;
struct lowest_common_ancestor {
  const vector<vector<int>> graph;
  const int sz, width;
  vector<int> depth;
  vector<vector<int>> par_table;
  int root;

  lowest_common_ancestor(const vector<vector<int>> &graph, int root = 0)
      : graph(graph), sz(graph.size()), width(32 - __builtin_clz(graph.size())),
        depth(graph.size()), par_table(width, vector<int>(graph.size(), -1)),
        root(root) {
    build();
  }

  void dfs(int cur, int par = -1, int d = 0) {
    par_table[0][cur] = par;
    depth[cur] = d;
    for (auto &&e : graph[cur])
      if (e != par) {
        dfs(e, cur, d + 1);
      }
  }
  void build() {
    dfs(root);
    for (int k = 0; k < width - 1; ++k)
      for (int i = 0; i < sz; ++i) {
        if (par_table[k][i] == -1)
          par_table[k + 1][i] = -1;
        else
          par_table[k + 1][i] = par_table[k][par_table[k][i]];
      }
  }
  int query(int u, int v) {
    if (depth[u] > depth[v])
      swap(u, v);
    for (int i = width - 1; i >= 0; --i) {
      if ((depth[v] - depth[u]) >> i & 1)
        v = par_table[i][v];
    }
    if (u == v)
      return u;
    for (int i = width - 1; i >= 0; --i) {
      if (par_table[i][u] != par_table[i][v]) {
        u = par_table[i][u];
        v = par_table[i][v];
      }
    }
    return par_table[0][u];
  }
};