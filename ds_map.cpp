#include <iostream> // utilizado para entradas e saidas
#include <stdlib.h> // utilizado para usar o rand
#include <cmath> // utilizado para o numero de euler e as funcoes abs e pow
#include <cfloat> // utilizado no DBL_MAX
#include <climits> // utilizado no INT_MAX
#include <vector> 
#include <algorithm>    // std::copy
#include <chrono> // utilizado para contar o tempo de execucao

using namespace std;
using namespace std::chrono;


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
    for (int i = 2; i<=pow(frame,2);i++) {
        double a1 = (fat(frame)/(fat(empty)*fat(success)*fat(colisao)));
        // cout << a1 << endl;
        double a2 = p1(frame, empty, i);
        double a3 = p2(frame, empty, success, i);
        double a4 = p3(success, colisao, i);
        // cout << "p1: " << a2 << " p2: " << a3 << " p3: " << a4 << endl;
        double p = a1*a2*a3*a4;

        // cout << p << "\t==>\t" << i << endl;


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
    for(int i = 2;i<=10000;i=i*2) {
        double auxU = (n/((double)i))*pow(1-(1.0/i),n - 1);
        //cout << auxU << " " << U << endl;
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


vector<vector<double> > dsmap(int inislots, // quantidade inicial de slots
    int initags, // quantidade inicial de tags
    int incrementotags, // tamanho do incremento na quantidade de tags
    int maximotags, // numero maximo de tags
    int quantsimulacoes // quantidade de simulacoes para cada quantidade de tags
) {
    int epoca = 1; // incremento de tags (100,200, ..., 1000)

	int quanttags = initags; // quantidade atual de tags
	
	int Nback = 0;
	int K = -1;

    vector<vector<double> > retorno;

    high_resolution_clock::time_point t1, t2;
	duration<double, std::milli> time_span;
	
	while (quanttags <= maximotags) {
		int execucao = quantsimulacoes;
        int somaslots = inislots;
        int slotscolisao = 0;
        int slotsvazio = 0;
        int slotssucesso = 0;
        
		t1 = high_resolution_clock::now();
        while (execucao--) {
        	int Fnxt = inislots; // quantidade de slots na interacao atual

	 		while (quanttags > 0) {
				int slots[Fnxt],
		    	sucesso = 0, // quantidade de slots que leram as etiquetas com sucesso
		    	colisao = 0, // quantidade de slots que tiveram colisao
		    	vazio = 0, // quantidade de slots vazios
		   		S = 0; // Sucesso total

				for (int i = 0; i< Fnxt;i++) {
					slots[i] = 0; // coloca 0 em todos os slots
				}

				for (int i = 0; i < quanttags; i++) {
					slots[rand() % Fnxt] += 1; // gera um numero aleatorio entre 0 e a quantidade de slots e no slot do numero que foi gerado acrescenta um nele
				}

				int Fsub = fsub(Fnxt);
				if (K == 1)
					Fsub = Fnxt;
				int Ns, Nc;
				
				Ns=0, Nc=0;
				for (int i = 0; i< Fsub;i++) {
					 if (slots[i] == 0) {
                        vazio++; // pega a quantidade de slots vazios
                    } else if (slots[i] == 1) {
						Ns++;
					} else if (slots[i] > 1) {
						Nc++;
					}
				}            
					
				
				//cout << "Ns: " << Ns << ", Nc: " << Nc << ", Fsub: " << Fsub << ", ";
				int n = valor(Fsub,Ns,Nc);
				K = ceil(Fnxt/Fsub);
				int Nest = n * K;
				int nslots = table1(Nest);
				//cout << Nest << "  " << nslots << "  " << Fnxt << endl;
				// cout << "n: " << n << ", K: " << K << ", Nest: " << Nest << ", nslots: " << nslots << ", Fnxt: " << Fnxt << ", ";
				if (Fnxt <= nslots && Fnxt >= nslots/2) {
					Nest = S = 0;
					//cout << endl;
					for (int i = 0;i<K;i++) {
						Ns = Nc = 0;
						int lenframe = Fsub;
						// cout << "len: " << lenframe << " ";
						for (int j = i*Fsub; j<lenframe;j++) {
							 if (slots[j] == 0) {
								vazio++; // pega a quantidade de slots vazios
							} else if (slots[j] == 1) {
								Ns++;
								S++;
							} else if (slots[j] > 1) {
								Nc++;
							}
						}
						// cout << "Nc: " << Nc << ", Ns: " << Ns << ", vv: " << valor(lenframe - i*Fsub, Ns, Nc) << endl;
						Nest += valor(lenframe, Ns, Nc);
					}
					Nback = Nest - S;
					quanttags -= S;
					Fnxt = table1(Nback);
					K = 1;
					//cout << "Nest: " << Nest << ", S: " << S << ", Nback: " << Nback << endl << endl;
				} else {
					Nback = Nest - Ns;
					quanttags -= Ns*K;
					Fnxt = table1(Nback);
				}
				//cout << "Fnxt: " << Fnxt << ", Tags: " << quanttags << endl;
				if (Fnxt == -1) break;

				
                slotscolisao += Nc;
                slotsvazio += vazio;
                somaslots += Fnxt; // utilizado para saber a quantidade de slots sao utilizados em media para reconhecer as tags
                slotssucesso += Ns;
			}

	  	    quanttags=initags*epoca; // reinicia a variavel quanttags com a quantidade de tags da epoca que ela esta (10)
     	}
		cout << " int: " << epoca << endl; 
		t2 = high_resolution_clock::now();
        time_span = t2 - t1;
        vector<double> medias = {(double)somaslots/quantsimulacoes,(double)slotscolisao/quantsimulacoes,(double)slotsvazio/quantsimulacoes,(double)time_span.count(), (double)slotssucesso/somaslots};
        retorno.push_back(medias);
        epoca++;
        quanttags+=initags;
	}

	 return retorno;
}




int main() {
    vector<vector<double> > ds = dsmap(64, 100, 100, 1000, 500);

    for (int i = 0;i< ds.size();i++) {
        cout << "Interação " << i + 1 << endl;
        cout << "Total slots: " << ds[i][0] << endl;
        cout << "Slots com colisão: " << ds[i][1] << endl;
        cout << "Slots vazios: " << ds[i][2] << endl << endl;
        cout << "Tempo: " << ds[i][3] << endl;
        cout << "Fluxo: " << ds[i][4] << endl << endl;
    }
}