#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

const double EPS = 1e-9;
 
int sign(const double x, const double eps = EPS) {
    return x < -eps ? -1 : x > eps;
}

struct Point {
    double x, y;
 
    Point (const double &x = 0, const double &y = 0) : x(x), y(y) {}
 
    void in() {
        scanf("%lf%lf", &x, &y);
    }
 
    double len2() {
        return x * x + y * y;
    }
 
    double len() {
        return sqrt(x * x + y * y);
    }

    Point turn90() {
        return Point(-y, x);
    }

    Point norm() {
        double l = len();
        return Point(x / l, y / l);
    }
    
    int quad() const {
        return sign(y) == 1 || sign(y) == 0 && sign(x) >= 0;
    } 
};
 
Point operator + (const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}
 
Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}
 
Point operator * (const Point &a, const double &k) {
    return Point(a.x * k, a.y * k);
}
 
Point operator / (const Point &a, const double &k) {
    return Point(a.x / k, a.y / k);
}
 
double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
 
double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
 
struct Line {
    Point a, b;
 
    void in() {
        a.in(), b.in();
    }
 
    Line(const Point a = Point(0, 0), const Point b = Point(0, 0)) : a(a), b(b) {}

    bool include(const Point &p) const {
        return sign(det(b - a, p - a)) > 0;
    }

    Line push() {
        const double eps = 1e-6;
        Point delta = (b - a).turn90().norm() * eps;
        return Line(a - delta, b - delta);
    }
    

};
 
bool parallel(const Line &l0, const Line &l1) {
    return sign(det(l0.b - l0.a, l1.b - l1.a)) == 0;
}

bool sameDir(const Line &l0, const Line &l1) {
    return parallel(l0, l1) && sign(dot(l0.b - l0.a, l1.b - l1.a)) == 1;
}
 
Point intersect(const Line &l0, const Line &l1) {
    double s1 = det(l0.b - l0.a, l1.a - l0.a),
           s2 = det(l0.b - l0.a, l1.b - l0.a);
    return (l1.a * s2 - l1.b * s1) / (s2 - s1);
}

bool operator < (const Point &a, const Point &b) {
    if (a.quad() != b.quad()) {
        return a.quad() < b.quad();
    } else {
        return sign(det(a, b)) > 0;
    }
}

bool operator < (const Line &l0, const Line &l1) {
    if (sameDir(l0, l1)) {
        return l1.include(l0.a);
    } else {
        return (l0.b - l0.a) < (l1.b - l1.a);
    }
}

bool check(const Line &u, const Line &v, const Line &w) {
    return w.include(intersect(u, v));
}

vector<Point> intersection(vector<Line> &l) {
    sort(l.begin(), l.end());
    deque<Line> q;
    for (int i = 0; i < (int)l.size(); ++i) {
        if (i && sameDir(l[i], l[i - 1])) {
            continue;
        }
        while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i])) {
            q.pop_back();
        }
        while (q.size() > 1 && !check(q[1], q[0], l[i])) {
            q.pop_front();
        }
        q.push_back(l[i]);
    } 
    while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0])) {
        q.pop_back();
    }
    while (q.size() > 2 && !check(q[1], q[0], q[q.size() - 1])) {
        q.pop_front();
    }
    vector<Point> ret;
    for (int i = 0; i < (int)q.size(); ++i) {
        ret.push_back(intersect(q[i], q[(i + 1) % q.size()]));
    }
    return ret;
}

int main() {
    return 0;
}