const double INF = 1e60;
const double eps = 1e-8;
const double pi = acos(-1);

int sgn(double x) { return x < -eps ? -1 : x > eps; }
double Sqr(double x) { return x * x; }
double Sqrt(double x) { return x >= 0 ? std::sqrt(x) : 0; }

struct Vec {
    double x, y, z;
    
    Vec() = default;
    Vec(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
    
    Vec operator + (const Vec &oth) const { return Vec(x + oth.x, y + oth.y, z + oth.z); }
    Vec operator - (const Vec &oth) const { return Vec(x - oth.x, y - oth.y, z - oth.z); }
    Vec operator * (double oth) const { return Vec(x * oth, y * oth, z * oth); }
    Vec operator / (double oth) const { return Vec(x / oth, y / oth, z / oth); }
    
    double len2() const { return Sqr(x) + Sqr(y) + Sqr(z); }
    double len() const { return Sqrt(len2()); }
    
    Vec norm() const { return *this / len(); }
};

double Dot(Vec a, Vec b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Vec Cross(Vec a, Vec b) { return Vec(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

bool InTriangle(Vec p, std::vector<Vec> tri) {
    return sgn(Cross(tri[0] - tri[1], tri[0] - tri[2]).len()
         - Cross(p - tri[0], p - tri[1]).len()
         - Cross(p - tri[1], p - tri[2]).len()
         - Cross(p - tri[2], p - tri[0]).len()) == 0;
}

struct Line {
    Vec a, b;
    
    Line() = default;
    Line(Vec _a, Vec _b): a(_a), b(_b) {}
    
    Vec v() const { return b - a; }
};

Vec Intersect(Line l1, Line l2) {
    double t = ((l1.a.x - l2.a.x) * (l2.a.y - l2.b.y) - (l1.a.y - l2.a.y) * (l2.a.x - l2.b.x))
             / ((l1.a.x - l1.b.x) * (l2.a.y - l2.a.y) - (l1.a.y - l1.b.y) * (l2.a.x - l2.b.x));
    return l1.a + l1.v() * t;
}

Vec Intersect(Line l, std::vector<Vec> flat) {
    Vec p = Cross(flat[1] - flat[0], flat[2] - flat[0]);
    double t = Dot(p, flat[0] - l.a) / Dot(p, l.v());
    return l.a + l.v() * t;
}

bool SameSide(Vec p1, Vec p2, Line l) { // If two points are on the same side of a coplanar line
    return sgn(Dot(Cross(l.v(), p1 - l.a), Cross(l.v(), p2 - l.a))) > 0;
}
