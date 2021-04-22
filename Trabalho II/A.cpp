#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Função que simplica ao máximo uma fração
void simplificaFracao(int &numerador, int &denominador) {
    int maior = max(numerador,denominador);

    for(int i = maior; i >= 2; i--) {
        if((numerador % i == 0) && (denominador % i == 0)) {
            numerador = numerador / i;
            denominador = denominador / i;
        }
    }
}

// Função dfs que vai "andando" no grafo ao mesmo tempo que calcula as correspondêcias dos itens vizinhos
void dfs(map<string,vector<pair<string,pair<int,int>>>> &listaAdjacencia, map<string,bool> &visitado, const string &item1, const string &item2, int numerador, int denominador, int &numeradorFinal, int &denominadorFinal, bool &encontrei) {
    visitado[item1] = true;

    // Se conseguirmos chegar no item2, armazenamos a correspondência final
    if(item1 == item2) {
        encontrei = true;
        numeradorFinal = numerador;
        denominadorFinal = denominador;
        return;
    }

    vector<pair<string,pair<int,int>>> vizinhos = listaAdjacencia[item1];

    for(int i = 0; i < vizinhos.size(); i++) {
        if(!visitado[vizinhos[i].first] && !encontrei) {
            // Salvando do numerador e denominador antes de chamarmos recursivamente
            int numeradorAntigo = numerador;
            int denominadorAntigo = denominador;

            // Achando a correspondência dos itens vizinhos
            numerador = numerador * vizinhos[i].second.second;
            denominador = denominador * vizinhos[i].second.first;

            simplificaFracao(numerador,denominador);

            dfs(listaAdjacencia, visitado, vizinhos[i].first, item2, numerador, denominador, numeradorFinal, denominadorFinal, encontrei);
            
            // Voltando para o numerador e denominador de antes de fazer a recursão
            numerador = numeradorAntigo;
            denominador = denominadorAntigo;
        }
    }

}

int main() {
    char opcao, igual;
    int valor1, valor2, numeradorFinal, denominadorFinal;
    map<string,vector<pair<string,pair<int,int>>>> listaAdjacencia; 
    map<string,bool> visitado;
    string item1, item2;
    bool encontrei = false;
    
    while(cin >> opcao) {
        if(opcao == '!') {
            cin >> valor1 >> item1 >> igual >> valor2 >> item2;
            listaAdjacencia[item1].push_back(make_pair(item2,make_pair(valor1,valor2)));
            listaAdjacencia[item2].push_back(make_pair(item1,make_pair(valor2,valor1)));
            visitado[item1] = false;
            visitado[item2] = false;

        } else if(opcao == '?') {
            cin >> item1 >> igual >> item2;

            dfs(listaAdjacencia, visitado, item1, item2, 1, 1, numeradorFinal, denominadorFinal, encontrei);
        
            if(encontrei) {
                cout << denominadorFinal << " " << item1 << " = " << numeradorFinal << " " << item2 << "\n";
            } else {
                cout << "? " << item1 << " = ? " << item2 << "\n";
            }

            encontrei = false;

            for(map<string,bool>::iterator it = visitado.begin(); it != visitado.end(); it++) (*it).second = false;
        } else break;
    }

    return 0;
}