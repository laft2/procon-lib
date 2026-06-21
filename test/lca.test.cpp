#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../tree/lca.hpp"
#include <iostream>

using namespace std;

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> p(n);
  auto lca = lowest_common_ancestor(n, 0);
  for (int i = 0; i < n - 1; ++i) {
    int tmp;
    cin >> tmp;
    lca.add_edge(i + 1, tmp);
  }
  for (int i = 0; i < q; ++i) {
    int u, v;
    cin >> u >> v;
    cout << lca.lca(u, v) << '\n';
  }
}