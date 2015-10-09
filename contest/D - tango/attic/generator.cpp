#include <cstdio>
#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

void usage(char *);
void swap(vector<int>&, int, int);

int main (int argc, char *argv[]) {
	int m = 1, f = 1;
	bool equal = false;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			printf("ERROR: Unknown parameter '%s'\n");
		}
		switch (argv[i][1]) {
		case 'M':
		case 'm':
			m = atoi(&(argv[i][2]));
			break;
		
		case 'F':
		case 'f':
			f = atoi(&(argv[i][2]));
			break;
		
		case 'e':
			equal = true;
			break;
		
		default:
			usage(argv[0]);
			return 0;
		}
	}
	
	typedef chrono::high_resolution_clock clock;
	clock::time_point tp = clock::now();
	default_random_engine gen;
	gen.seed(tp.time_since_epoch().count());
	
	vector<bool> hm(161, false);	// Mark heights between 0.50 and 2.10
	vector<bool> hf(161, false);	// Mark heights between 0.50 and 2.10
	
	int rnd;
	uniform_int_distribution<int> unihm(0, 160);
	for (int i = 0; i < m; i++) {
		do {
			rnd = unihm(gen);
		} while (hm[rnd]);
		hm[rnd] = true;
	}
	
	if (equal) {
		for (int i = 0; i < 161; i++) {
			hf[i] = hm[i];
		}
	}
	else {
		uniform_int_distribution<int> unihf(0, 160);
		for (int i = 0; i < f; i++) {
			do {
				rnd = unihf(gen);
			} while (hf[rnd]);
			hf[rnd] = true;
		}
	}
	
	vector<int> valm;
	vector<int> valf;
	for (int i = 0; i <= 160; i++) {
		if (hm[i]) valm.push_back(i+50);
		if (hf[i]) valf.push_back(i+50);
	}
	
	// Permutations
	for (int i = 0; i < m; i++) {
		uniform_int_distribution<int> perhm(i, m-1);
		swap(valm, i, perhm(gen));
	}
	for (int i = 0; i < f; i++) {
		uniform_int_distribution<int> perhf(i, m-1);
		swap(valf, i, perhf(gen));
	}
	
	printf("%d\n", m);
	printf("%d", valm[0]);
	for (int i = 1; i < m; i++) {
		printf(" %d", valm[i]);
	}
	printf("\n");
	printf("%d", valf[0]);
	for (int i = 1; i < f; i++) {
		printf(" %d", valf[i]);
	}
	printf("\n");
	
	return 0;
}

void swap(vector<int>& v, int i, int j) {
	if (i == j) return;
	v[i] ^= v[j];
	v[j] ^= v[i];
	v[i] ^= v[j];
	return;
}

void usage(char *fname) {
	printf("Usage:\n");
	printf("%s [-Mmen|-mmen] [-Fwom|-fwom] [-e]\n", fname);
	printf("\n");
	printf("men: number of male dancers.\n");
	printf("wom: number of female dancers.\n");
	printf("-e: force balanced heights between men and women.\n");
}