#include <iostream> // utilizado para entradas e saidas
#include <stdlib.h> // utilizado para usar o rand
#include <vector>
#include <chrono> // utilizado para contar o tempo de execucao

using namespace std;
using namespace std::chrono;

vector<vector<double> > lower_bound(int inislots, // quantidade inicial de slots
    int initags, // quantidade inicial de tags
    int incrementotags, // tamanho do incremento na quantidade de tags
    int maximotags, // numero maximo de tags
    int quantsimulacoes // quantidade de simulacoes para cada quantidade de tags
) {
    int epoca = 1; // incremento de tags (100,200, ..., 1000)

    int quanttags = initags; // quantidade atual de tags

    vector<vector<double> > retorno;

    high_resolution_clock::time_point t1, t2;
    duration<double, std::milli> time_span;

    while (quanttags <= maximotags) {
        int execucao = quantsimulacoes;
        int somaslots = inislots;
        int slotscolisao = 0;
        int slotsvazio = 0;

        t1 = high_resolution_clock::now();
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
                quantslots = colisao<<1; // quantidade de slots no proximo quadro (colisao * 2)
                quanttags -= sucesso;
                slotscolisao += colisao;
                slotsvazio += vazio;
                somaslots += quantslots; // utilizado para saber a quantidade de slots sao utilizados em media para reconhecer as tags
            }
            quanttags=initags*epoca; // reinicia a variavel quanttags com a quantidade de tags da epoca que ela esta (10)
        }
        t2 = high_resolution_clock::now();
        time_span = t2 - t1;
        vector<double> medias = {(double)somaslots/quantsimulacoes,(double)slotscolisao/quantsimulacoes,(double)slotsvazio/quantsimulacoes,(double)time_span.count()};
        retorno.push_back(medias);
        epoca++;
        quanttags+=initags;
    }

    return retorno;
}

int main() {
    vector<vector<double> > retorno = lower_bound(64, 100, 100, 1000, 2000);

    for (int i = 0;i< retorno.size();i++) {
        cout << "Interação " << i + 1 << endl;
        cout << "Total slots: " << retorno[i][0] << endl;
        cout << "Slots com colisão: " << retorno[i][1] << endl;
        cout << "Slots vazios: " << retorno[i][2] << endl;
        cout << "Tempo: " << retorno[i][3] << endl << endl;
    }

    return 0;
}