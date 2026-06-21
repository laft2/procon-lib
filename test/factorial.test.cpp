#define PROBLEM                                                                \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/DPL/5/DPL_5_D"

#include "math/factrial.hpp"
#include "math/modint.hpp"
#include <iostream>

using namespace std;
using mint = modint1000000007;

int main() {
  int n, k;
  if (!(cin >> n >> k))
    return 0;

  // modint (10^9+7) を使って階乗・組合せライブラリを初期化
  factrial<mint> fc;

  // n個の区別できないボールを k個の区別できる箱に入れる方法の数 = k H n
  // (重複組合せ)
  cout << fc.comb_rep(k, n) << endl;

  return 0;
}
