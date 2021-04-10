#include <iostream>
#include <vector>

using namespace std;

int numElementos(const vector<vector<int>> &arvore, int elemento) {
    int qtdElementos = 1;

    for(int i = 0; i < arvore[elemento].size(); i++) {
        qtdElementos += numElementos(arvore,arvore[elemento][i]);
    }

    return qtdElementos;
}

int evenForest(int t_nodes, int t_edges, int t_from[], int t_to[]) {
    vector<vector<int>> arvore(t_nodes + 1);
    vector<bool> arestaJaIncluida(t_edges,false);
    int qtdPar = 0;
    int qtdElementos;

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

    for(int i = 1; i <= t_nodes; i++) {
        for(int j = 0; j < arvore[i].size(); j++) {
            qtdElementos = numElementos(arvore, arvore[i][j]);

            if(qtdElementos % 2 == 0) qtdPar++;
        }
    }

    return qtdPar;
}

int main() {
    int t_nodes, t_edges;

    cin >> t_nodes >> t_edges;

    int t_from[t_edges], t_to[t_edges];

    for(int i = 0; i < t_edges; i++) {
        cin >> t_from[i] >> t_to[i];
    }

    int maxEdges = evenForest(t_nodes, t_edges, t_from, t_to);

    cout << maxEdges << "\n";

    return 0;
}