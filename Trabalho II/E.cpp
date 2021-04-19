#include <iostream>
#include <vector>

using namespace std;

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
    vector<int> cor(V + 1, -1);

    while(cin >> a >> b) {
        if(a == 0 && b == 0) break;

        listaAdj[a].push_back(b);
        listaAdj[b].push_back(a);
    }

    for(int i = 1; i <= V; i++) {
        if(cor[i] == -1) {
            if(!bfsBipartido(listaAdj,cor,i,0)) {
                cout << "NO\n";
                return;
            }
        }
    }

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