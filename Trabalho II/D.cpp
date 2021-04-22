#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void tarjan(int u, const vector<vector<int>> &listaAdjacencia, vector<int> &dfsPai, vector<int> &dfsNum, vector<int> &dfsLow, vector<int> &numPombo, int &dfsContador) {
    dfsLow[u] = dfsNum[u] = ++dfsContador;

    for(int v:listaAdjacencia[u]) {
        if(dfsNum[v] == 0) {
            dfsPai[v] = u;

            tarjan(v,listaAdjacencia,dfsPai,dfsNum,dfsLow,numPombo,dfsContador);

            // Se a aresta for uma ponte, incrementamos a quantidade de pombos necessários do vértice u e v em 1
            if(dfsLow[v] > dfsNum[u]) {
                numPombo[u]++;
                numPombo[v]++;
            }

            dfsLow[u] = min(dfsLow[u],dfsLow[v]);
        } else if(v != dfsPai[u]) dfsLow[u] = min(dfsLow[u],dfsNum[v]);
    }
}

void tarjan(const vector<vector<int>> &listaAdjacencia, vector<int> &numPombo) {
    int n = listaAdjacencia.size();
    vector<int> dfsPai(n,-1), dfsLow(n,0), dfsNum(n,0);
    int dfsContador = 0;

    tarjan(0,listaAdjacencia,dfsPai,dfsNum,dfsLow,numPombo,dfsContador);  
}

void solve(int n, int m) {
    vector<vector<int>> listaAdjacencia(n);
    int x,y;

    while(cin >> x >> y) {
        if(x == -1 && y == -1) break;

        listaAdjacencia[x].push_back(y);
        listaAdjacencia[y].push_back(x);
    }

    vector<int> numPombo(n,0); // Criando um vetor que indica quantos pombos serão necessários caso o vértice seja bombardeado
    
    tarjan(listaAdjacencia,numPombo);

    // Caso algum vertice possua arestas que não são pontes, incrementamos a quantidade de pombos em 1
    for(int i = 0; i < n; i++) {
        if(numPombo[i] != listaAdjacencia[i].size()) {
            numPombo[i]++;
        }
    }

    vector<pair<int,int>> verticesQtdPombos(n); // Criando um vetor de pair que indica quantos pombos serão necessários para cada vértice

    for(int i = 0; i < n; i++) {
        verticesQtdPombos[i].first = -numPombo[i]; // Armazenando negativo para ser ordenado de maneira decrescente
        verticesQtdPombos[i].second = i;
    }

    sort(verticesQtdPombos.begin(),verticesQtdPombos.end());

    for(int i = 0; i < m; i++) {
        cout << verticesQtdPombos[i].second << " " << -verticesQtdPombos[i].first << "\n";
    }
}

int main() {
    int n,m;

    while(cin >> n >> m) {
        if(n == 0 && m == 0) break;

        solve(n,m);

        cout << "\n";
    }

    return 0;
}