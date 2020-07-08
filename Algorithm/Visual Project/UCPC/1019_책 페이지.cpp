#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

long long res[10];	// 0 ~ 9

void calc(long long n, long long unit) {
	while (n > 0) {
		res[n % 10] += unit;
		n /= 10;
	}
}

int main(void) {
	int start, end, unit;
	start = unit = 1;
	scanf("%d", &end);

	while (start <= end) {
		while (start % 10 != 0 && start <= end) {
			calc(start, unit);
			start += 1;
		}
		if (start > end)	break;
		while (end % 10 != 9 && start <= end) {
			calc(end, unit);
			end -= 1;
		}
		long long cnt = (end / 10 - start / 10 + 1);
		for (int i = 0; i < 10; ++i) {
			res[i] += cnt * unit;
		}
		start /= 10;
		end /= 10;
		unit *= 10;
	}
	for (int i = 0; i < 10; ++i)
		printf("%d ", res[i]);
	printf("\n");
	
	return 0;
}