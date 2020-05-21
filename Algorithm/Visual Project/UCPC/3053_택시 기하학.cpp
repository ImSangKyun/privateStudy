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
	
	cout << fixed;		//cout.precision 이 소숫점으로 6자리가 되도록 변경. (이를 사용하지 않을경우 소숫점만 6자리가 아니라 정수부분도 합하여 6자리가 되도록 하는 식)
	cout.precision(6);	//소숫점 6자리 까지 출력 후 버림
	cout << R * R*PI << '\n';
	cout << pow(R * 2, 2) / 2 << '\n';
}