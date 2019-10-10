#include<bits/stdc++.h>
using namespace std;

// Range Minimum Query in Segment Tree.

struct rmq{
  // 管理したい元の配列のサイズ以上の2冪。
  int n;
  // セグメント木(完全二分木)を管理する一次元配列。
  vector<int> segtree;
  // minの単位元としてのINF。値は2^31-1。
  const int INF = INT_MAX;
  
  // @param sz 管理したい元の配列のサイズ
  // nをsz以上の2冪にし、セグメント木のサイズを2*n-1、値をINFに初期化する。
  rmq(int sz){
    for(n = 1; n<sz;) n <<= 1;
    segtree.assign(2*n-1,INF);
  }
  
  // 元の配列の[l,r)のminを求める。
  // @param l,r [l,r)が求めたいminの元の配列での範囲。
  // @param a,b [a,b)が現在見ている頂点の持つminの元の配列における範囲。
  // @param k   セグメント木の現在見ている頂点のindex
  // @return    セグメント木により、求められた[l,r)の最小値。
  // 上からDFSして、[l,r)内の頂点であれば自身の値を返し、そうでなければ単位元を返す。
  // このようにして帰ってきた値を全てminしたものが求めたいものである。
  int find(int l, int r, int a=0, int b=n, int k=0){
    // [a,b)が[l,r)の外側なら、影響のない単位元INFを返す。
    if(b<l || r<a) return INF;
    
    // [a,b)が[l,r)の内側なら、その頂点は[l,r)内で最も大きい区間minを持つので、それを返す。
    else if(l<=a && b<=r) return segtree[k];
    
    // どちらでもなければ(解説スライドでの赤線を跨いでいる状態)、もっと細分されたものを確認する必要があるため、子を確認する。
    // 左側の子は[a,(a+b)/2)の区間minを持ち、indexは2*k+1
    // 右側の子は[(a+b)/2,b)の区間minを持ち、indexは2*k+2
    // この２つの[l,r)内の区間minのminを返してやれば良い。
    // 現在見ている頂点が葉に該当する場合は必ず上の２つの条件のどちらかで捕捉されるため考えなくて良い。
    else return min(find(l,r,a,(a+b)/2,2*k+1), find(l,r,(a+b)/2,b,2*k+2));
  }
  
    
  // @param i 書き換えたい値の元の配列におけるindex
  // @param x 更新後の値
  void update(int i, int x){
    // 解説スライドの通り、元の配列を持つ最下段の長さをn(2冪)とすると、
    // その上のセグメント木の構造を持つ部分は n/2 + n/4 + n/8 + .. + 1 = n-1(等比級数の公式より)
    // よって、元の配列を最初に更新したいので、元の配列部分のindexに修正するため、n-1を加える。
    i += n-1;
    
    //
    while(i>0){
      i = (i-1)/2;
      segtree[i] = min(segtree[2*i+1], segtree[2*i+2]);
    }
  }
};
  
