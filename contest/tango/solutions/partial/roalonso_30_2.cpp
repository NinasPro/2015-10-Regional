#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main (int argc, char *argv[]) {
	int n;
	
	scanf("%d", &n);
	
	vector<pair<int,int> > x(n);
	vector<pair<int,int> > y(n);
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &(x[i].first));
		x[i].second = i;
	}
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &(y[i].first));
		y[i].second = i;
	}
	
	sort(x.begin(), x.end());
	
	for (int i = 0; i < n; i++) {
		printf("%d %d\n", x[i].first, x[i].first);
	}
	
	return 0;
}