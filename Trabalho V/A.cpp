#include <iostream>
#include <vector>
#include <map>

using namespace std;

void solve(int n, int r) {
    vector<vector<int>> adj(n,vector<int>(n));
    map<string,int> cidade;
    string cidadeOrigem, cidadeDestino;
    int contador = 0, peso;

    for(int i = 0; i < r; i++) {
        cin >> cidadeOrigem >> cidadeDestino >> peso;

        if(cidade.find(cidadeOrigem) == cidade.end()) {
            cidade[cidadeOrigem] = contador;
            contador++;
        }
        
        if(cidade.find(cidadeDestino) == cidade.end()) {
            cidade[cidadeDestino] = contador;
            contador++;
        }

        adj[cidade[cidadeOrigem]][cidade[cidadeDestino]] = peso;
        adj[cidade[cidadeDestino]][cidade[cidadeOrigem]] = peso;
    }

    cin >> cidadeOrigem >> cidadeDestino;

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                adj[i][j] = max(adj[i][j], min(adj[i][k], adj[k][j]));
            }
        }
    }

    cout << adj[cidade[cidadeOrigem]][cidade[cidadeDestino]] << " tons\n";
}

int main() {
    int n, r, contador = 1;

    while(true) {
        cin >> n >> r;

        if(n == 0 && r == 0) break;

        cout << "Scenario #" << contador << "\n";
        
        solve(n,r);
        
        cout << "\n";
        
        contador++;
    }

    return 0;
}