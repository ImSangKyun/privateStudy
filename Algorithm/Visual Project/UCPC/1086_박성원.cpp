#include <iostream>
#include <vector>
#include <string>
using namespace std;

int N, K;
vector<string> arr;
vector<int> val, len, powVal;
long long cache[1 << 15][101];

long long gcd(long long x, long long y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	arr = vector<string>(N);
	val = vector<int>(N);
	len = vector<int>(N);
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
		len[i] = arr[i].size();
	}
	cin >> K;
	//string to int % K
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < len[i]; ++j) {
			val[i] = val[i] * 10 + (arr[i][j] - '0');
			val[i] %= K;
		}
	}

	vector<int> powVal(51);
	powVal[0] = 1;
	for (int i = 1; i <= 50; ++i) {
		powVal[i] = powVal[i - 1] * 10;
		powVal[i] %= K;
	}

	cache[0][0] = 1;
	for (int i = 0; i < (1 << N); ++i) {
		for (int j = 0; j < K; ++j) {
			for (int k = 0; k < N; ++k) {
				if ((i & (1 << k)) == 0) {
					int next = j * powVal[len[k]];
					next %= K;
					next += val[k];
					next %= K;
					cache[i | (1 << k)][next] += cache[i][j];
				}
			}
		}
	}
	long long t1 = cache[(1 << N) - 1][0];
	long long t2 = 1;
	for (long long i = 2; i <= N; ++i)
		t2 *= i;
	long long g = gcd(t1, t2);
	t1 /= g;
	t2 /= g;
	cout << t1 << '/' << t2 << '\n';
	return 0;
}