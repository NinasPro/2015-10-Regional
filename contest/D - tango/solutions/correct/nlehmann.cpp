/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * -----------------------------------------------------------------------------
 */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> hombres(N);
  for (int i = 0; i < N; ++i) {
    cin >> hombres[i];
  }

  vector<int> mujeres(N);
  for (int i = 0; i < N; ++i) {
    cin >> mujeres[i];
  }

  sort(hombres.rbegin(), hombres.rend());
  sort(mujeres.rbegin(), mujeres.rend());

  int j = 0;
  for (int i = 0; i < N; ++i) {
    while (j < N && mujeres[j] > hombres[i])
      ++j;

    if (j < N)
      cout << hombres[i] << " " << mujeres[j] << endl;
    ++j;
  }
}
