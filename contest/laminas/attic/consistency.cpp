/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * -----------------------------------------------------------------------------
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;



int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Specify a subtask";
    exit(0);
  }

  string subtask(argv[1]);

  int maxN, maxP, maxS, minS, minN;
  int minP = 0;
  if (subtask == "1") {
    maxP = 100;
    minS = 1;
    maxS = 2;
    minN = 1;
    maxN = 10;
  } else if (subtask == "2") {
    maxP = 5;
    minS = 3;
    maxS = 100;
    minN = 10;
    maxN = 500;
  } else if (subtask == "3") {
    maxP = 1000;
    maxS = 1000;
    minS = 101;
    minN = 501;
    maxN = 5000;
  } else {
    maxP = 1000;
    maxS = 1000;
    minS = 101;
    maxN = 5000;
    minN = 501;
  }

  int N, S, P;
  cin >> N >> S >> P;

  if (N < minN || N > maxN) {
    cout << "N fuera de rrango " << N << endl;
    exit(0);
  }
  if (P < minP || P > maxP) {
    cout << "P fuera de rrango " << P << endl;
    exit(0);
  }
  if (S < minS || S > maxS) {
    cout << "S fuera de rrango " << S << endl;
    exit(0);
  }

  // cout << N << " " << S << " " << P << endl;

  vector<int> laminas(N+1);

  for (int i = 1; i <= N; ++i) {
    cin >> laminas[i];
    if (laminas[i] <= 0) {
      cout << "Lámina negativa\n";
      exit(0);
    }
    if (laminas[i] > 5000) {
      cout << "Lámina muy cara\n";
      exit(0);
    }
    if (subtask == "3" && i > 1 && laminas[i-1] != laminas[i]){
      cout << "Lámina suelta con distinto precio\n";
      exit(0);
    }
  }
  char c = cin.get();
  if (c != '\n') {
    cout << "Línea no contiene N enteros\n";
    exit(0);
  }

  for (int i = 0; i < S-1; ++i) {
    for (int j = 0; j < 5; ++j){
      int l;
      cin >> l;
      if (subtask == "2") {
        if (not laminas[l]) {
          cout << "Lámina repetida " << l << ", sobre: " << i+1 << "\n";
          exit(0);
        }
      }
      laminas[l] = 0;
    }
  }

  bool b = false;
  for (int j = 0; j < 5; ++j){
    int l;
    cin >> l;
    if (laminas[l])
      b = true;
    if (subtask == "2") {
      if (not laminas[l]) {
        cout << "Lámina repetida " << l << "\n";
        exit(0);
      }
    }
    laminas[l] = 0;
  }

  if (not b) {
    cout << "Último sobre tiene solo láminas repetidas\n";
    exit(0);
  }

  for (int i = 1; i <= N; ++i) {
    if (laminas[i]) {
      cout << "No se completaron todas las láminas\n";
      exit(0);
    }
  }


  return 0;
}

