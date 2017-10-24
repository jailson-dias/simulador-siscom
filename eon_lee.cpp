#include <iostream> // utilizado para entradas e saidas
#include <stdlib.h> // utilizado para usar o rand
#include <cmath> // utilizado para o numero de euler e as funcoes abs e pow
#include <cfloat> // utilizado no DBL_MAX
#include <climits> // utilizado no INT_MAX
#include <vector> 
#include <algorithm>    // std::copy

using namespace std;

double calcbk(int l, double ykm1, int sc, int ss) {
    /** funcao para calcular o beta da interacao k no algoritmo de eon-lee
        
        paramentros
        l = quantidade de slots
        ykm1 = gama da interacao k - 1
        sc =  quantidade de slots em colisao
        ss =  quantidade de slots bem sucedidos*/     
        
    // cout << "l: " << l << ", ykm1: " << ykm1 << ", sc: " << sc << ", ss: " << ss << endl;
    return (double)l/(ykm1*sc + ss);
}

double calcyk(double bk) {
    /** funcao utilizada para calcular o gama da interacao k no algoritmo de eon-lee

        paramentros
        bk = beta da interacao k - 1*/
    return (1 - pow(M_E, -1/bk))/(bk*(1-(1+1/bk)*pow(M_E, -1/bk)));
}

vector<vector<double> > eonlee(int inislots, // quantidade inicial de slots
    int initags, // quantidade inicial de tags
    int incrementotags, // tamanho do incremento na quantidade de tags
    int maximotags, // numero maximo de tags
    int quantsimulacoes // quantidade de simulacoes para cada quantidade de tags
) {
    double inib1 = DBL_MAX, // valor inicial de beta
           iniy1 = 2, // valor inicial de gama
           limiar = 0.001; // limiar de aproximacao para o estimador de eon-lee parar
    
    int epoca = 1; // incremento de tags (100,200, ..., 1000)
   
    int quanttags = initags; // quantidade atual de tags    
    vector<vector<double> > retorno;
    while (quanttags <= maximotags) {
        int execucao = quantsimulacoes;
        int somaslots = inislots;
        int slotscolisao = 0;
        int slotsvazio = 0;
        while (execucao--) {
            int quantslots = inislots; // quantidade de slots na interacao atual
            while (quanttags > 0) {
                int slots[quantslots],
                    sucesso = 0, // quantidade de slots que leram as etiquetas com sucesso
                    colisao = 0, // quantidade de slots que tiveram colisao
                    vazio = 0; // quantidade de slots vazios

                for (int i = 0; i< quantslots;i++) {
                    slots[i] = 0; // coloca 0 em todos os slots
                }
                for (int i = 0; i < quanttags; i++) {
                    slots[rand() % quantslots] += 1; // gera um numero aleatorio entre 0 e a quantidade de slots e no slot do numero que foi gerado acrescenta um nele
                }

                for (int i = 0; i< quantslots;i++) {
                    if (slots[i] == 0) {
                        vazio++; // pega a quantidade de slots vazios
                    } else if (slots[i] == 1) {
                        sucesso++; // pega a quantidade de slots que conseguiram reconhecer tags
                    } else {
                        colisao++; // pega a quantidade de slots que teve colisao
                    }
                }

                double ykm1 = DBL_MAX, // valor do gama na interacao anterior
                    yk = iniy1, // valor atual de gama
                    bkm1 = inib1, // valor do beta na interacao anterior
                    bk = DBL_MAX; // valor atual de beta
                if (colisao > 0) {
                    while (limiar < abs(ykm1 - yk)) {
                        ykm1 = yk;
                        bk = calcbk(quantslots, ykm1, colisao, sucesso);
                        yk = calcyk(bk);
                    }
                    quantslots = ceil(yk * colisao); // quantidade de slots no proximo quadro (gama atual * slots com colisao)
                }
                quanttags -= sucesso;
                slotscolisao += colisao;
                slotsvazio += vazio;
                somaslots += quantslots; // utilizado para saber a quantidade de slots sao utilizados em media para reconhecer as tags
            }
            quanttags=initags*epoca; // reinicia a variavel quanttags com a quantidade de tags da epoca que ela esta (10)
        }
        vector<double> medias = {(double)somaslots/quantsimulacoes,(double)slotscolisao/quantsimulacoes,(double)slotsvazio/quantsimulacoes};
        retorno.push_back(medias);
        epoca++;
        quanttags+=initags;
    }
    
    return retorno;
}

int main() {
    vector<vector<double> > eon = eonlee(64, 100, 100, 1000, 500);

    for (int i = 0;i< eon.size();i++) {
        cout << "Interação " << i + 1 << endl;
        cout << "Total slots: " << eon[i][0] << endl;
        cout << "Slots com colisão: " << eon[i][1] << endl;
        cout << "Slots vazios: " << eon[i][2] << endl << endl;
    }
}