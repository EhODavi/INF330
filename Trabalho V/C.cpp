#include <iostream>
#include <vector>

using namespace std;

struct Aresta {
    int x, y, t;
};

void solve() {
    int n, m, x, y, t;

    cin >> n >> m;

    vector<Aresta> arestas(m);

    for(int i = 0; i < m; i++) {
        cin >> arestas[i].x >> arestas[i].y >> arestas[i].t;
    }

    vector<int> pai(n, -1), custo(n, 987654321);

    custo[0] = 0;
    pai[0] = 0;

    for(int i = 0; i < (n - 1); i++) {
        for(int j = 0; j < m; j++) {
            if(custo[arestas[j].x] + arestas[j].t < custo[arestas[j].y]) {
                custo[arestas[j].y] = custo[arestas[j].x] + arestas[j].t;
                pai[arestas[j].y] = arestas[j].x;
            }
        }
    }

    bool possuiCicloNegativo = false;

    for(int j = 0; j < m; j++) {
        if(custo[arestas[j].x] + arestas[j].t < custo[arestas[j].y]) {
            possuiCicloNegativo = true;
        }
    }

    if(possuiCicloNegativo) {
        cout << "possible\n";
    } else {
        cout << "not possible\n";
    }
}

int main() {
    int c;

    cin >> c;

    for(int i = 0; i < c; i++) {
        solve();
    }

    return 0;
}