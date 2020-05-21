#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int n;
const int INF = 987654321;
vector<pair<int, int>> arr;	//x, y
vector<pair<int, int>> subarr;

int func(int start, int end) {
	if (end - start + 1 < 10) {    //�ʹ����� �������� �ɰ����� �ʵ��� ������ ũ�⿡���� ����Ž��
		int dis = INF;
		for (int i = start; i <= end - 1; ++i) {
			for (int j = i + 1; j <= end; ++j) {
				dis = min(dis, static_cast<int>(pow(arr[i].first - arr[j].first, 2) + pow(arr[i].second - arr[j].second, 2)));
			}
		}
		return dis;
	}

	int mid = (start + end) / 2;
	int dis = min(func(start, mid), func(mid + 1, end));    //Left, Right

	subarr.clear();
	/*
	 * �߰��� �������� dis(�ּҰŸ��� ����)���� ������츸 subarr �߰�
	 */
	for (int i = mid; i <= end; ++i) {
		if (pow(arr[i].first - arr[mid].first, 2) < dis)
			subarr.push_back(arr[i]);
		else	break;
	}
	for (int i = mid - 1; i >= start; --i) {
		if (pow(arr[i].first - arr[mid].first, 2) < dis)
			subarr.push_back(arr[i]);
		else	break;
	}


	std::sort(subarr.begin(), subarr.end(), [](pair<int, int> a, pair<int, int> b) -> bool {
		if (a.second == b.second) {
			return a.first < b.first;
		}
		return a.second < b.second;
	}); //y��ǥ�� �������� Sort
	
	for (int i = 0; i < subarr.size(); ++i) {
		for (int j = i + 1; j < subarr.size(); ++j) {
			if (pow(subarr[i].second - subarr[j].second, 2) < dis) {
				dis = min(dis, static_cast<int>(pow(subarr[i].first - subarr[j].first, 2) + pow(subarr[i].second - subarr[j].second, 2)));
			}
			else //y��ǥ ������ ������ dis(�ּҰŸ��� ����) ���� Ŭ ��� break
				break;
		}
	}
	return dis;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;

	arr = vector<pair<int, int>>(n);

	for (int i = 0; i < n; ++i)
		cin >> arr[i].first >> arr[i].second;

	std::sort(arr.begin(), arr.end(), [](pair<int, int> a, pair<int, int> b) -> bool {
		if (a.first == b.first) {
			return a.second < b.second;
		}
		return a.first < b.first;
	});	//x��ǥ�� �������� ����
	int res = func(0, arr.size() - 1);
	cout << res << '\n';
}