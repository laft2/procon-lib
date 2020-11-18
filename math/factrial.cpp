#include<vector>
using namespace std;

template<typename T>
struct factrial{
  int sz_f=0, sz_i=0;
  vector<T> m_fact;
  vector<T> m_infact;

  void update_fact(int n){
    if(sz_f > n) return;
    m_fact.resize(n+1, 1);
    for(int i = sz_f; i<n+1; ++i){
      m_fact[i] = m_fact[i-1] * i;
    }
    sz_f = n+1;
  }
  void update_infact(int n){
    if(sz_i > n) return;
    m_infact.resize(n+1, 1);
    for(int i = sz_i; i<n+1; ++i){
      m_infact[i] = m_infact[i-1] / i;
    }
    sz_i = n+1;
  }

  // n!を求める
  T fact(int n){
    update_fact(n);
    return m_fact[n];
  }
  // (1/n!)を求める。
  T infact(int n){
    update_infact(n);
    return m_infact;
  }
  // nPkを求める。
  T perm(int n, int k){
    if(n < k) return 0;
    return fact(n) * infact(n-k);
  }
  // nCkを求める。
  T comb(int n, int k){
    if(n < k) return 0;
    return perm(n,k) * infact(k);
  }
  // nHkを求める。
  T comb_rep(int n, int k){
    return comb(n+k-1, k);
  }
};

// usage:
// factrial<mint> fc();
// fc.fact(10); // 10!を計算する。
// fc.comb(10,3); // 10C3を計算する。