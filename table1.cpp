#include <cmath>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

class T {
public:
    int f, nmin, nmax;
    T (int f, int min, int max): f(f),nmin(min),nmax(max) {}
};

vector<T> tabela;

int table() {
    int f = 1, faux=0, min=1;
    for(int i = 1; i < 46340; i++) {
        faux = pow(2,lround(log2(i)));

        if(f != faux) {
            // cout << faux << " " << i << " " << log2(i) << " " << lround(log2(i)) <<  endl;
            tabela.push_back(T(f, min, i-1));
            min = i;
            f = faux;
            if(tabela.size() == 15) {
                tabela.push_back(T(faux, i, 46340));
                break;
            }
        }
    }
    
    for(int i=0; i < tabela.size(); i++) {
        cout << tabela[i].f << " " << tabela[i].nmin << " " << tabela[i].nmax << endl;
    }
}

int main() {
    table();
}