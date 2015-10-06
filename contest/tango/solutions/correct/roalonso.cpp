#include <vector>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

int main (int argc, char *argv[]) {
	
	// Entrada
	int h, w;
	
// 	scanf("%d %d", &h, &w);
	scanf("%d", &h);
	
	vector<pair<int,int> > x(h);
	vector<pair<int,int> > y(h);
	
	for (int i = 0; i < h; i++) {
		scanf("%d", &(x[i].first));
		x[i].second = i;
	}
	
	for (int i = 0; i < h; i++) {
		scanf("%d", &(y[i].first));
		y[i].second = i;
	}
	
	// Ordenamiento
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	
	// Procesamiento de datos
	int l = 0;
	int u = h - 1;
	for (int i = 0; i < h; i++) {
		if (x[i].first > y[l].first) {
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