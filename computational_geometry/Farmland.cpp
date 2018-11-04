#include <bits/stdc++.h>

using LL = long long;

const double eps = 1e-6;

int sgn(double x) { return x < -eps ? -1 : x > eps; }

struct Vec {
    LL x, y;
    
    Vec() = default;
    Vec(LL _x, LL _y): x(_x), y(_y) {}
    
    bool operator == (const Vec &oth) const { return x == oth.x && y == oth.y; }
    
    Vec operator + (const Vec &oth) const { return Vec(x + oth.x, y + oth.y); }
    Vec operator - (const Vec &oth) const { return Vec(x - oth.x, y - oth.y); }
    
    double angle() const { return std::atan2(y, x); }
};

LL Dot(Vec a, Vec b) { return a.x * b.x + a.y * b.y; }
LL Cross(Vec a, Vec b) { return a.x * b.y - a.y * b.x; }

const int MAXN = 2e5 + 5;
const int MAXM = 1e6 + 5;

int n, m;
Vec p[MAXN];

std::vector<std::pair<int, int>> G[MAXN];

struct Query {
    int opt, e_id;
    
    Query() = default;
    Query(int _o, int _e): opt(_o), e_id(_e) {}
} qrys[MAXM];

std::map<std::pair<int, int>, int> edgeID;
std::vector<std::pair<int, int>> edges;

int prev[MAXM << 1];
int leftArea[MAXM << 1], areaCnt = 0;
int fa[MAXM << 1];
LL area[MAXM << 1];

int Fa(int x) {
    return fa[x] == x ? x : fa[x] = Fa(fa[x]);
}

int DFS(int u, int v, int now) {
    if (leftArea[now]) return u;
    leftArea[now] = areaCnt;
    
    int nxt = prev[now ^ 1];
    int st = DFS(edges[nxt].first, edges[nxt].second, nxt);
    
    area[areaCnt] += Cross(p[u] - p[st], p[v] - p[st]);
    
    return st;
}

std::vector<LL> ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", &p[i].x, &p[i].y);
    
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        static int opt, u, v;
        
        scanf("%d%d%d", &opt, &u, &v); ++u, ++v;
        
        if (opt == 1) {
            G[u].emplace_back(v, edges.size());
            edgeID.insert({{u, v}, edges.size()});
            edges.emplace_back(u, v);
            
            G[v].emplace_back(u, edges.size());
            edgeID.insert({{v, u}, edges.size()});
            edges.emplace_back(v, u);
        }
        
        qrys[i] = Query(opt, edgeID[{u, v}]);
    }
    
    for (int i = 1; i <= n; ++i) if (!G[i].empty()) {
        static double angles[MAXN];
        
        for (auto e: G[i])
            angles[e.first] = (p[e.first] - p[i]).angle();
        
        std::sort(G[i].begin(), G[i].end(), [&] (std::pair<int, int> a, std::pair<int, int> b) {
            return sgn(angles[a.first] - angles[b.first]) == 0 ? Cross(p[a.first] - p[i], p[b.first] - p[i]) > 0 : sgn(angles[a.first] - angles[b.first]) < 0;
        });
        
        prev[G[i].front().second] = G[i].back().second;
        for (int j = 1; j < (int)G[i].size(); ++j)
            prev[G[i][j].second] = G[i][j - 1].second;
    }
    
    for (int i = 0; i < (int)edges.size(); ++i) if (!leftArea[i]) {
        ++areaCnt;
        DFS(edges[i].first, edges[i].second, i);
        
        if (area[areaCnt] <= 0) area[areaCnt] = -1;
    }
    
    for (int i = 1; i <= areaCnt; ++i) fa[i] = i;
    
    for (int i = m; i >= 1; --i) {
        if (qrys[i].opt == 0) {
            ans.push_back(area[Fa(leftArea[qrys[i].e_id])]);
        } else {
            int e = qrys[i].e_id;
            
            int u = Fa(leftArea[e]), v = Fa(leftArea[e ^ 1]);
            
            if (u == v) continue;
            
            if (area[u] == -1 || area[v] == -1) area[v] = -1;
            else area[v] += area[u];
            
            fa[u] = v;
        }
    }
    
    std::reverse(ans.begin(), ans.end());
    for (LL i: ans)
        printf("%lld\n", i);
    
    return 0;
}
