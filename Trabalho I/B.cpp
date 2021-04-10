#include <iostream>
#include <vector>

using namespace std;

void imprime(vector<vector<int>> &matriz) {

}

bool euleriano(const vector<vector<int>> &matriz) {
    bool linhaVazia, linhaComApenasLoop;
    int grau;

    for(int i = 0; i < 50; i++) {
        linhaVazia = linhaComApenasLoop = true;
        grau = 0;

        for(int j = 0; j < 50; j++) {
            if(matriz[i][j] != 0) linhaVazia = false;
            if(matriz[i][j] == 1) linhaVazia = linhaComApenasLoop = false;
            
            grau += matriz[i][j];
        }

        if(grau % 2 != 0 || linhaVazia || linhaComApenasLoop) return false;
    }

    return true;
}

void colar() {
    vector<vector<int>> matriz(50, vector<int>(50, 0));
    int N, cor1, cor2;
    
    cin >> N;

    for(int i = 0; i < N; i++) {
        cin >> cor1 >> cor2;

        if(cor1 == cor2) matriz[cor1 - 1][cor2 - 1] += 2;
        else {
            matriz[cor1 - 1][cor2 - 1]++;
            matriz[cor2 - 1][cor1 - 1]++;
        }
    }

    if(euleriano(matriz)) {
        imprime(matriz);
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