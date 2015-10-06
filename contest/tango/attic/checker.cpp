#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#define M 0
#define F 1

using namespace std;

int wrong_ans() {
	cout << "0.0\n";
	return 0;
}

int right_ans() {
	cout << "1.0\n";
	return 0;
}

int main (int argc, char *argv[]) {
	ifstream fin;  	// Input
	ifstream fcorr;	// Expected
	ifstream ftest;	// Submission

	int n;         	// Number of pairs

	fin.open(argv[1]);
	fcorr.open(argv[2]);
	ftest.open(argv[3]);

	if (!fin.is_open()) {
		cerr << "Could not open file \"" << argv[1] << "\".\n";
		return 1;
	}

	if (!fcorr.is_open()) {
		cerr << "Could not open file \"" << argv[2] << "\".\n";
		return 2;
	}

	if (!ftest.is_open()) {
		cerr << "Could not open file \"" << argv[3] << "\".\n";
		return 3;
	}

	fin >> n;

	vector<int> mm(161, 0);
	vector<int> ff(161, 0);

	int h;

	for (int i = 0; i < n; i++) {
		fin >> h;
		mm[h-50]++;
	}

	for (int i = 0; i < n; i++) {
		fin >> h;
		ff[h-50]++;
	}

	fin.close();

	int r = 0;     	// Maximum number of couples

	char str[12];  	// Buffer

	do {
		fcorr.getline(str, 12);
		if (strlen(str) > 0) r++;
	} while (!(fcorr.rdstate() & ifstream::eofbit));

	fcorr.close();

	int state = M;

	int c;
	int hm = 0, hf = 0;
	// int cnt = 0;

	while (true) {
		c = ftest.get();
		switch (c) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			if (state == M) {
				hm *= 10;
				hm += c - '0';
				if (hm > 210) {
					cerr << "Altura de uno de los hombres (" << hm << ") es mayor que 210 cm.\n";
					return wrong_ans();
				}
			}
			else {
				hf *= 10;
				hf += c - '0';
				if (hf > 210) {
					cerr << "Altura de una de las mujeres (" << hf << ") es mayor que 210 cm.\n";
					return wrong_ans();
				}
			}
			break;

		case ' ':
			if (state == M) {
				// Check if height is valid and available
				if (hm < 50) {
					cerr << "Altura de uno de los hombres (" << hm << ") es menor que 50.\n";
					return wrong_ans();
				}
				if (mm[hm-50]-- == 0) {
					cerr << "Asignaste más hombres de altura " << hm << " de los que hay.\n";
					return wrong_ans();
				}
				state = F;
			}
			else {
				cerr << "Error de formato: hay más de dos números en una línea.\n";
				return wrong_ans();
			}
			break;

		case EOF:
			if (state == M && hm == 0) {
				goto endloop;
			}
// 			break;

		case '\n':
			if (state == F) {
				// Check if height is valid and available
				if (hf < 50) {
					cerr << "Altura de una de las mujeres (" << hf << ") es menor que 50.\n";
					return wrong_ans();
				}
				if (ff[hf-50]-- == 0) {
					cerr << "Asignaste más mujeres de altura " << hf << " de las que hay.\n";
					return wrong_ans();
				}
				// Check if pair satisfies condition
				if (hm < hf) {
					cerr << "Una pareja no satisface la condición de Vardieri.\n";
					return wrong_ans();
				}
				// Add to count
				r--;
				// Reset variables
				hm = 0; hf = 0;
				state = M;
			}
			else {
				cerr << "Error de formato: hay un solo número en una línea.\n";
				return wrong_ans();
			}
			break;

		default:
			cerr << "Error de formato: símbolo \'" << (char)c << "\' desconocido.\n";
			return wrong_ans();
		}
	}
	endloop:

	if (r != 0) {
		cerr << "Número de parejas es subóptimo.\n";
		return wrong_ans();
  }

	return right_ans();
}
