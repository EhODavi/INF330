#include <iostream>
#include <vector>

using namespace std;

void insereColar(vector<vector<int>> &matriz, vector<pair<int,int>> &colar, int i) {
    for(int j = 1; j <= 50; j++) {
        if(matriz[i][j] != 0) {
            matriz[i][j]--;
            matriz[j][i]--;

            insereColar(matriz,colar,j);

            colar.push_back(make_pair(j,i));
        }
    }
}

bool podeSerEuleriano(const vector<vector<int>> &matriz) {
    int grau;

    for(int i = 1; i <= 50; i++) {
        grau = 0;

        for(int j = 1; j <= 50; j++) {
            grau += matriz[i][j];
        }
        
        if(grau % 2 != 0) return false;
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

    if(podeSerEuleriano(matriz)) {
        vector<pair<int,int>> colar;
        
        for(int i = 1; i <= 50; i++) {
            insereColar(matriz,colar,i);
        }
        
        bool ehColar = true;
        
        for(int i = 0; i < colar.size() - 1; i++) {
            if(colar[i].second != colar[i + 1].first) {
                ehColar = false;
                break;
            }
        }

        if(colar[0].first != colar[colar.size() - 1].second) ehColar = false;

        if(ehColar) {
            for(int i = 0; i < colar.size(); i++) {
                cout << colar[i].first << " " << colar[i].second << "\n";
            }
        } else {
            cout << "some beads may be lost\n";
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