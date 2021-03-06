const double pi = acos(-1.0);
int n, m; char ch1; bool flag;
double a[4][4], s1, s2, x, y, z, w, b[4][4], c[4][4];
int main() {
	scanf("%d\n", &n);
	memset(b, 0, sizeof(b));
	b[0][0] = b[1][1] = b[2][2] = b[3][3] = 1;//initial matrix
	for(int i = 1; i <= n; i++) {
		scanf("%c", &ch1);
		if(ch1 == 'T') {
			scanf("%lf %lf %lf\n", &x, &y, &z);//plus each coordinate by a number (x, y, z)
			memset(a, 0, sizeof(a));
			a[0][0] = 1; a[3][0] = x;
			a[1][1] = 1; a[3][1] = y;
			a[2][2] = 1; a[3][2] = z;
			a[3][3] = 1;
		} else if(ch1 == 'S') {
			scanf("%lf %lf %lf\n", &x, &y, &z);//multiply each coordinate by a number (x, y, z)
			memset(a, 0, sizeof(a));
			a[0][0] = x; a[1][1] = y; a[2][2] = z; a[3][3] = 1;
		} else {
			scanf("%lf %lf %lf %lf\n", &x, &y, &z, &w);
			/* 大拇指指向x轴正方向时，4指弯曲由y轴正方向指向z轴正方向
			大拇指沿着原点到点(x, y, z)的向量，4指弯曲方向旋转w度 */
			w = w * pi / 180;
			memset(a, 0, sizeof(a));
			s1 = x * x + y * y + z * z;
			a[3][3] = 1;
			a[0][0] = ((y*y+z*z)*cos(w)+x*x)/s1;			a[0][1] = x*y*(1-cos(w))/s1+z*sin(w)/sqrt(s1);	a[0][2] = x*z*(1-cos(w))/s1-y*sin(w)/sqrt(s1);
			a[1][0] = x*y*(1-cos(w))/s1-z*sin(w)/sqrt(s1);	a[1][1] = ((x*x+z*z)*cos(w)+y*y)/s1;			a[1][2] = y*z*(1-cos(w))/s1+x*sin(w)/sqrt(s1);
			a[2][0] = x*z*(1-cos(w))/s1+y*sin(w)/sqrt(s1);	a[2][1] = y*z*(1-cos(w))/s1-x*sin(w)/sqrt(s1);	a[2][2] = ((x*x+y*y)*cos(w)+z*z)/s1;
		}
		memset(c, 0, sizeof(c));
		for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) for(int k = 0; k < 4; k++)
			c[i][j] += b[i][k] * a[k][j];
		memcpy(b, c, sizeof(c));
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		scanf("%lf%lf%lf", &x, &y, &z);//initial vector
		printf("%lf %lf %lf\n", x * b[0][0] + y * b[1][0] + z * b[2][0] + b[3][0],
								x * b[0][1] + y * b[1][1] + z * b[2][1] + b[3][1],
								x * b[0][2] + y * b[1][2] + z * b[2][2] + b[3][2]);
	}
	return 0;
}
// 求平面和直线的交点
Point3D intersection(const Point3D &a, const Point3D &b, const Point3D &c, const Point3D &l0, const Point3D &l1) {
	Point3D p = pVec(a, b, c); // 平面法向量
	double t = (p.x * (a.x - l0.x) + p.y * (a.y - l0.y) + p.z * (a.z - l0.z)) / (p.x * (l1.x - l0.x) + p.y * (l1.y - l0.y) + p.z * (l1.z - l0.z));
	return l0 + (l1 - l0) * t;
}
