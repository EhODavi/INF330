#include <iostream>
#include <string>
#include <set>

using namespace std;

void calculaComponentes() {
    int qtdArestas = 0, qtdVertices, qtdComponentes, qtdVerticesIsolados = 0;
    string linha;
    set<char> arestas;
    set<char> vertices;

    while(true) {
        cin >> linha;

        if(linha[0] == '*') break;

        arestas.insert(linha.begin(),linha.end());
        qtdArestas++;
    }

    arestas.erase('(');
    arestas.erase(')');
    arestas.erase(',');

    cin >> linha;
        
    vertices.insert(linha.begin(),linha.end());
    vertices.erase(',');
        
    qtdVertices = vertices.size();
    qtdComponentes = qtdVertices - qtdArestas;
        
    for(set<char>::iterator it = vertices.begin(); it != vertices.end(); it++) {
        if(arestas.find(*it) == arestas.end()) qtdVerticesIsolados++;
    }
        
    qtdComponentes = qtdComponentes - qtdVerticesIsolados;

    cout << "There are " << qtdComponentes << " tree(s) and " << qtdVerticesIsolados << " acorn(s).\n";
}

int main() {
    int N;

    cin >> N;

    for(int i = 0; i < N; i++) {
        calculaComponentes();
    }

    return 0;
}