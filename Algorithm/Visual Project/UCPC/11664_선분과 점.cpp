#include <stdio.h>
#include <algorithm>
using namespace std;

typedef double db;

struct pt {
	db x, y, z;
	pt(db x = 0, db y = 0, db z = 0) : x(x), y(y), z(z) {}
	pt operator-(const pt &a) { return pt(x - a.x, y - a.y, z - a.z); }
	//����
	pt operator*(const pt &a) { return pt(y*a.z - z * a.y, z*a.x - x * a.z, x*a.y - y * a.x); }
	//����
	db operator|(const pt &a) { return x * a.x + y * a.y + z * a.z; }
};

//���� ����
db mul(pt a) { return sqrt(a | a); }

int main() {
	pt a[3];
	for (int i = 0; i < 3; i++) scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].z);
	pt b = a[1] - a[0], c = a[2] - a[0], d = a[2] - a[1];
	//�ִܰŸ��� ������ �̿��Ѵ�.
	if ((b | c)*(b | d) <= 0) printf("%.10lf\n", mul(b*c) / mul(b));
	else printf("%.10lf\n", min(mul(c), mul(d)));
	return 0;
}
