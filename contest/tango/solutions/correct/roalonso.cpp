#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main (int argc, char *argv[]) {
	int n;
	
	scanf("%d", &n);
	
	vector<pair<int,int> > x(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &(x[i].first));
		x[i].second = i;
	}
	
	vector<pair<int,int> > y(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &(y[i].first));
		y[i].second = i;
	}
	
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	
	int l = 0;
	int u = n - 1;
	for (int i = 0; i < n; i++) {
		if (x[i].first >= y[l].first) {
			// Parejas que cumplen criterio
			printf("%d %d\n", x[i].first, y[l].first);
			l++;
		}
		else {
			// Parejas que no cumplen criterio
//  			printf("%d %d\n", x[i].second, y[u].second);
			u--;
		}
		if (l > u) break;
	}
	
	return 0;
}