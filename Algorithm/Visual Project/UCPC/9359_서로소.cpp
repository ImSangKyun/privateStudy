#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

int T;
struct node {
	long long A, B, N;
};
typedef struct node Node;

vector<long long> prime, divisors;
vector<Node> arr;
map<long long, int> cacheMap;

void eratos(int N) {	//에라토스테네스의 체
	vector<long long> cache(N + 1, 1);
	for (int i = 2; i <= N; ++i) {
		if (cache[i]) {
			prime.push_back(i);
			for (int j = i + 1; j <= N; j += i)	cache[j] = 0;
		}
	}
}

//포함-배제 알고리즘 재귀함수
long long recurse(int i, long long soFar, long long bnd) {
	if (i == divisors.size() || divisors[i] * soFar > bnd)	return 0;
	long long ret = (bnd / divisors[i]) / soFar;
	ret += recurse(i + 1, soFar, bnd);
	ret -= recurse(i + 1, divisors[i] * soFar, bnd);
	return ret;
}

int solution(int A, int B, int N) {
	
	/* 소수로 계속 나누기 */
	while (N > 1) {
		bool divided = false;
		for (auto iter : prime) {
			if (N%iter == 0) {	//소수로 나누어 질 경우
				N /= iter;
				cacheMap[iter] = 1;	//map에 {소수, 1} 로 해당 값으로 나누어 졌음을 추가
				divided = true;
				//break;
			}
		}
		if (!divided) break;
	}
	if (N != 1)	cacheMap[N] = 1;	//마지막에 1이 아닐경우 첫번째 가장 큰 소인수이므로 cacheMap에 소인수로써 저장

	for (auto iter = cacheMap.begin(); iter != cacheMap.end(); ++iter)
		divisors.push_back((*iter).first);	//소인수 중복되지 않게 추출
	
	//포함-배제 알고리즘 (With Bitmask)
	long long ans = 0;
	/*
	long long bits = 1 << divisors.size();
	for (int i = 1; i < bits; ++i) {
		long long cnt = 0, sum = 1;
		for (int j = 0; j < divisors.size(); ++j) {
			if (!(i & (1 << j)))	continue;
			++cnt;
			sum *= divisors[j];
		}

		long long aa = (A + sum - 1) / sum;	//시작값 + 누적값
		long long bb = B / sum;	//최대 상한선
		if (aa > bb)	continue;
		if (cnt & 1)	ans += bb - aa + 1;
		else		ans -= bb - aa + 1;
	}
	*/
	ans = recurse(0, 1, B) - recurse(0, 1, A - 1);
	return B - A + 1 - ans;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	eratos((int)sqrt(1000000000));
	cin >> T;
	arr = vector<Node>(T);
	for (int i = 0; i < T; ++i) {
		cin >> arr[i].A >> arr[i].B >> arr[i].N;
	}

	for (int i = 0; i < T; ++i) {
		divisors.clear();
		cacheMap.clear();
		cout << "Case #" << i+1 << ": " << solution(arr[i].A, arr[i].B, arr[i].N) << '\n';
	}
}