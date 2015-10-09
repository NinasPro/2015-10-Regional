#include <cstdio>
#include <vector>

int main() {
	int n, s, p;
	int u;
	int min;

	scanf("%d %d %d", &n, &s, &p);

	if (s > 2) {
		printf("%d\n", s*p);
		return 0;
	}

	int c = 0;

	std::vector<int> lam(n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &(lam[i]));
		c += lam[i];
	}
	min = c;

	for (int i = 0; i < s; i++) {
		if (i == 2) {
			break;
		}
		c += p;
		for (int j = 0; j < 5; j++) {
			scanf("%d", &u);
			c -= lam[u-1];
			lam[u-1] = 0;
		}
		if (min > c) {
			min = c;
		}
	}

	printf("%d\n", min);
	return 0;
}
