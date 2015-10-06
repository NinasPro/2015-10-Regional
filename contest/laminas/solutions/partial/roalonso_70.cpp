#include <cstdio>
#include <vector>

int main() {
	int n, s, p;
	int u, c;
	int min;
	
	scanf("%d %d %d", &n, &s, &p);
	
	if (s <= 2) {
		c = 0;
		
		std::vector<int> lam(n);
		
		for (int i = 0; i < n; i++) {
			scanf("%d", &(lam[i]));
			c += lam[i];
		}
		min = c;
		
		for (int i = 0; i < s; i++) {
			if (s == 2) {
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
	}
	else if (s <= 100) {
		printf("%d\n", s*p);
		return 0;
	}
	else {
		c = 0;
		
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
	}
	
	printf("%d\n", min);
	return 0;
}
