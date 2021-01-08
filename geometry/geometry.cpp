#include <complex>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;
constexpr long double EPS = 1e-10;

using ld = long double;
using Point = complex<ld>;
bool eq(Point a,Point b) {
  return (abs(a - b) < EPS);
}
ld dot(Point a, Point b){
  return real(conj(a)*b);
}
ld cross(Point a, Point b){
  return imag(conj(a)*b);
}
struct Line{
  Point a,b;
};
struct Circle{
  Point p;
  ld r;
};
int ccw(Point a, Point b, Point c){
  b -= a; c -= a;
  if(cross(b,c) > EPS) return 1; // a,b,cが時計回りに並ぶ。
  if(cross(b,c) < -EPS) return -1; // a,b,cが反時計回りに並ぶ。
  if(dot(b,c) < 0) return 2; // c,a,bの順に直線に並ぶ。
  if(norm(b) < norm(c)) return -2; // a,b,cの順に直線に並ぶ。
  return 0; // a,c,bの順に直線に並ぶ。
}
/// 交差判定
// 直線と直線の交差判定
bool isis_ll (Line l, Line m) {
  return !eq(cross(l.b - l.a, m.b - m.a), 0);
}
// 直線と線分の交差判定
bool isis_ls (Line l, Line s) {
  return (cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - s.a) < EPS);
}
// 点が直線上に存在するかの判定
bool isis_lp (Line l, Point p) {
  return (abs(cross(l.b - p, l.a - p)) < EPS);
}
// 点が線分上に存在するかの判定
bool isis_sp (Line s, Point p) {
  return (abs(s.a - p) + abs(s.b - p) - abs(s.b - s.a) < EPS);
}
// 線分と線分の交差判定
bool isis_ss(Line s1, Line s2) {
  return ccw(s1.a, s1.b, s2.a) * ccw(s1.a, s1.b, s2.b) <= 0 &&
    ccw(s2.a, s2.b, s1.a) * ccw(s2.a, s2.b, s1.b) <= 0;
}
// 点が直線に下ろす垂線の足
Point proj (Line l, Point p) {
  ld t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + t * (l.a - l.b);
}
// 直線と直線の交点の座標
Point is_ll (Line s, Line t) {
  Point sv = s.b - s.a, tv = t.b - t.a;
  assert(cross(sv, tv) != 0);
  return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);
}
/// 距離
// 点と直線
ld dist_lp (Line l, Point p) {
  return abs(p - proj(l, p));
}
// 直線と直線
ld dist_ll (Line l, Line m) {
  return isis_ll(l, m) ? 0 : dist_lp(l, m.a);
}
// 直線と線分
ld dist_ls (Line l, Line s) {
  return isis_ls(l, s) ? 0 : min(dist_lp(l, s.a), dist_lp(l, s.b));
}
// 線分と点
ld dist_sp (Line s, Point p) {
  Point r = proj(s, p);
  return isis_sp(s, r) ? abs(r - p) : min(abs(s.a - p), abs(s.b - p));
}
// 線分と線分
ld dist_ss (Line s, Line t) {
  if (isis_ss(s, t)) return 0;
  return min({dist_sp(s, t.a), dist_sp(s, t.b), dist_sp(t, s.a), dist_sp(t, s.b)});
}

// 円と円の交点
vector<Point> is_cc (Circle c1, Circle c2) {
  vector<Point> res;
  ld d = abs(c1.p - c2.p);
  ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
  ld dfr = c1.r * c1.r - rc * rc;
  if (abs(dfr) < EPS) dfr = 0.0;
  if (dfr < 0.0) return res;
  ld rs = sqrt(dfr);
  Point dif = (c2.p - c1.p) / d;
  res.push_back(c1.p + dif * Point (rc, rs));
  if (dfr != 0.0) res.push_back(c1.p + dif * Point (rc, -rs));
  return res;
}
// 円と直線の交点
vector<Point> is_lc (Circle c, Line l) {
  vector<Point> res;
  ld d = dist_lp(l, c.p);
  if (d > c.r + EPS) return res;
  ld len = (d > c.r) ? 0.0 : sqrt(c.r * c.r - d * d);
  Point nor = (l.a - l.b) / abs(l.a - l.b);
  res.push_back(proj(l, c.p) + len * nor);
  res.push_back(proj(l, c.p) - len * nor);
  return res;
}
// 円と線分の交点
vector<Point> is_sc (Circle c, Line s) {
  vector<Point> v = is_lc(c, s), res;
  for (int k = 0; k < (int)v.size(); k++)
  if (ccw(s.a, v[k], s.b) == -2)
  res.push_back(v[k]);
  return res;
}
// 与えられた点を通る円の接点
vector<Line> tangent_cp(Circle c, Point p) {
  vector<Line> res;
  Point v = c.p - p;
  ld d = abs(v);
  ld l = sqrt(norm(v) - c.r * c.r);
  if (isnan(l)) { return res; }
  Point v1 = v * Point (l / d, c.r / d);
  Point v2 = v * Point (l / d, -c.r / d);
  res.push_back((Line){p, p + v1});
  if (l < EPS) return res;
  res.push_back((Line){p, p + v2});
  return res;
}
// 円と円の接線
vector<Line> tangent_cc(Circle c1, Circle c2) {
  vector<Line> res;
  if (abs(c1.p - c2.p) - (c1.r + c2.r) > -EPS) {
  Point center = (c1.p * c2.r + c2.p * c1.r) / (c1.r + c2.r);
  res = tangent_cp(c1, center);
  }
  if (abs(c1.r - c2.r) > EPS) {
  Point out = (-c1.p * c2.r + c2.p * c1.r) / (c1.r - c2.r);
  vector<Line> nres = tangent_cp(c1, out);
  res.insert(res.end(), nres.begin(), nres.end());
  }
  else {
  Point v = c2.p - c1.p; v /= abs(v);
  Point q1 = c1.p + v * Point(0, 1) * c1.r;
  Point q2 = c1.p + v * Point(0, -1) * c1.r;
  res.push_back((Line){q1, q1 + v});
  res.push_back((Line){q2, q2 + v});
  }
  return res;
}