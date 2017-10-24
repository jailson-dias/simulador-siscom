#include <iostream>
#include <fstream>
#include<string>
#include "eon_lee.h"
#include "lower_bound.h"

using namespace std;
using std::string;
using std::to_string;

int main() {

    int protocolo = 1,
        initags = 1,
        incrementotags = 1,
        maxtags = 1,
        repeticoes = 1,
        inislots = 1;
    string protocolos[3] = {"Lower Bound", "Eom-Lee","Lower Bound e Eom-Lee"};
    do {
        if (protocolo < 1 || protocolo > 3) {
            cout << "Digite um número válido.(1,2 ou 3)" << endl << endl;
        }
        cout << "Digite o protocolo que vai ser utilizado" << endl;
        cout << "(1) " + protocolos[0] << endl;
        cout << "(2) " + protocolos[1] << endl;
        cout << "(3) " + protocolos[2] << endl;
    } while (cin >> protocolo, (protocolo < 1 || protocolo > 3));

    cout << "O protocolo selecionado foi " + protocolos[protocolo - 1] << "." << endl << endl;

    do {
        if (initags < 0) {
            cout << "Digite uma quantidade válida de etiquetas.(maior ou igual a 0)" << endl;
        }
        cout << "Digite a quantidade inicial de etiquetas" << endl;
    } while (cin >> initags, initags < 0);
    cout << "A quantidade inicial de etiquetas é " << initags << "." << endl << endl;

    do {
        if (incrementotags < 1) {
            cout << "Digite uma quantidade válida para o incremento de etiquetas.(maior que 0)" << endl; 
        }
        cout << "Digite a quantidade de etiquetas que vai ser incrementada a cada interação" << endl;
    } while (cin >> incrementotags, incrementotags < 1);

    cout << "A quantidade de etiquetas que vai ser incrementado a cada interação é " << incrementotags << "." << endl << endl;

    do {
        if (maxtags < initags) {
            cout << "Digite uma quantidade maior ou igual a quantidade inicial de etiquetas. ( maior ou igual a " << initags << ")" << endl;
        }
        cout << "Digite a quantidade máxima de etiquetas que vai ser utilizada no teste" << endl;
    } while (cin >> maxtags, maxtags < initags);

    cout << "A quantidade máxima de etiquetas que vai ser utilizado no teste é " << maxtags << "." << endl << endl;

    do {
        if (repeticoes < 1) {
            cout << "Digite uma quantidade válida para a quantiade de repetições do teste em cada quantidade de etiquetas. (maior ou igual a 1)" << endl; 
        }
        cout << "Digite a quantidade de repetições do teste em cada quantidade de etiquetas" << endl;
    } while (cin >> repeticoes, repeticoes < 1);

    cout << "A quantidade de repetições do teste em cada quantidade de etiquetas é " << repeticoes << "." << endl << endl;

    do {
        if (inislots < 1) {
            cout << "Digite um número válida para o tamanho do quadro inicial.(maior ou igual a 1)" << endl; 
        }
        cout << "Digite o tamanho do quadro inicial" << endl;
    } while (cin >> inislots, inislots < 1);

    cout << "O tamanho do quadro inicial é " << inislots << "." << endl << endl;

    cout << "Resumo:" << endl;
    cout << "Protocolo selecionado: " + protocolos[protocolo - 1] << "," << endl;
    cout << "Quantidade inicial de etiquetas: " << initags << "," << endl;
    cout << "Quantidade de etiquetas que vai ser incrementado a cada interação: " << incrementotags << "," << endl;
    cout << "Quantidade máxima de etiquetas que vai ser utilizado no teste: " << maxtags << "," << endl;
    cout << "Quantidade de repetições do teste em cada quantidade de etiquetas: " << repeticoes << "," << endl;
    cout << "Tamanho do quadro inicial: " << inislots << "." << endl << endl << endl;

/*
initags,
incrementotags,
maxtags,
repeticoes,
inislots;
*/
    int num = 2;
    ofstream slots, slotsvazios, slotscolisao;
    slots.open ("slots.dat");
    slotsvazios.open ("slotsvazios.dat");
    slotscolisao.open ("slotscolisao.dat");

    if(protocolo == 1) {
        vector<vector<double> > lb = lower_bound(
            inislots,
            initags,
            incrementotags,
            maxtags,
            repeticoes
        );

        int tags = initags;
        slots << "Etiquetas Lower-Bound\n";
        slotsvazios << "Etiquetas Lower-Bound\n";
        slotscolisao << "Etiquetas Lower-Bound\n";
        for(int i = 0; i < lb.size(); i++) {
            slots << tags << " " << lb[i][0] << "\n";
            slotscolisao << tags << " " << lb[i][1] << "\n";
            slotsvazios << tags << " " << lb[i][2] << "\n";
            tags += incrementotags;
        }
    } else if(protocolo == 2) {
        vector<vector<double> > el = eonlee(
            inislots,
            initags,
            incrementotags,
            maxtags,
            repeticoes
        );

        int tags = initags;
        slots << "Etiquetas Eon-Lee\n";
        slotsvazios << "Etiquetas Eon-Lee\n";
        slotscolisao << "Etiquetas Eon-Lee\n";
        for(int i = 0; i < el.size(); i++) {
            slots << tags << " " << el[i][0] << "\n";
            slotscolisao << tags << " " << el[i][1] << "\n";
            slotsvazios << tags << " " << el[i][2] << "\n";
            tags += incrementotags;
        }
    } else if (protocolo == 3) {
        num = 3;
        vector<vector<double> > lb = lower_bound(
            inislots,
            initags,
            incrementotags,
            maxtags,
            repeticoes
        );

        vector<vector<double> > el = eonlee(
            inislots,
            initags,
            incrementotags,
            maxtags,
            repeticoes
        );

        int tags = initags;
        slots << "Etiquetas Lower-Bound Eon-Lee\n";
        slotsvazios << "Etiquetas Lower-Bound Eon-Lee\n";
        slotscolisao << "Etiquetas Lower-Bound Eon-Lee\n";
        for(int i = 0; i < el.size(); i++) {
            slots << tags << " " << lb[i][0] << " " << el[i][0] << "\n";
            slotscolisao << tags << " " << lb[i][1] << " " << el[i][1] << "\n";
            slotsvazios << tags << " " << lb[i][2] << " " << el[i][2] << "\n";
            tags += incrementotags;
        }
    }

    slots.close();
    slotsvazios.close();
    slotscolisao.close();

    // gerar graficos
    string comando1 = "gnuplot -c run-gnuplot.gp slots.png slots.dat " + to_string(num);
    string comando2 = "gnuplot -c run-gnuplot.gp slotsvazios.png slotsvazios.dat " + to_string(num);
    string comando3 = "gnuplot -c run-gnuplot.gp slotscolisao.png slotscolisao.dat " + to_string(num);
    
    system(comando1.c_str());
    system(comando2.c_str());
    system(comando3.c_str());

    return 0;
}