#include <iostream>
#include <vector>

using namespace std;

// Função que verifica se a matriz de incidência M representa um grafo simples e se
// a matriz de incidência M é válida
bool check(const vector<vector<int>> &M, int n, int m) {
    // Criando sum (representa a soma de todos os elementos de uma coluna) e
    // columnEqual (representa se a matriz de incidência possui duas colunas iguais)
    int sum;
    bool columnEqual = true;

    // Percorrendo toda a matriz e verificando se a soma de cada coluna é igual a 2
    for(int j = 0; j < m; j++) {
        sum = 0;
            
        for(int i = 0; i < n; i++) {
            sum += M[i][j];
        }

        if(sum != 2) return false;
    }

    // Percorrendo toda a matriz e verificando se há duas colunas iguais
    for(int j = 0; j < m - 1; j++) {
        for(int j1 = j + 1; j1 < m; j1++) {
            columnEqual = true;
            
            for(int i = 0; i < n; i++) {
                if(M[i][j] != M[i][j1]) {
                    columnEqual = false;
                    break;    
                }
            }

            if(columnEqual) return false;
        }
    }

    return true;
}

int main() {
    // Criando t (representa quantos casos de testes),
    // n (representa quantas linhas a matriz de incidência possui) e 
    // m (representa quantas colunas a matriz de incidência possui)
    int t, n, m;

    cin >> t;

    for(int h = 0; h < t; h++) {
        cin >> n >> m;
        
        // Criando M (representa a matriz de incidência)
        vector<vector<int>> M(n, vector<int>(m, 0));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> M[i][j];
            }
        }

        // Verificando se a matriz de incidência lida pode representar um grafo simples
        if(check(M,n,m)) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}