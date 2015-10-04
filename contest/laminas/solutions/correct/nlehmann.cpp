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
  int N, S, P;
  cin >> N >> S >> P;
  vector<int> price(N + 1);

  int single = 0;
  for (int i = 1; i <= N; ++i) {
    cin >> price[i];
    single += price[i];
  }

  int min = single;
  for (int i = 0; i < S; ++i) {
    for (int j = 0; j < 5; ++j) {
      int l;
      cin >> l;
      single -= price[l];
      price[l] = 0;
    }
    min = std::min(min, single + (i+1)*P);
  }

  cout << min << endl;
}
