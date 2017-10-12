#include <iostream>

using namespace std;

int main() {
    int protocolo = 1,
        initags = 1,
        incrementotags,
        maxtags,
        repeticoes,
        inislots;
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


    switch(protocolo) {
        case 1:
            
            break;
        case 2:
        
            break;
        case 3:
    
            break;
    }

    return 0;
}