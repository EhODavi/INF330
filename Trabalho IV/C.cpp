#include <iostream>
#include <vector>
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
    int u, v, c;
};

bool operator<(const Aresta &a, const Aresta &b) {
    return a.c > b.c;
}

int kruskal(vector<Aresta> &arestas, int n) {
    UnionFind conjuntos;
    conjuntos.createSet(n);

    int menorPeso;
    int numArestas = arestas.size();
    int tamanhoArvore = n - 1;
    int qtdArestas = 0;

    for(int i = 0; i < numArestas; i++) {
        if(!conjuntos.isSameSet(arestas[i].u, arestas[i].v)) {
            qtdArestas++;

            if(qtdArestas == tamanhoArvore) {
                menorPeso = arestas[i].c;
                break;
            }

            conjuntos.mergeSet(arestas[i].u, arestas[i].v);
        }
    }

    return menorPeso;
}

void solve() {
    int n, m;

    cin >> n >> m;

    vector<Aresta> arestas(m);

    for(int i = 0; i < m; i++) {
        cin >> arestas[i].u >> arestas[i].v >> arestas[i].c;
    }

    sort(arestas.begin(),arestas.end());

    int menorPeso = kruskal(arestas,n);

    cout << menorPeso << "\n";
}

int main() {
    int N;

    cin >> N;

    for(int i = 0; i < N; i++) {
        cout << "Case #" << (i + 1) << ": ";
        solve();
    }

    return 0;
}