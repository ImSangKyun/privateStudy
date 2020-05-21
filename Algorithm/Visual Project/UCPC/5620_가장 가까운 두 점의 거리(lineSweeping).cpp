#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int N;
const int INF = 987654321;
vector<pair<int, int>> arr;

int calcDistance(pair<int, int>&a, pair<int, int>& b) {
	return (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second);
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	arr = vector<pair<int, int>>(N);
	for (int i = 0; i < N; ++i) 
		cin >> arr[i].first >> arr[i].second;
	
	std::sort(arr.begin(), arr.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
		if (a.first == b.first)
			return a.second < b.second;
		else
			return a.first < b.first;
	});


}