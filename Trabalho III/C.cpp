#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfs(const vector<vector<int>> &primosAteMil, int s, int t, vector<bool> &visitado) {
    queue<int> numeros;
    int qtd = 0, tamanhoNumeros, numero;

    numeros.push(s);
    visitado[s] = true;

    while(!numeros.empty()) {
        tamanhoNumeros = numeros.size();

        for(int i = 0; i < tamanhoNumeros; i++) {
            numero = numeros.front();
            numeros.pop();

            for(int j = primosAteMil[numero].size() - 1; j >= 0; j--) {
                if(numero + primosAteMil[numero][j] == t) return qtd + 1;
                else if(numero + primosAteMil[numero][j] < t && !visitado[numero + primosAteMil[numero][j]]) {
                    visitado[numero + primosAteMil[numero][j]] = true;
                    numeros.push(numero + primosAteMil[numero][j]); 
                }
            }
        }
        
        qtd++;
    }

    return -1;
}

void solve(const vector<vector<int>> &primosAteMil) {
    vector<bool> visitado(1001,false);
    int s, t, qtd;

    cin >> s >> t;

    if(s == t) qtd = 0;
    else if(s > t) qtd = -1;
    else qtd = bfs(primosAteMil,s,t,visitado);

    cout << qtd;
}

int main() {
    vector<vector<int>> primosAteMil(1001);
    int T, numero, divisor;

    for(int i = 4; i <= 1000; i++) {
        numero = i;
        divisor = 2;

        while(numero != 1) {
            if(numero % divisor == 0) {
                if(divisor != i) primosAteMil[i].push_back(divisor);

                while(numero % divisor == 0) {
                    numero = numero / divisor;
                }
            }

            divisor++;
        }
    }

    cin >> T;

    for(int i = 0; i < T; i++) {
        cout << "Case " << (i + 1) << ": ";
        solve(primosAteMil);
        cout << "\n";
    }

    return 0;
}