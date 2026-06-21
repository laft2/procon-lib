---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"geometry/geometry.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <complex>\n#include <vector>\n#include <cmath>\n\nconstexpr\
    \ long double EPS = 1e-10;\n\nusing ld = long double;\nusing Point = std::complex<ld>;\n\
    \ninline bool eq(Point a, Point b) { return (std::abs(a - b) < EPS); }\ninline\
    \ ld dot(Point a, Point b) { return std::real(std::conj(a) * b); }\ninline ld\
    \ cross(Point a, Point b) { return std::imag(std::conj(a) * b); }\n\nstruct Line\
    \ {\n  Point a, b;\n};\n\nstruct Circle {\n  Point p;\n  ld r;\n};\n\ninline int\
    \ ccw(Point a, Point b, Point c) {\n  b -= a;\n  c -= a;\n  if (cross(b, c) >\
    \ EPS)\n    return 1; // a,b,c\u304C\u6642\u8A08\u56DE\u308A\u306B\u4E26\u3076\
    \u3002\n  if (cross(b, c) < -EPS)\n    return -1; // a,b,c\u304C\u53CD\u6642\u8A08\
    \u56DE\u308A\u306B\u4E26\u3076\u3002\n  if (dot(b, c) < 0)\n    return 2; // c,a,b\u306E\
    \u9806\u306B\u76F4\u7DDA\u306B\u4E26\u3076\u3002\n  if (std::norm(b) < std::norm(c))\n\
    \    return -2; // a,b,c\u306E\u9806\u306B\u76F4\u7DDA\u306B\u4E26\u3076\u3002\
    \n  return 0;    // a,c,b\u306E\u9806\u306B\u76F4\u7DDA\u306B\u4E26\u3076\u3002\
    \n}\n\n/// \u4EA4\u5DEE\u5224\u5B9A\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\u306E\u4EA4\
    \u5DEE\u5224\u5B9A\ninline bool isis_ll(Line l, Line m) { return !eq(cross(l.b\
    \ - l.a, m.b - m.a), 0); }\n// \u76F4\u7DDA\u3068\u7DDA\u5206\u306E\u4EA4\u5DEE\
    \u5224\u5B9A\ninline bool isis_ls(Line l, Line s) {\n  return (cross(l.b - l.a,\
    \ s.a - l.a) * cross(l.b - l.a, s.b - s.a) < EPS);\n}\n// \u70B9\u304C\u76F4\u7DDA\
    \u4E0A\u306B\u5B58\u5728\u3059\u308B\u304B\u306E\u5224\u5B9A\ninline bool isis_lp(Line\
    \ l, Point p) { return (std::abs(cross(l.b - p, l.a - p)) < EPS); }\n// \u70B9\
    \u304C\u7DDA\u5206\u4E0A\u306B\u5B58\u5728\u3059\u308B\u304B\u306E\u5224\u5B9A\
    \ninline bool isis_sp(Line s, Point p) {\n  return (std::abs(s.a - p) + std::abs(s.b\
    \ - p) - std::abs(s.b - s.a) < EPS);\n}\n// \u7DDA\u5206\u3068\u7DDA\u5206\u306E\
    \u4EA4\u5DEE\u5224\u5B9A\ninline bool isis_ss(Line s1, Line s2) {\n  return ccw(s1.a,\
    \ s1.b, s2.a) * ccw(s1.a, s1.b, s2.b) <= 0 &&\n         ccw(s2.a, s2.b, s1.a)\
    \ * ccw(s2.a, s2.b, s1.b) <= 0;\n}\n// \u70B9\u304C\u76F4\u7DDA\u306B\u4E0B\u308D\
    \u3059\u5782\u7DDA\u306E\u8DB3\ninline Point proj(Line l, Point p) {\n  ld t =\
    \ dot(p - l.a, l.a - l.b) / std::norm(l.a - l.b);\n  return l.a + t * (l.a - l.b);\n\
    }\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\u306E\u4EA4\u70B9\u306E\u5EA7\u6A19\ninline\
    \ Point is_ll(Line s, Line t) {\n  Point sv = s.b - s.a, tv = t.b - t.a;\n  assert(cross(sv,\
    \ tv) != 0);\n  return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);\n}\n\n\
    /// \u8DDD\u96E2\n// \u70B9\u3068\u76F4\u7DDA\ninline ld dist_lp(Line l, Point\
    \ p) { return std::abs(p - proj(l, p)); }\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\n\
    inline ld dist_ll(Line l, Line m) { return isis_ll(l, m) ? 0 : dist_lp(l, m.a);\
    \ }\n// \u76F4\u7DDA\u3068\u7DDA\u5206\ninline ld dist_ls(Line l, Line s) {\n\
    \  return isis_ls(l, s) ? 0 : std::min(dist_lp(l, s.a), dist_lp(l, s.b));\n}\n\
    // \u7DDA\u5206\u3068\u70B9\ninline ld dist_sp(Line s, Point p) {\n  Point r =\
    \ proj(s, p);\n  return isis_sp(s, r) ? std::abs(r - p) : std::min(std::abs(s.a\
    \ - p), std::abs(s.b - p));\n}\n// \u7DDA\u5206\u3068\u7DDA\u5206\ninline ld dist_ss(Line\
    \ s, Line t) {\n  if (isis_ss(s, t))\n    return 0;\n  return std::min(\n    \
    \  {dist_sp(s, t.a), dist_sp(s, t.b), dist_sp(t, s.a), dist_sp(t, s.b)});\n}\n\
    \n// \u5186\u3068\u5186\u306E\u4EA4\u70B9\ninline std::vector<Point> is_cc(Circle\
    \ c1, Circle c2) {\n  std::vector<Point> res;\n  ld d = std::abs(c1.p - c2.p);\n\
    \  ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);\n  ld dfr = c1.r * c1.r\
    \ - rc * rc;\n  if (std::abs(dfr) < EPS)\n    dfr = 0.0;\n  if (dfr < 0.0)\n \
    \   return res;\n  ld rs = std::sqrt(dfr);\n  Point dif = (c2.p - c1.p) / d;\n\
    \  res.push_back(c1.p + dif * Point(rc, rs));\n  if (dfr != 0.0)\n    res.push_back(c1.p\
    \ + dif * Point(rc, -rs));\n  return res;\n}\n// \u5186\u3068\u76F4\u7DDA\u306E\
    \u4EA4\u70B9\ninline std::vector<Point> is_lc(Circle c, Line l) {\n  std::vector<Point>\
    \ res;\n  ld d = dist_lp(l, c.p);\n  if (d > c.r + EPS)\n    return res;\n  ld\
    \ len = (d > c.r) ? 0.0 : std::sqrt(c.r * c.r - d * d);\n  Point nor = (l.a -\
    \ l.b) / std::abs(l.a - l.b);\n  res.push_back(proj(l, c.p) + len * nor);\n  res.push_back(proj(l,\
    \ c.p) - len * nor);\n  return res;\n}\n// \u5186\u3068\u7DDA\u5206\u306E\u4EA4\
    \u70B9\ninline std::vector<Point> is_sc(Circle c, Line s) {\n  std::vector<Point>\
    \ v = is_lc(c, s), res;\n  for (int k = 0; k < (int)v.size(); k++)\n    if (ccw(s.a,\
    \ v[k], s.b) == -2)\n      res.push_back(v[k]);\n  return res;\n}\n// \u4E0E\u3048\
    \u3089\u308C\u305F\u70B9\u3092\u901A\u308B\u5186\u306E\u63A5\u70B9\ninline std::vector<Line>\
    \ tangent_cp(Circle c, Point p) {\n  std::vector<Line> res;\n  Point v = c.p -\
    \ p;\n  ld d = std::abs(v);\n  ld l = std::sqrt(std::norm(v) - c.r * c.r);\n \
    \ if (std::isnan(l)) {\n    return res;\n  }\n  Point v1 = v * Point(l / d, c.r\
    \ / d);\n  Point v2 = v * Point(l / d, -c.r / d);\n  res.push_back((Line){p, p\
    \ + v1});\n  if (l < EPS)\n    return res;\n  res.push_back((Line){p, p + v2});\n\
    \  return res;\n}\n// \u5186\u3068\u5186\u306E\u63A5\u7DDA\ninline std::vector<Line>\
    \ tangent_cc(Circle c1, Circle c2) {\n  std::vector<Line> res;\n  if (std::abs(c1.p\
    \ - c2.p) - (c1.r + c2.r) > -EPS) {\n    Point center = (c1.p * c2.r + c2.p *\
    \ c1.r) / (c1.r + c2.r);\n    res = tangent_cp(c1, center);\n  }\n  if (std::abs(c1.r\
    \ - c2.r) > EPS) {\n    Point out = (-c1.p * c2.r + c2.p * c1.r) / (c1.r - c2.r);\n\
    \    std::vector<Line> nres = tangent_cp(c1, out);\n    res.insert(res.end(),\
    \ nres.begin(), nres.end());\n  } else {\n    Point v = c2.p - c1.p;\n    v /=\
    \ std::abs(v);\n    Point q1 = c1.p + v * Point(0, 1) * c1.r;\n    Point q2 =\
    \ c1.p + v * Point(0, -1) * c1.r;\n    res.push_back((Line){q1, q1 + v});\n  \
    \  res.push_back((Line){q2, q2 + v});\n  }\n  return res;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <complex>\n\
    #include <vector>\n#include <cmath>\n\nconstexpr long double EPS = 1e-10;\n\n\
    using ld = long double;\nusing Point = std::complex<ld>;\n\ninline bool eq(Point\
    \ a, Point b) { return (std::abs(a - b) < EPS); }\ninline ld dot(Point a, Point\
    \ b) { return std::real(std::conj(a) * b); }\ninline ld cross(Point a, Point b)\
    \ { return std::imag(std::conj(a) * b); }\n\nstruct Line {\n  Point a, b;\n};\n\
    \nstruct Circle {\n  Point p;\n  ld r;\n};\n\ninline int ccw(Point a, Point b,\
    \ Point c) {\n  b -= a;\n  c -= a;\n  if (cross(b, c) > EPS)\n    return 1; //\
    \ a,b,c\u304C\u6642\u8A08\u56DE\u308A\u306B\u4E26\u3076\u3002\n  if (cross(b,\
    \ c) < -EPS)\n    return -1; // a,b,c\u304C\u53CD\u6642\u8A08\u56DE\u308A\u306B\
    \u4E26\u3076\u3002\n  if (dot(b, c) < 0)\n    return 2; // c,a,b\u306E\u9806\u306B\
    \u76F4\u7DDA\u306B\u4E26\u3076\u3002\n  if (std::norm(b) < std::norm(c))\n   \
    \ return -2; // a,b,c\u306E\u9806\u306B\u76F4\u7DDA\u306B\u4E26\u3076\u3002\n\
    \  return 0;    // a,c,b\u306E\u9806\u306B\u76F4\u7DDA\u306B\u4E26\u3076\u3002\
    \n}\n\n/// \u4EA4\u5DEE\u5224\u5B9A\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\u306E\u4EA4\
    \u5DEE\u5224\u5B9A\ninline bool isis_ll(Line l, Line m) { return !eq(cross(l.b\
    \ - l.a, m.b - m.a), 0); }\n// \u76F4\u7DDA\u3068\u7DDA\u5206\u306E\u4EA4\u5DEE\
    \u5224\u5B9A\ninline bool isis_ls(Line l, Line s) {\n  return (cross(l.b - l.a,\
    \ s.a - l.a) * cross(l.b - l.a, s.b - s.a) < EPS);\n}\n// \u70B9\u304C\u76F4\u7DDA\
    \u4E0A\u306B\u5B58\u5728\u3059\u308B\u304B\u306E\u5224\u5B9A\ninline bool isis_lp(Line\
    \ l, Point p) { return (std::abs(cross(l.b - p, l.a - p)) < EPS); }\n// \u70B9\
    \u304C\u7DDA\u5206\u4E0A\u306B\u5B58\u5728\u3059\u308B\u304B\u306E\u5224\u5B9A\
    \ninline bool isis_sp(Line s, Point p) {\n  return (std::abs(s.a - p) + std::abs(s.b\
    \ - p) - std::abs(s.b - s.a) < EPS);\n}\n// \u7DDA\u5206\u3068\u7DDA\u5206\u306E\
    \u4EA4\u5DEE\u5224\u5B9A\ninline bool isis_ss(Line s1, Line s2) {\n  return ccw(s1.a,\
    \ s1.b, s2.a) * ccw(s1.a, s1.b, s2.b) <= 0 &&\n         ccw(s2.a, s2.b, s1.a)\
    \ * ccw(s2.a, s2.b, s1.b) <= 0;\n}\n// \u70B9\u304C\u76F4\u7DDA\u306B\u4E0B\u308D\
    \u3059\u5782\u7DDA\u306E\u8DB3\ninline Point proj(Line l, Point p) {\n  ld t =\
    \ dot(p - l.a, l.a - l.b) / std::norm(l.a - l.b);\n  return l.a + t * (l.a - l.b);\n\
    }\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\u306E\u4EA4\u70B9\u306E\u5EA7\u6A19\ninline\
    \ Point is_ll(Line s, Line t) {\n  Point sv = s.b - s.a, tv = t.b - t.a;\n  assert(cross(sv,\
    \ tv) != 0);\n  return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);\n}\n\n\
    /// \u8DDD\u96E2\n// \u70B9\u3068\u76F4\u7DDA\ninline ld dist_lp(Line l, Point\
    \ p) { return std::abs(p - proj(l, p)); }\n// \u76F4\u7DDA\u3068\u76F4\u7DDA\n\
    inline ld dist_ll(Line l, Line m) { return isis_ll(l, m) ? 0 : dist_lp(l, m.a);\
    \ }\n// \u76F4\u7DDA\u3068\u7DDA\u5206\ninline ld dist_ls(Line l, Line s) {\n\
    \  return isis_ls(l, s) ? 0 : std::min(dist_lp(l, s.a), dist_lp(l, s.b));\n}\n\
    // \u7DDA\u5206\u3068\u70B9\ninline ld dist_sp(Line s, Point p) {\n  Point r =\
    \ proj(s, p);\n  return isis_sp(s, r) ? std::abs(r - p) : std::min(std::abs(s.a\
    \ - p), std::abs(s.b - p));\n}\n// \u7DDA\u5206\u3068\u7DDA\u5206\ninline ld dist_ss(Line\
    \ s, Line t) {\n  if (isis_ss(s, t))\n    return 0;\n  return std::min(\n    \
    \  {dist_sp(s, t.a), dist_sp(s, t.b), dist_sp(t, s.a), dist_sp(t, s.b)});\n}\n\
    \n// \u5186\u3068\u5186\u306E\u4EA4\u70B9\ninline std::vector<Point> is_cc(Circle\
    \ c1, Circle c2) {\n  std::vector<Point> res;\n  ld d = std::abs(c1.p - c2.p);\n\
    \  ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);\n  ld dfr = c1.r * c1.r\
    \ - rc * rc;\n  if (std::abs(dfr) < EPS)\n    dfr = 0.0;\n  if (dfr < 0.0)\n \
    \   return res;\n  ld rs = std::sqrt(dfr);\n  Point dif = (c2.p - c1.p) / d;\n\
    \  res.push_back(c1.p + dif * Point(rc, rs));\n  if (dfr != 0.0)\n    res.push_back(c1.p\
    \ + dif * Point(rc, -rs));\n  return res;\n}\n// \u5186\u3068\u76F4\u7DDA\u306E\
    \u4EA4\u70B9\ninline std::vector<Point> is_lc(Circle c, Line l) {\n  std::vector<Point>\
    \ res;\n  ld d = dist_lp(l, c.p);\n  if (d > c.r + EPS)\n    return res;\n  ld\
    \ len = (d > c.r) ? 0.0 : std::sqrt(c.r * c.r - d * d);\n  Point nor = (l.a -\
    \ l.b) / std::abs(l.a - l.b);\n  res.push_back(proj(l, c.p) + len * nor);\n  res.push_back(proj(l,\
    \ c.p) - len * nor);\n  return res;\n}\n// \u5186\u3068\u7DDA\u5206\u306E\u4EA4\
    \u70B9\ninline std::vector<Point> is_sc(Circle c, Line s) {\n  std::vector<Point>\
    \ v = is_lc(c, s), res;\n  for (int k = 0; k < (int)v.size(); k++)\n    if (ccw(s.a,\
    \ v[k], s.b) == -2)\n      res.push_back(v[k]);\n  return res;\n}\n// \u4E0E\u3048\
    \u3089\u308C\u305F\u70B9\u3092\u901A\u308B\u5186\u306E\u63A5\u70B9\ninline std::vector<Line>\
    \ tangent_cp(Circle c, Point p) {\n  std::vector<Line> res;\n  Point v = c.p -\
    \ p;\n  ld d = std::abs(v);\n  ld l = std::sqrt(std::norm(v) - c.r * c.r);\n \
    \ if (std::isnan(l)) {\n    return res;\n  }\n  Point v1 = v * Point(l / d, c.r\
    \ / d);\n  Point v2 = v * Point(l / d, -c.r / d);\n  res.push_back((Line){p, p\
    \ + v1});\n  if (l < EPS)\n    return res;\n  res.push_back((Line){p, p + v2});\n\
    \  return res;\n}\n// \u5186\u3068\u5186\u306E\u63A5\u7DDA\ninline std::vector<Line>\
    \ tangent_cc(Circle c1, Circle c2) {\n  std::vector<Line> res;\n  if (std::abs(c1.p\
    \ - c2.p) - (c1.r + c2.r) > -EPS) {\n    Point center = (c1.p * c2.r + c2.p *\
    \ c1.r) / (c1.r + c2.r);\n    res = tangent_cp(c1, center);\n  }\n  if (std::abs(c1.r\
    \ - c2.r) > EPS) {\n    Point out = (-c1.p * c2.r + c2.p * c1.r) / (c1.r - c2.r);\n\
    \    std::vector<Line> nres = tangent_cp(c1, out);\n    res.insert(res.end(),\
    \ nres.begin(), nres.end());\n  } else {\n    Point v = c2.p - c1.p;\n    v /=\
    \ std::abs(v);\n    Point q1 = c1.p + v * Point(0, 1) * c1.r;\n    Point q2 =\
    \ c1.p + v * Point(0, -1) * c1.r;\n    res.push_back((Line){q1, q1 + v});\n  \
    \  res.push_back((Line){q2, q2 + v});\n  }\n  return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: geometry/geometry.hpp
  requiredBy: []
  timestamp: '2026-06-21 13:05:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/geometry.hpp
layout: document
redirect_from:
- /library/geometry/geometry.hpp
- /library/geometry/geometry.hpp.html
title: geometry/geometry.hpp
---
