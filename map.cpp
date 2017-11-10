#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;
double p1(double frame, double empty, double tags) {
    return pow((1-((double)empty)/frame),tags);
}

double fat(double f) {
    double r = 1;
    while (f>0) {
        r *= f--;
    }
    return r;
}

double comb(double n, double s) {
    return fat(n)/(fat(s)*fat(n-s));
}

double p2(double frame, double empty, double success, double tags) {
    // cout << "bi " << comb(tags, success) << endl;
    double c1 = comb(tags, success);
    double c2 = pow(frame - empty - success,tags - success);
    double c3 = pow(frame-empty, tags);
    double c4 = fat(success);
    // cout << frame << "\tem: " << empty << "\tsuc: " << success << "\ttags: " << tags << endl;
    // cout << c1 << "\t" << c2 << "\t" << c3 << "\t" << c4 << endl;
    // cout << "p2" << endl;
    return c1*(c2/c3)*c4;
}

double p3(double success, double colisao, double tags) {
    double res = 0;
    for (int k = 0; k <= colisao;k++) {
        for (int v = 0;v<=colisao - k;v++) {
            res += pow(-1, k + v)*
            comb(colisao, k)*
            comb(colisao-k,v)*
            (fat(tags-success)/fat(tags-success-k))*
            (pow(colisao-k-v,tags-success-k)/pow(colisao,tags-success));
        }
    }
    // cout << res << endl;
    // cout << "p3" << endl;
    return res;
}

vector<vector<int> > table2(double frame) {
    vector<vector<int> > table;
    cout << " \t\t";
    for (int j = 0; j<frame;j++) {
        cout << j <<'\t';
    }
    cout << endl << endl;
    for (int colisao = 1;colisao<=frame;colisao++) {
        cout << colisao << "\t\t";
        vector<int> line;
        for (int success = 0;success<=frame - colisao;success++) {
            double maxi = 0;
            double n = -1;
            double s = 0, c = 0;
            double empty = frame - colisao - success;
            for (int i = 2; i<100;i++) {
                double a1 = (fat(frame)/(fat(empty)*fat(success)*fat(colisao)));
                double a2 = p1(frame, empty, i);
                double a3 = p2(frame, empty, success, i);
                double a4 = p3(success, colisao, i);
                double p = a1*a2*a3*a4;

                if (isfinite(p) && p < 1 && p>maxi) {
                    maxi = p;
                    s = success;
                    c = colisao;
                    n = i;
                }
                // cout << p << endl;
            }
            // cout << s << " " << c << ": " << n << "\t" << maxi << endl;
            cout << n << "\t";
            line.push_back(n);
        }
        cout << endl;
        table.push_back(line);
    }
    return table;
}


double valor(double frame, double success, double colisao) {
    double maxi = 0;
    double n = -1;
    double s = 0, c = 0;
    double empty = frame - colisao - success;
    // cout << "empty: " << empty << " colisao: " << colisao << " success: " << success << endl;
    for (int i = 2; i<100;i++) {
        double a1 = (fat(frame)/(fat(empty)*fat(success)*fat(colisao)));
        cout << a1 << endl;
        double a2 = p1(frame, empty, i);
        double a3 = p2(frame, empty, success, i);
        double a4 = p3(success, colisao, i);
        cout << "p1: " << a2 << " p2: " << a3 << " p3: " << a4 << endl;
        double p = a1*a2*a3*a4;

        cout << p << "\t==>\t" << i << endl;


        if (isfinite(p) && p < 1 && p>maxi) {
            maxi = p;
            s = success;
            c = colisao;
            n = i;
        }
        // cout << p << endl;
    }
    return n;
}


int table1(double n) {
    double U = 0;
    int f = -1;
    for(int i = 2;i<=2000;i=i*2) {
        double auxU = (n/((double)i))*pow(1-(1.0/i),n - 1);
        // cout << auxU << " " << U << endl;
        if(auxU - U > 0.00000001) {
            U = auxU;
            f = i;
        }
    }
    return f;
}

int fsub(int n) {
    if (n>=1024) {
        return 64;
    }

    if (n>=512) {
        return 32;
    }

    if (n>=128) {
        return 16;
    }

    if (n>=32) {
        return 8;
    }

    return 4;
}

int main(int argc, char **argv){
    // table(10);
    // while(1) {
    //     int x;
    //     cin >> x; 
    //     cout << table1(x) << endl;
    // }
    vector<vector<int> > t = table2(50);
    // for(int i = 0; i < t.size();i++) {
    //     for (int j = 0; j < t[i].size(); j++) {
    //         cout << t[i][j] << "\t";
    //     }
    //     cout << endl;
    // }
    int quanttags = 100;
    int Nback = 64;
    int K = -1;
    while (quanttags > 0) {
        int slots[Nback],
            sucesso = 0, // quantidade de slots que leram as etiquetas com sucesso
            colisao = 0, // quantidade de slots que tiveram colisao
            vazio = 0, // quantidade de slots vazios
            S = 0; // Sucesso total

        for (int i = 0; i< Nback;i++) {
            slots[i] = 0; // coloca 0 em todos os slots
        }

        for (int i = 0; i < quanttags; i++) {
            slots[rand() % Nback] += 1; // gera um numero aleatorio entre 0 e a quantidade de slots e no slot do numero que foi gerado acrescenta um nele
        }
        int Fsub = fsub(Nback);
        if (K == 1)
            Fsub = Nback;
        for (int i = 0; i< Fsub;i++) {
            if (slots[i] == 0) {
                vazio++; // pega a quantidade de slots vazios
            } else if (slots[i] == 1) {
                sucesso++; // pega a quantidade de slots que conseguiram reconhecer tags
                S++;
            } else {
                colisao++; // pega a quantidade de slots que teve colisao
            }
        }

        int n = t[colisao][sucesso];
        K = ceil(Nback/Fsub);
        int Nest = n * K;
        int nslots = table1(Nest);
        if (Nback <= nslots && Nback >= nslots) {
            Nest = 0;
            for (int i = 0;i<K;i++) {
                vazio = sucesso = colisao = 0;
                for (int j = i*Fsub; j< min((i+1)*Fsub, Nback);j++) {
                    if (slots[j] == 0) {
                        vazio++; // pega a quantidade de slots vazios
                    } else if (slots[j] == 1) {
                        sucesso++; // pega a quantidade de slots que conseguiram reconhecer tags
                        S++;
                    } else {
                        colisao++; // pega a quantidade de slots que teve colisao
                    }
                }
                Nest += t[colisao][sucesso];
            }
            Nback = Nest - S;
            K = 1;
        } else {
            Nback = Nest - sucesso;
            K = 0;
        }
        cout << "back: " << Nback << endl;
        quanttags -= S;
    }
	return 0;
}