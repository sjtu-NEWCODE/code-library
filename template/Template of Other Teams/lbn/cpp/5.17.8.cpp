// calculate argmin ||AX - B||
solution least_squares(vector<vector<double> > a, vector<double> b) {
	int n = (int)a.size(), m = (int)a[0].size();
	vector<vector<double> > p(m, vector<double>(m, 0));
	vector<double> q(m, 0);
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			for (int k = 0; k < n; ++k)
				p[i][j] += a[k][i] * a[k][j];
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			q[i] += a[j][i] * b[j];
	return gauss_elimination(p, q);
}
