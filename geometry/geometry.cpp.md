---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/geometry.cpp\"\n#include <complex>\n#include <vector>\n\
    #include <cassert>\n#include <algorithm>\nusing namespace std;\nconstexpr long\
    \ double EPS = 1e-10;\n\nusing ld = long double;\nusing Point = complex<ld>;\n\
    bool eq(Point a,Point b) {\n  return (abs(a - b) < EPS);\n}\nld dot(Point a, Point\
    \ b){\n  return real(conj(a)*b);\n}\nld cross(Point a, Point b){\n  return imag(conj(a)*b);\n\
    }\nstruct Line{\n  Point a,b;\n};\nstruct Circle{\n  Point p;\n  ld r;\n};\nint\
    \ ccw(Point a, Point b, Point c){\n  b -= a; c -= a;\n  if(cross(b,c) > EPS) return\
    \ 1; // a,b,c\u304C\u6642\u8A08\u56DE\u308A\u306B\u4E26\u3076\u3002\n  if(cross(b,c)\
    \ < -EPS) return -1; // a,b,c\u304C\u53CD\u6642\u8A08\u56DE\u308A\u306B\u4E26\u3076\
    \u3002\n  if(dot(b,c) < 0) return 2; // c,a,b\u306E\u9806\u306B\u76F4\u7DDA\u306B\
    \u4E26\u3076\u3002\n  if(norm(b) < norm(c)) return -2; // a,b,c\u306E\u9806\u306B\
    \u76F4\u7DDA\u306B\u4E26\u3076\u3002\n  return 0; // a,c,b\u306E\u9806\u306B\u76F4\
    \u7DDA\u306B\u4E26\u3076\u3002\n}\n/// \u4EA4\u5DEE\u5224\u5B9A\n// \u76F4\u7DDA\
    \u3068\u76F4\u7DDA\u306E\u4EA4\u5DEE\u5224\u5B9A\nbool isis_ll (Line l, Line m)\
    \ {\n  return !eq(cross(l.b - l.a, m.b - m.a), 0);\n}\n// \u76F4\u7DDA\u3068\u7DDA\
    \u5206\u306E\u4EA4\u5DEE\u5224\u5B9A\nbool isis_ls (Line l, Line s) {\n  return\
    \ (cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - s.a) < EPS);\n}\n// \u70B9\
    \u304C\u76F4\u7DDA\u4E0A\u306B\u5B58\u5728\u3059\u308B\u304B\u306E\u5224\u5B9A\
    \nbool isis_lp (Line l, Point p) {\n  return (abs(cross(l.b - p, l.a - p)) < EPS);\n\
    }\n// \u70B9\u304C\u7DDA\u5206\u4E0A\u306B\u5B58\u5728\u3059\u308B\u304B\u306E\
    \u5224\u5B9A\nbool isis_sp (Line s, Point p) {\n  return (abs(s.a - p) + abs(s.b\
    \ - p) - abs(s.b - s.a) < EPS);\n}\n// \u7DDA\u5206\u3068\u7DDA\u5206\u306E\u4EA4\
    \u5DEE\u5224\u5B9A\nbool isis_ss(Line s1, Line s2) {\n  return ccw(s1.a, s1.b,\
    \ s2.a) * ccw(s1.a, s1.b, s2.b) <= 0 &&\n    ccw(s2.a, s2.b, s1.a) * ccw(s2.a,\
    \ s2.b, s1.b) <= 0;\n}\n// \u70B9\u304C\u76F4\u7DDA\u306B\u4E0B\u308D\u3059\u5782\
    \u7DDA\u306E\u8DB3\nPoint proj (Line l, Point p) {\n  ld t = dot(p - l.a, l.a\
    \ - l.b) / norm(l.a - l.b);\n  return l.a + t * (l.a - l.b);\n}\n// \u76F4\u7DDA\
    \u3068\u76F4\u7DDA\u306E\u4EA4\u70B9\u306E\u5EA7\u6A19\nPoint is_ll (Line s, Line\
    \ t) {\n  Point sv = s.b - s.a, tv = t.b - t.a;\n  assert(cross(sv, tv) != 0);\n\
    \  return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);\n}\n/// \u8DDD\u96E2\
    \n// \u70B9\u3068\u76F4\u7DDA\nld dist_lp (Line l, Point p) {\n  return abs(p\
    \ - proj(l, p));\n}\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\nld dist_ll (Line l, Line\
    \ m) {\n  return isis_ll(l, m) ? 0 : dist_lp(l, m.a);\n}\n// \u76F4\u7DDA\u3068\
    \u7DDA\u5206\nld dist_ls (Line l, Line s) {\n  return isis_ls(l, s) ? 0 : min(dist_lp(l,\
    \ s.a), dist_lp(l, s.b));\n}\n// \u7DDA\u5206\u3068\u70B9\nld dist_sp (Line s,\
    \ Point p) {\n  Point r = proj(s, p);\n  return isis_sp(s, r) ? abs(r - p) : min(abs(s.a\
    \ - p), abs(s.b - p));\n}\n// \u7DDA\u5206\u3068\u7DDA\u5206\nld dist_ss (Line\
    \ s, Line t) {\n  if (isis_ss(s, t)) return 0;\n  return min({dist_sp(s, t.a),\
    \ dist_sp(s, t.b), dist_sp(t, s.a), dist_sp(t, s.b)});\n}\n\n// \u5186\u3068\u5186\
    \u306E\u4EA4\u70B9\nvector<Point> is_cc (Circle c1, Circle c2) {\n  vector<Point>\
    \ res;\n  ld d = abs(c1.p - c2.p);\n  ld rc = (d * d + c1.r * c1.r - c2.r * c2.r)\
    \ / (2 * d);\n  ld dfr = c1.r * c1.r - rc * rc;\n  if (abs(dfr) < EPS) dfr = 0.0;\n\
    \  if (dfr < 0.0) return res;\n  ld rs = sqrt(dfr);\n  Point dif = (c2.p - c1.p)\
    \ / d;\n  res.push_back(c1.p + dif * Point (rc, rs));\n  if (dfr != 0.0) res.push_back(c1.p\
    \ + dif * Point (rc, -rs));\n  return res;\n}\n// \u5186\u3068\u76F4\u7DDA\u306E\
    \u4EA4\u70B9\nvector<Point> is_lc (Circle c, Line l) {\n  vector<Point> res;\n\
    \  ld d = dist_lp(l, c.p);\n  if (d > c.r + EPS) return res;\n  ld len = (d >\
    \ c.r) ? 0.0 : sqrt(c.r * c.r - d * d);\n  Point nor = (l.a - l.b) / abs(l.a -\
    \ l.b);\n  res.push_back(proj(l, c.p) + len * nor);\n  res.push_back(proj(l, c.p)\
    \ - len * nor);\n  return res;\n}\n// \u5186\u3068\u7DDA\u5206\u306E\u4EA4\u70B9\
    \nvector<Point> is_sc (Circle c, Line s) {\n  vector<Point> v = is_lc(c, s), res;\n\
    \  for (int k = 0; k < (int)v.size(); k++)\n  if (ccw(s.a, v[k], s.b) == -2)\n\
    \  res.push_back(v[k]);\n  return res;\n}\n// \u4E0E\u3048\u3089\u308C\u305F\u70B9\
    \u3092\u901A\u308B\u5186\u306E\u63A5\u70B9\nvector<Line> tangent_cp(Circle c,\
    \ Point p) {\n  vector<Line> res;\n  Point v = c.p - p;\n  ld d = abs(v);\n  ld\
    \ l = sqrt(norm(v) - c.r * c.r);\n  if (isnan(l)) { return res; }\n  Point v1\
    \ = v * Point (l / d, c.r / d);\n  Point v2 = v * Point (l / d, -c.r / d);\n \
    \ res.push_back((Line){p, p + v1});\n  if (l < EPS) return res;\n  res.push_back((Line){p,\
    \ p + v2});\n  return res;\n}\n// \u5186\u3068\u5186\u306E\u63A5\u7DDA\nvector<Line>\
    \ tangent_cc(Circle c1, Circle c2) {\n  vector<Line> res;\n  if (abs(c1.p - c2.p)\
    \ - (c1.r + c2.r) > -EPS) {\n  Point center = (c1.p * c2.r + c2.p * c1.r) / (c1.r\
    \ + c2.r);\n  res = tangent_cp(c1, center);\n  }\n  if (abs(c1.r - c2.r) > EPS)\
    \ {\n  Point out = (-c1.p * c2.r + c2.p * c1.r) / (c1.r - c2.r);\n  vector<Line>\
    \ nres = tangent_cp(c1, out);\n  res.insert(res.end(), nres.begin(), nres.end());\n\
    \  }\n  else {\n  Point v = c2.p - c1.p; v /= abs(v);\n  Point q1 = c1.p + v *\
    \ Point(0, 1) * c1.r;\n  Point q2 = c1.p + v * Point(0, -1) * c1.r;\n  res.push_back((Line){q1,\
    \ q1 + v});\n  res.push_back((Line){q2, q2 + v});\n  }\n  return res;\n}\n"
  code: "#include <complex>\n#include <vector>\n#include <cassert>\n#include <algorithm>\n\
    using namespace std;\nconstexpr long double EPS = 1e-10;\n\nusing ld = long double;\n\
    using Point = complex<ld>;\nbool eq(Point a,Point b) {\n  return (abs(a - b) <\
    \ EPS);\n}\nld dot(Point a, Point b){\n  return real(conj(a)*b);\n}\nld cross(Point\
    \ a, Point b){\n  return imag(conj(a)*b);\n}\nstruct Line{\n  Point a,b;\n};\n\
    struct Circle{\n  Point p;\n  ld r;\n};\nint ccw(Point a, Point b, Point c){\n\
    \  b -= a; c -= a;\n  if(cross(b,c) > EPS) return 1; // a,b,c\u304C\u6642\u8A08\
    \u56DE\u308A\u306B\u4E26\u3076\u3002\n  if(cross(b,c) < -EPS) return -1; // a,b,c\u304C\
    \u53CD\u6642\u8A08\u56DE\u308A\u306B\u4E26\u3076\u3002\n  if(dot(b,c) < 0) return\
    \ 2; // c,a,b\u306E\u9806\u306B\u76F4\u7DDA\u306B\u4E26\u3076\u3002\n  if(norm(b)\
    \ < norm(c)) return -2; // a,b,c\u306E\u9806\u306B\u76F4\u7DDA\u306B\u4E26\u3076\
    \u3002\n  return 0; // a,c,b\u306E\u9806\u306B\u76F4\u7DDA\u306B\u4E26\u3076\u3002\
    \n}\n/// \u4EA4\u5DEE\u5224\u5B9A\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\u306E\u4EA4\
    \u5DEE\u5224\u5B9A\nbool isis_ll (Line l, Line m) {\n  return !eq(cross(l.b -\
    \ l.a, m.b - m.a), 0);\n}\n// \u76F4\u7DDA\u3068\u7DDA\u5206\u306E\u4EA4\u5DEE\
    \u5224\u5B9A\nbool isis_ls (Line l, Line s) {\n  return (cross(l.b - l.a, s.a\
    \ - l.a) * cross(l.b - l.a, s.b - s.a) < EPS);\n}\n// \u70B9\u304C\u76F4\u7DDA\
    \u4E0A\u306B\u5B58\u5728\u3059\u308B\u304B\u306E\u5224\u5B9A\nbool isis_lp (Line\
    \ l, Point p) {\n  return (abs(cross(l.b - p, l.a - p)) < EPS);\n}\n// \u70B9\u304C\
    \u7DDA\u5206\u4E0A\u306B\u5B58\u5728\u3059\u308B\u304B\u306E\u5224\u5B9A\nbool\
    \ isis_sp (Line s, Point p) {\n  return (abs(s.a - p) + abs(s.b - p) - abs(s.b\
    \ - s.a) < EPS);\n}\n// \u7DDA\u5206\u3068\u7DDA\u5206\u306E\u4EA4\u5DEE\u5224\
    \u5B9A\nbool isis_ss(Line s1, Line s2) {\n  return ccw(s1.a, s1.b, s2.a) * ccw(s1.a,\
    \ s1.b, s2.b) <= 0 &&\n    ccw(s2.a, s2.b, s1.a) * ccw(s2.a, s2.b, s1.b) <= 0;\n\
    }\n// \u70B9\u304C\u76F4\u7DDA\u306B\u4E0B\u308D\u3059\u5782\u7DDA\u306E\u8DB3\
    \nPoint proj (Line l, Point p) {\n  ld t = dot(p - l.a, l.a - l.b) / norm(l.a\
    \ - l.b);\n  return l.a + t * (l.a - l.b);\n}\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\
    \u306E\u4EA4\u70B9\u306E\u5EA7\u6A19\nPoint is_ll (Line s, Line t) {\n  Point\
    \ sv = s.b - s.a, tv = t.b - t.a;\n  assert(cross(sv, tv) != 0);\n  return s.a\
    \ + sv * cross(tv, t.a - s.a) / cross(tv, sv);\n}\n/// \u8DDD\u96E2\n// \u70B9\
    \u3068\u76F4\u7DDA\nld dist_lp (Line l, Point p) {\n  return abs(p - proj(l, p));\n\
    }\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\nld dist_ll (Line l, Line m) {\n  return\
    \ isis_ll(l, m) ? 0 : dist_lp(l, m.a);\n}\n// \u76F4\u7DDA\u3068\u7DDA\u5206\n\
    ld dist_ls (Line l, Line s) {\n  return isis_ls(l, s) ? 0 : min(dist_lp(l, s.a),\
    \ dist_lp(l, s.b));\n}\n// \u7DDA\u5206\u3068\u70B9\nld dist_sp (Line s, Point\
    \ p) {\n  Point r = proj(s, p);\n  return isis_sp(s, r) ? abs(r - p) : min(abs(s.a\
    \ - p), abs(s.b - p));\n}\n// \u7DDA\u5206\u3068\u7DDA\u5206\nld dist_ss (Line\
    \ s, Line t) {\n  if (isis_ss(s, t)) return 0;\n  return min({dist_sp(s, t.a),\
    \ dist_sp(s, t.b), dist_sp(t, s.a), dist_sp(t, s.b)});\n}\n\n// \u5186\u3068\u5186\
    \u306E\u4EA4\u70B9\nvector<Point> is_cc (Circle c1, Circle c2) {\n  vector<Point>\
    \ res;\n  ld d = abs(c1.p - c2.p);\n  ld rc = (d * d + c1.r * c1.r - c2.r * c2.r)\
    \ / (2 * d);\n  ld dfr = c1.r * c1.r - rc * rc;\n  if (abs(dfr) < EPS) dfr = 0.0;\n\
    \  if (dfr < 0.0) return res;\n  ld rs = sqrt(dfr);\n  Point dif = (c2.p - c1.p)\
    \ / d;\n  res.push_back(c1.p + dif * Point (rc, rs));\n  if (dfr != 0.0) res.push_back(c1.p\
    \ + dif * Point (rc, -rs));\n  return res;\n}\n// \u5186\u3068\u76F4\u7DDA\u306E\
    \u4EA4\u70B9\nvector<Point> is_lc (Circle c, Line l) {\n  vector<Point> res;\n\
    \  ld d = dist_lp(l, c.p);\n  if (d > c.r + EPS) return res;\n  ld len = (d >\
    \ c.r) ? 0.0 : sqrt(c.r * c.r - d * d);\n  Point nor = (l.a - l.b) / abs(l.a -\
    \ l.b);\n  res.push_back(proj(l, c.p) + len * nor);\n  res.push_back(proj(l, c.p)\
    \ - len * nor);\n  return res;\n}\n// \u5186\u3068\u7DDA\u5206\u306E\u4EA4\u70B9\
    \nvector<Point> is_sc (Circle c, Line s) {\n  vector<Point> v = is_lc(c, s), res;\n\
    \  for (int k = 0; k < (int)v.size(); k++)\n  if (ccw(s.a, v[k], s.b) == -2)\n\
    \  res.push_back(v[k]);\n  return res;\n}\n// \u4E0E\u3048\u3089\u308C\u305F\u70B9\
    \u3092\u901A\u308B\u5186\u306E\u63A5\u70B9\nvector<Line> tangent_cp(Circle c,\
    \ Point p) {\n  vector<Line> res;\n  Point v = c.p - p;\n  ld d = abs(v);\n  ld\
    \ l = sqrt(norm(v) - c.r * c.r);\n  if (isnan(l)) { return res; }\n  Point v1\
    \ = v * Point (l / d, c.r / d);\n  Point v2 = v * Point (l / d, -c.r / d);\n \
    \ res.push_back((Line){p, p + v1});\n  if (l < EPS) return res;\n  res.push_back((Line){p,\
    \ p + v2});\n  return res;\n}\n// \u5186\u3068\u5186\u306E\u63A5\u7DDA\nvector<Line>\
    \ tangent_cc(Circle c1, Circle c2) {\n  vector<Line> res;\n  if (abs(c1.p - c2.p)\
    \ - (c1.r + c2.r) > -EPS) {\n  Point center = (c1.p * c2.r + c2.p * c1.r) / (c1.r\
    \ + c2.r);\n  res = tangent_cp(c1, center);\n  }\n  if (abs(c1.r - c2.r) > EPS)\
    \ {\n  Point out = (-c1.p * c2.r + c2.p * c1.r) / (c1.r - c2.r);\n  vector<Line>\
    \ nres = tangent_cp(c1, out);\n  res.insert(res.end(), nres.begin(), nres.end());\n\
    \  }\n  else {\n  Point v = c2.p - c1.p; v /= abs(v);\n  Point q1 = c1.p + v *\
    \ Point(0, 1) * c1.r;\n  Point q2 = c1.p + v * Point(0, -1) * c1.r;\n  res.push_back((Line){q1,\
    \ q1 + v});\n  res.push_back((Line){q2, q2 + v});\n  }\n  return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: geometry/geometry.cpp
  requiredBy: []
  timestamp: '2023-11-29 04:11:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/geometry.cpp
layout: document
redirect_from:
- /library/geometry/geometry.cpp
- /library/geometry/geometry.cpp.html
title: geometry/geometry.cpp
---
