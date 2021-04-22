#include <iostream>
#include <vector>

using namespace std;

// Função que verifica se um componente conexo é bipartido
bool bfsBipartido(vector<vector<int>> &listaAdj, vector<int> &cor, int i, int c) {
    if(cor[i] != -1) return cor[i] == c;
    
    cor[i] = c;

    for(int j = 0; j < listaAdj[i].size(); j++) {
        int corDiferente = 1 - c;
        bool resultado = bfsBipartido(listaAdj,cor,listaAdj[i][j],corDiferente);
        
        if(!resultado) return false;
    }

    return true;
}

void solve(int V) {
    int a,b;
    vector<vector<int>> listaAdj(V + 1);
    vector<int> cor(V + 1, -1); // Vetor que indica as cores que cada vértice possui (inicialmente nenhum vértice possui cor)

    while(cin >> a >> b) {
        if(a == 0 && b == 0) break;

        listaAdj[a].push_back(b);
        listaAdj[b].push_back(a);
    }

    // Verificando se todos os componentes conexos do grafo são bipartidos
    for(int i = 1; i <= V; i++) {
        if(cor[i] == -1) {
            // Se um componente conexo não for bipartido, o grafo não é bipartido
            if(!bfsBipartido(listaAdj,cor,i,0)) {
                cout << "NO\n";
                return;
            }
        }
    }

    // Se todos os componentes conexos forem bipartido, o grafo é bipartido
    cout << "YES\n";
}

int main() {
    int V;

    while(cin >> V) {
        if(V == 0) break;

        solve(V);
    }

    return 0;
}