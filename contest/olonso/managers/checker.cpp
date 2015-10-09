/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * ----------------------------------------------------------------------------
 */
#include <fstream>
#include <iostream>
#include <cstdio>
using namespace std;

ifstream input;
ifstream res;
ifstream output;

int main(int, char *argv[]) {
  input.open(argv[1], ios::in);
  res.open(argv[2], ios::in);
  output.open(argv[3], ios::in);

  string line;
  int status;
  output >> status;
  switch (status){
  case 0: case 1: case 2: case 4:
    std::getline(output, line);
    std::getline(output, line);
    cerr << line << "\n";
    cout << 0.0;
    return 0;
  case 3:
    cout << 1.0;
  }
}
