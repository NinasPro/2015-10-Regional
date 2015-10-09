#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main (int argc, char *argv[]) {
	int n;
	
	scanf("%d", &n);
	
	if (n > 2) n = 2;
	
	vector<pair<int,int> > x(2);
	vector<pair<int,int> > y(2);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &(x[i].first));
		x[i].second = i;
	}
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &(y[i].first));
		y[i].second = i;
	}
	
	// Ordenamiento
	if (n == 2 && x[0].first > x[1].first) {
		pair<int,int> tmp = x[0];
		x[0] = x[1];
		x[1] = tmp;
	}
	if (n == 2 && y[0].first > y[1].first) {
		pair<int,int> tmp = y[0];
		y[0] = y[1];
		y[1] = tmp;
	}
	
	// Procesamiento de datos
	int l = 0;
	int u = n - 1;
	for (int i = 0; i <= n; i++) {
		if (x[i].first >= y[l].first) {
			// Parejas según criterio
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