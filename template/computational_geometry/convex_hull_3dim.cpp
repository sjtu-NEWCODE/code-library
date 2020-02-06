std::vector<std::vector<Vec>> ConvexHull(std::vector<Vec> ps) {
    int n = ps.size();
    std::vector<std::vector<int>> vs(n, std::vector<int>(n));
    std::vector<std::vector<int>> crt;
    crt.push_back({0, 1, 2});
    crt.push_back({2, 1, 0});
    for (int i = 3; i < n; ++i) {
        std::vector<std::vector<int>> nxt;
        for (auto t: crt) {
            int v = (Cross(ps[t[1]] - ps[t[0]], ps[t[2]] - ps[t[0]]), ps[i] - ps[t[0]]) < 0 ? -1 : 1;
            if (v < 0) nxt.push_back(t);
            for (int j = 0; j < 3; ++j) {
                if (vs[t[(j + 1) % 3]][t[j]] == 0) {
                    vs[t[j]][t[(j + 1) % 3]] = v;
                } else {
                    if (vs[t[(j + 1) % 3]][t[j]] != v) {
                        if (v > 0) next.push_back({t[j], t[(j + 1) % 3], i});
                        else next.push_back({t[(j + 1) % 3], t[j], i});
                    }
                    vs[t[(j + 1) % 3]][t[j]] = 0;
                }
            }
        }
        crt = nxt;
    }
    std::vector<std::vector<Vec>> pss(crt.size(), std::vector<Vec>(3));
    for (int i = 0; i < (int)pss.size(); ++i)
        for (int j = 0; j < 3; ++j)
            pss[i][j] = ps[crt[i][j]];
    return pss;
}
