#include <iostream>
#include <vector>

using namespace std;

int fordFulkerson(int n, int s, int t, vector<vector<int>> &matrizAdjacencia) {
    vector<vector<int>> fnet(n, vector<int>(n, 0));
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

void solve() {
    int n, m, ki, adesivo;

    cin >> n >> m;

    vector<vector<int>> qtdAdesivos(n, vector<int>(m, 0));

    for(int i = 0; i < n; i++) {
        cin >> ki;

        for(int j = 0; j < ki; j++) {
            cin >> adesivo; adesivo--;
            qtdAdesivos[i][adesivo]++;
        }
    }

    vector<vector<int>> matrizAdjacencia(n + m + 1, vector<int>(n + m + 1, 0));
    
    for(int i = 1; i <= m; i++) {
        matrizAdjacencia[0][i] = qtdAdesivos[0][i - 1];
    }

    for(int i = 1; i <= m; i++) {
        for(int j = m + 1; j <= m + n - 1; j++) {
            if(qtdAdesivos[j - m][i - 1] == 0) {
                matrizAdjacencia[i][j] = 1;
            }
        }
    }
    
    for(int j = m + 1; j <= m + n - 1; j++) {
        for(int i = 1; i <= m; i++) {
            if(qtdAdesivos[j - m][i - 1] > 1) {
                matrizAdjacencia[j][i] = qtdAdesivos[j - m][i - 1] - 1;
            }
        }
    }

    for(int i = 1; i <= m; i++) {
        matrizAdjacencia[i][m + n] = 1;
    }

    cout << fordFulkerson(n + m + 1, 0, m + n, matrizAdjacencia) << "\n";
}

int main() {
    int T;

    cin >> T;

    for(int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}