#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, M;
vector<vector<char>> arr;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	arr = vector<vector<char>>(N, vector<char>(M));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> arr[i][j];
		}
	}

	int res = 64;	//절대 나올 수 없는 큰 값
	for (int i = 0; i <= N - 8; ++i) {
		for (int j = 0; j <= M - 8; ++j) {
			int cnt = 0;

			for (int a = 0; a < 8; ++a) {
				for (int b = 0; b < 8; ++b) {
					cnt += (a % 2 == b % 2 ? 'W' : 'B') == arr[i + a][j + b];
				}
			}
			res = min(res, cnt);
			res = min(res, 64 - cnt);
		}
	}
	cout << res << '\n';
}