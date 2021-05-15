#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void fordFulkerson(int n, int s, int t, vector<vector<int>> &matrizAdjacencia, vector<vector<int>> &fnet) {
    vector<int> q(n);
    int qf, qb;

    while(true) {
        vector<int> prev(n, -1);
        
        qf = qb = 0;
        
        prev[q[qb++] = s] = -2;
        
        while(qb > qf && prev[t] == -1) {
            for(int u = q[qf++], v = 0; v < n; v++) {
                if(prev[v] == -1 && fnet[u][v] - fnet[v][u] < matrizAdjacencia[u][v]) {
                    prev[q[qb++] = v] = u;
                }
            }
        }

        if(prev[t] == -1) break;

        int bot = 0x7FFFFFFF;
        
        for(int v = t, u = prev[v]; u >= 0; v = u, u = prev[v]) {
            bot = min(bot, matrizAdjacencia[u][v] - fnet[u][v] + fnet[v][u]);
        }

        for(int v = t, u = prev[v]; u >= 0; v = u, u = prev[v]) {
            fnet[u][v] += bot;
        }
    }
}

void solve() {
    string nome;
    int n, qtdNomesTotal = 0, qtdNomes;

    cin >> n;

    vector<vector<string>> nomesPossiveis(n);

    for(int i = 0; i < n; i++) {
        cin >> qtdNomes;

        qtdNomesTotal += qtdNomes;

        for(int j = 0; j < qtdNomes; j++) {
            cin >> nome;
            
            transform(nome.begin(), nome.end(), nome.begin(), ::tolower);
            nome[0] = (char) toupper(nome[0]);
            
            nomesPossiveis[i].push_back(nome);
        }
    }

    vector<vector<int>> matrizAdjacencia(2 * n + qtdNomesTotal + 2, vector<int>(2 * n + qtdNomesTotal + 2, 0));
    vector<vector<int>> fnet(2 * n + qtdNomesTotal + 2, vector<int>(2 * n + qtdNomesTotal + 2, 0));

    for(int i = 1; i <= n; i++) {
        matrizAdjacencia[0][i] = 1;
    }

    int inicioPalavras = n + 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < nomesPossiveis[i].size(); j++) {
            matrizAdjacencia[i + 1][inicioPalavras] = 1;

            int primeiraLetra = (int) nomesPossiveis[i][j][0] - 65;
            
            if(primeiraLetra >= 0 && primeiraLetra <= n - 1) {
                matrizAdjacencia[inicioPalavras][n + qtdNomesTotal + 1 + primeiraLetra] = 1;
            }

            inicioPalavras++;
        }
    }

    for(int i = n + qtdNomesTotal + 1; i <= 2 * n + qtdNomesTotal; i++) {
        matrizAdjacencia[i][2 * n + qtdNomesTotal + 1] = 1;
    }

    fordFulkerson(2 * n + qtdNomesTotal + 2, 0, 2 * n + qtdNomesTotal + 1, matrizAdjacencia, fnet);

    for(int i = n + qtdNomesTotal + 1; i <= 2 * n + qtdNomesTotal; i++) {
        for(int j = n + 1; j <= n + qtdNomesTotal; j++) {
            if((fnet[j][i] - fnet[i][j]) == 1) {
                int numPalavra = j - (n + 1);
                int contador = 0;

                bool encontrei = false;
                for(int k = 0; k < n; k++) {
                    for(int l = 0; l < nomesPossiveis[k].size(); l++) {
                        if(numPalavra == contador) {
                            cout << nomesPossiveis[k][l] << "\n";
                            encontrei = true;
                            break;
                        }
                        contador++;
                    }
                    
                    if(encontrei) break;
                }

                break;
            }
        }
    }
}

int main() {
    int N;

    cin >> N;

    for(int i = 1; i <= N; i++) {
        cout << "Case #" << i << ":\n";
        solve();
    }
    
    return 0;
}