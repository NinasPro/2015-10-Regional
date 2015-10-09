#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n, s, p, ccr, csr, costo; //costo cartas restantes y costo sobres restantes
vector <int> precio, sobre, obtenidas;

int main(){
    cin >> n >> s >> p;
    ccr = 0, csr = s*p;
    precio.assign(n+1, 0);
    sobre.assign(5*s, 0);
    obtenidas.assign(n+1, 0);
    int mini = INT_MAX;
    costo = 0;
    for (int i = 1; i<=n; i++){
        cin >> precio[i];
        ccr += precio[i];
    }
    for (int i = 0; i<5*s; i++){
        cin >> sobre[i];
    }
    for (int i = 0; i<5*s; i+=5){
        mini = min(mini,costo+min(ccr,csr));
        csr -=p;
        costo+=p;
        for (int j = 0; j<5; j++){
            if (obtenidas[sobre[i+j]]==0){
                obtenidas[sobre[i+j]]=1;
                ccr-=precio[sobre[i+j]];
            }
        }
    }
    cout << mini << endl;
    return 0;
}
