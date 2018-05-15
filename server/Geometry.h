#ifndef GEOMETRY_H_9DUX6CK4
#define GEOMETRY_H_9DUX6CK4

#include <cstdint>
#include <cmath>
#include <algorithm>

/*
 * x: left to right
 * y: bottom to top
 *
 */

namespace ConnectDots {
typedef int64_t Int;

struct Point {
    Int x, y;
    Int dist2() const {
        return x * x + y * y;
    }
    Int dist() const {
        return hypot(x, y);
    }
};
inline Point operator+(Point p1, Point p2) {
    return Point{p1.x + p2.x, p1.y + p2.y};
}
inline Point operator-(Point p1, Point p2) {
    return Point{p1.x - p2.x, p1.y - p2.y};
}
inline Int ccw(Point v1, Point v2) {
    return v1.x * v2.y - v1.y * v2.x;
}
inline Int ccw(Point p1, Point p2, Point p3) {
    return ccw(p2 - p1, p3 - p2);
}

struct Line {
    Point p[2];
    double distTo(Point q) const {
        return 1.0 * abs(ccw(q, p[0], p[1])) / (p[0] - p[1]).dist();
    }
};

inline bool HasIntersection(Line ln1, Line ln2) {
    return ccw(ln1.p[0], ln1.p[1], ln2.p[0]) * ccw(ln1.p[0], ln1.p[1], ln2.p[1]) < 0 &&
           ccw(ln2.p[0], ln2.p[1], ln1.p[0]) * ccw(ln2.p[0], ln2.p[1], ln1.p[1]) < 0;
}
inline bool Inside(Point p1, Point p2, Point p3, Point q) {
    if (ccw(p1, p2, p3) < 0)
        std::swap(p2, p3);
    return ccw(p1, p2, q) > 0 && ccw(p2, p3, q) > 0 && ccw(p3, p1, q) > 0;
}

struct Triangle {
    Point p[3];
    Int Area() const {
        return ccw(p[0], p[1], p[2]);
    }
};

} // namespace ConnectDots

#endif /* end of include guard: GEOMETRY_H_9DUX6CK4 */
