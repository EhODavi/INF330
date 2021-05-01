#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class UnionFind {
    public:
        void createSet(int tamanho) {
            representante.resize(tamanho);
            
            for(int i = 0; i < tamanho; i++) {
                representante[i] = i;
            }
        }

        bool isSameSet(int i, int j) {
            return findSet(i) == findSet(j);
        }

        void mergeSet(int i, int j) {
            representante[findSet(i)] = findSet(j);
        }

        int findSet(int elemento) {
            if(representante[elemento] == elemento) return elemento;

            representante[elemento] = findSet(representante[elemento]);

            return representante[elemento];
        }
    private:
        vector<int> representante;
};

struct Aresta {
    double peso;
    int u, v;
};

bool operator<(const Aresta &a, const Aresta &b) {
    return a.peso < b.peso;
}

double distancia(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int kruskal(vector<Aresta> &arestas, double &somaEstrada, double &somaFerrovia, int n, int r) {
    UnionFind conjuntos;
    conjuntos.createSet(n);

    int qtdEstados = n;
    int numArestas = arestas.size();
    int tamanhoArvore = n - 1;
    int qtdArestas = 0;

    for(int i = 0; i < numArestas; i++) {
        if(!conjuntos.isSameSet(arestas[i].u, arestas[i].v)) {
            if(arestas[i].peso <= r) {
                somaEstrada += arestas[i].peso;
                qtdEstados--;
            } else {
                somaFerrovia += arestas[i].peso;
            }

            qtdArestas++;

            if(qtdArestas == tamanhoArvore) break;

            conjuntos.mergeSet(arestas[i].u, arestas[i].v);
        }
    }

    return qtdEstados;
}

void solve() {
    vector<Aresta> arestas;
    int n, r;

    cin >> n >> r;

    vector<pair<int,int>> cidades(n);

    for(int i = 0; i < n; i++) {
        cin >> cidades[i].first >> cidades[i].second;
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            Aresta aresta;
            aresta.u = i;
            aresta.v = j;
            aresta.peso = distancia(cidades[i].first, cidades[i].second, cidades[j].first, cidades[j].second);
            arestas.push_back(aresta);
        }
    }

    sort(arestas.begin(),arestas.end());

    double somaEstrada = 0;
    double somaFerrovia = 0;
    int qtdEstados = kruskal(arestas,somaEstrada,somaFerrovia,n,r);

    cout << qtdEstados << " " << (int) (somaEstrada + 0.5) << " " << (int) (somaFerrovia + 0.5) << "\n";
}

int main() {
    int T;

    cin >> T;

    for(int i = 0; i < T; i++) {
        cout << "Case #" << (i + 1) << ": ";
        solve();
    }

    return 0;
}