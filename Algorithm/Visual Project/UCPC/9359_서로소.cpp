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

void eratos(int N) {	//�����佺�׳׽��� ü
	vector<long long> cache(N + 1, 1);
	for (int i = 2; i <= N; ++i) {
		if (cache[i]) {
			prime.push_back(i);
			for (int j = i + 1; j <= N; j += i)	cache[j] = 0;
		}
	}
}

//����-���� �˰��� ����Լ�
long long recurse(int i, long long soFar, long long bnd) {
	if (i == divisors.size() || divisors[i] * soFar > bnd)	return 0;
	long long ret = (bnd / divisors[i]) / soFar;
	ret += recurse(i + 1, soFar, bnd);
	ret -= recurse(i + 1, divisors[i] * soFar, bnd);
	return ret;
}

int solution(int A, int B, int N) {
	
	/* �Ҽ��� ��� ������ */
	while (N > 1) {
		bool divided = false;
		for (auto iter : prime) {
			if (N%iter == 0) {	//�Ҽ��� ������ �� ���
				N /= iter;
				cacheMap[iter] = 1;	//map�� {�Ҽ�, 1} �� �ش� ������ ������ ������ �߰�
				divided = true;
				//break;
			}
		}
		if (!divided) break;
	}
	if (N != 1)	cacheMap[N] = 1;	//�������� 1�� �ƴҰ�� ù��° ���� ū ���μ��̹Ƿ� cacheMap�� ���μ��ν� ����

	for (auto iter = cacheMap.begin(); iter != cacheMap.end(); ++iter)
		divisors.push_back((*iter).first);	//���μ� �ߺ����� �ʰ� ����
	
	//����-���� �˰��� (With Bitmask)
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

		long long aa = (A + sum - 1) / sum;	//���۰� + ������
		long long bb = B / sum;	//�ִ� ���Ѽ�
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