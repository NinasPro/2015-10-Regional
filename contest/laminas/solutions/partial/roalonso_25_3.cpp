#include <cstdio>
#include <vector>

int main() {
	int n, s, p;
	int u;
	int min;
	
	scanf("%d %d %d", &n, &s, &p);
	
	int c = 0;
	
	int lam;
	std::vector<bool> have(n+1, false);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &lam);
	}
	min = c = n*lam;
	
	for (int i = 0; i < s; i++) {
		if (s == 2) {
			break;
		}
		c += p;
		for (int j = 0; j < 5; j++) {
			scanf("%d", &u);
			if (!have[u]) {
				c -= lam;
				have[u] = true;
			}
		}
		if (min > c) {
			min = c;
		}
	}
	
	printf("%d\n", min);
	return 0;
}
