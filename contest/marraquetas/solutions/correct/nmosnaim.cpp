#include <iostream>
using namespace std;

int main(){
    int n, r;
    cin >> n;
    r = n/2;
    if (n%2!=0) r++;
    cout << r << endl;
    return 0;
}
