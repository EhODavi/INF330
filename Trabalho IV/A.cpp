#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

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

double distancia(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double kruskal(vector<Aresta> &arestas, int n) {
    UnionFind conjuntos;
    conjuntos.createSet(n);

    double pesoTotal = 0;
    int numArestas = arestas.size();
    int tamanhoArvore = n - 1;
    int qtdArestas = 0;

    for(int i = 0; i < numArestas; i++) {
        if(!conjuntos.isSameSet(arestas[i].u, arestas[i].v)) {
            pesoTotal += arestas[i].peso;
            qtdArestas++;

            if(qtdArestas == tamanhoArvore) break;

            conjuntos.mergeSet(arestas[i].u, arestas[i].v);
        }
    }

    return pesoTotal;
}

void solve() {
    vector<Aresta> arestas;
    int n;
    
    cin >> n;

    vector<pair<double,double>> vertices(n);

    for(int i = 0; i < n; i++) {
        cin >> vertices[i].first >> vertices[i].second;
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            Aresta aresta;
            aresta.u = i;
            aresta.v = j;
            aresta.peso = distancia(vertices[i].first, vertices[i].second, vertices[j].first, vertices[j].second);
            arestas.push_back(aresta);
        }
    }
    
    sort(arestas.begin(),arestas.end());

    double pesoTotal = kruskal(arestas,n);

    cout << fixed << setprecision(2) << pesoTotal << "\n";
}

int main() {
    int T;

    cin >> T;

    for(int i = 0; i < T; i++) {
        solve();
        
        if(i != T - 1) cout << "\n";
    }

    return 0;
}