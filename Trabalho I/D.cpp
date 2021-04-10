#include <iostream>
#include <vector>

using namespace std;

// Função que calcula quantos elementos há em uma subárvore dada a raiz
int numElementos(const vector<vector<int>> &arvore, int elemento) {
    // Criando qtdElementos (representa quantos vértices há na subárvore)
    int qtdElementos = 1;

    // Calculando quantos vértices a subárvore possui
    for(int i = 0; i < arvore[elemento].size(); i++) {
        qtdElementos += numElementos(arvore,arvore[elemento][i]);
    }

    return qtdElementos;
}

// Função que calcula o número máximo de arestas que será possível retirar da árvore
int evenForest(int t_nodes, int t_edges, int t_from[], int t_to[]) {
    // Criando arvore [representa a árvore em uma lista de adjacência (guardei apenas os filhos de um vértice)]
    // arestaJaIncluida (representa se uma aresta já foi incluida na lista de adjacência)
    // qtdPar (representa quantas subárvores possuem um número par de vértices)
    // qtdElementos (representa quantos vértices há em uma subárvore)
    vector<vector<int>> arvore(t_nodes + 1);
    vector<bool> arestaJaIncluida(t_edges,false);
    int qtdPar = 0;
    int qtdElementos;

    // Incluindo as arestas na árvore (lista de adjacência)
    for(int i = 1; i <= t_nodes; i++) {
        for(int j = 0; j < t_edges; j++) {
            if(!arestaJaIncluida[j]) {
                if(t_from[j] == i) {
                    arvore[i].push_back(t_to[j]);
                    arestaJaIncluida[j] = true;
                } else if(t_to[j] == i) {
                    arvore[i].push_back(t_from[j]);
                    arestaJaIncluida[j] = true;
                }
            }
        }
    }

    // Contando quantos elementos há em cada subárvore. Se a quantidade for par, podemos
    // retirar a aresta que liga essa subárvore
    for(int i = 1; i <= t_nodes; i++) {
        for(int j = 0; j < arvore[i].size(); j++) {
            qtdElementos = numElementos(arvore, arvore[i][j]);

            if(qtdElementos % 2 == 0) qtdPar++;
        }
    }

    return qtdPar;
}

int main() {
    // Criando t_nodes (representa a quantidade de vértices da árvore) e
    // t_edges (representa a quantidade de arestas da árvore)
    int t_nodes, t_edges;

    cin >> t_nodes >> t_edges;

    // Criando t_from (representa a origem das arestas) e
    // t_to (representa o destino das arestas)
    int t_from[t_edges], t_to[t_edges];

    for(int i = 0; i < t_edges; i++) {
        cin >> t_from[i] >> t_to[i];
    }

    // Calculando o número máximo de arestas que será possível retirar
    int maxEdges = evenForest(t_nodes, t_edges, t_from, t_to);

    cout << maxEdges << "\n";

    return 0;
}