#include <iostream> // utilizado para entradas e saidas
#include <stdlib.h> // utilizado para usar o rand

using namespace std;

int main() {
    int inislots = 64, // quantidade inicial de slots
        initags = 100, // quantidade inicial de tags
        incrementotags = 100, // tamanho do incremento na quantidade de tags
        maximotags = 1000, // numero maximo de tags
        quantsimulacoes = 2000, // quantidade de simulacoes para cada quantidade de tags
        epoca = 1; // incremento de tags (100,200, ..., 1000)

    int quanttags = initags; // quantidade atual de tags

    while (quanttags <= maximotags) {
        cout << "###################   " << quanttags << "  #########################" << endl;
        int execucao = quantsimulacoes;
        int somaslots = inislots;
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

                somaslots += quantslots; // utilizado para saber a quantidade de slots sao utilizados em media para reconhecer as tags
            }
            quanttags=initags*epoca; // reinicia a variavel quanttags com a quantidade de tags da epoca que ela esta (10)
        }
        cout << (double)somaslots/quantsimulacoes << endl; // media de slots utilizados para reconhecer as tags
        cout << "#########################################################################" << endl << endl;
        epoca++;
        quanttags+=initags;
    }
    return 0;
}