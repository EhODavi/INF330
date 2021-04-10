#include <iostream>
#include <string>
#include <set>

using namespace std;

// Função que calcula quantos componentes conexos que a floresta possui (separando-os em árvores e pontos isolados)
void calculaComponentes() {
    // Criando qtdArestas (representa a quantidade de arestas do grafo)
    // qtdVertices (representa a quantidade de vértices do grafo)
    // qtdComponentes (representa a quantidade de árvores do grafo)
    // qtdVerticesIsolados (representa a quantidade de vértices isolados do grafo)
    // linha (representa uma linha lida)
    // arestas (representa quais vértices foram usados nas arestas)
    // vertices (representa os vértices do grafo)
    int qtdArestas = 0, qtdVertices, qtdComponentes, qtdVerticesIsolados = 0;
    string linha;
    set<char> arestas;
    set<char> vertices;

    // Lendo as arestas do grafo
    while(true) {
        cin >> linha;

        if(linha[0] == '*') break;

        arestas.insert(linha.begin(),linha.end());
        qtdArestas++;
    }

    // Apagando a vírgula e os parênteses do set de arestas
    arestas.erase('(');
    arestas.erase(')');
    arestas.erase(',');

    // Lendo os vértices do grafo
    cin >> linha;
    
    // Inserindo os vértices no set de vértices e apagando a vírgula
    vertices.insert(linha.begin(),linha.end());
    vertices.erase(',');
    
    // Calculando quantos componentes conexos a floresta possui
    qtdVertices = vertices.size();
    qtdComponentes = qtdVertices - qtdArestas;
    
    // Verificando quais vértices são isolados
    for(set<char>::iterator it = vertices.begin(); it != vertices.end(); it++) {
        if(arestas.find(*it) == arestas.end()) qtdVerticesIsolados++;
    }
    
    // Calculando quantas árvores (exceto os vértices isolados) que a floresta possui
    qtdComponentes = qtdComponentes - qtdVerticesIsolados;

    cout << "There are " << qtdComponentes << " tree(s) and " << qtdVerticesIsolados << " acorn(s).\n";
}

int main() {
    // Criando N (representa a quantidade de casos de testes)
    int N;

    cin >> N;

    for(int i = 0; i < N; i++) {
        calculaComponentes();
    }

    return 0;
}