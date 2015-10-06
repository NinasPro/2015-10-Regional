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
	for (int i = 0; i < h; i++) {
		printf("%d %d\n", x[i].first, y[i].first);
	}
	
	return 0;
}