#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	const double PI = 3.14159265358979;
	int R;
	cin >> R;
	
	cout << fixed;		//cout.precision �� �Ҽ������� 6�ڸ��� �ǵ��� ����. (�̸� ������� ������� �Ҽ����� 6�ڸ��� �ƴ϶� �����κе� ���Ͽ� 6�ڸ��� �ǵ��� �ϴ� ��)
	cout.precision(6);	//�Ҽ��� 6�ڸ� ���� ��� �� ����
	cout << R * R*PI << '\n';
	cout << pow(R * 2, 2) / 2 << '\n';
}