#include <iostream>
#include <vector>

using namespace std;

int fordFulkerson(int n, int s, int t, vector<vector<int>> &matrizAdjacencia, vector<vector<int>> &fnet) {
    vector<int> q(n);
    int qf, qb;
    int flow = 0;

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

        flow += bot;
    }

    return flow;
}

void solve(const vector<string> &conteudo) {
    vector<vector<int>> matrizAdjacencia(conteudo.size() + 12, vector<int>(conteudo.size() + 12, 0));
    vector<vector<int>> fnet(conteudo.size() + 12, vector<int>(conteudo.size() + 12, 0));

    for(int i = 1; i <= conteudo.size(); i++) {
        matrizAdjacencia[0][i] = conteudo[i - 1][1] - '0';
    }

    for(int i = 0; i < conteudo.size(); i++) {
        for(int j = 3; j < conteudo[i].size() - 1; j++) {
            matrizAdjacencia[i + 1][conteudo.size() + 1 + (conteudo[i][j] - '0')] = 1;
        }
    }

    for(int i = conteudo.size() + 1; i <= conteudo.size() + 10; i++) {
        matrizAdjacencia[i][conteudo.size() + 11] = 1;
    }

    int fluxoMaximo = fordFulkerson(conteudo.size() + 12, 0, conteudo.size() + 11, matrizAdjacencia, fnet);

    int soma = 0;

    for(int i = 0; i < conteudo.size(); i++) {
        soma += (conteudo[i][1] - '0');
    }

    if(soma == fluxoMaximo) {
        for(int i = conteudo.size() + 1; i <= conteudo.size() + 10; i++) {
            bool ocupado = false;

            for(int j = 1; j <= conteudo.size(); j++) {
                if((fnet[j][i] - fnet[i][j]) == 1) {
                    cout << conteudo[j - 1][0];
                    ocupado = true;
                    break;
                }
            }

            if(!ocupado) cout << "_";
        }
    } else cout << "!";

    cout << "\n";
}

int main() {
    vector<string> conteudo;
    string linha;

    while(getline(cin, linha)) {
        if(linha.size() == 0) {
            solve(conteudo);
            conteudo.clear();
        } else conteudo.push_back(linha);
    }

    solve(conteudo);

    return 0;
}