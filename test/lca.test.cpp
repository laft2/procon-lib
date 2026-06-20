#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../tree/lca.hpp"
#include <iostream>

using namespace std;

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> p(n);
  vector<vector<int>> graph(n);
  for (int i = 0; i < n - 1; ++i) {
    int tmp;
    cin >> tmp;
    graph[i + 1].emplace_back(tmp);
    graph[tmp].emplace_back(i + 1);
  }
  auto lca = lowest_common_ancestor(graph, 0);
  for (int i = 0; i < q; ++i) {
    int u, v;
    cin >> u >> v;
    cout << lca.query(u, v) << '\n';
  }
}