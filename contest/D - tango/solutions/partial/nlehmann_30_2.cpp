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
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> altura(500, 0);

  for (int i = 0; i < N; ++i) {
    int h;
    cin >> h;
    altura[h]++;
  }

  for (int h = 0; h < 500; ++h) {
    if(altura[h])
      cout << h << " " << h << endl;
  }

  return 0;
}

