#include <iostream>
#include <vector>

using namespace std;

void imprime(vector<vector<int>> &matriz, int i) {
    for(int j = 1; j <= 50; j++) {
        if(matriz[i][j] != 0) {
            matriz[i][j]--;
            matriz[j][i]--;

            imprime(matriz,j);

            cout << j << " " << i << "\n";
        }
    }
}

bool circuitoEuleriano(const vector<vector<int>> &matriz) {
    int grau;
    bool linhaLoop;

    for(int i = 1; i <= 50; i++) {
        linhaLoop = true;
        grau = 0;

        for(int j = 1; j <= 50; j++) {
            if(matriz[i][j] != 0 && i != j) linhaLoop = false;

            grau += matriz[i][j];
        }

        linhaLoop = linhaLoop && (matriz[i][i] != 0);

        if(grau % 2 != 0 || linhaLoop) return false;
    }

    return true;
}

void colar() {
    vector<vector<int>> matriz(51, vector<int>(51, 0));
    int N, cor1, cor2;
    
    cin >> N;

    for(int i = 0; i < N; i++) {
        cin >> cor1 >> cor2;

        matriz[cor1][cor2]++;
        matriz[cor2][cor1]++;
    }

    if(circuitoEuleriano(matriz)) {
        for(int i = 1; i <= 50; i++) {
            imprime(matriz,i);
        }
    } else {
        cout << "some beads may be lost\n";
    }
}

int main() {
    int T;

    cin >> T;

    for(int i = 1; i <= T; i++) {
        cout << "Case #" << i << "\n";
        
        colar();
        
        if(i != T) cout << "\n";
    }

    return 0;
}