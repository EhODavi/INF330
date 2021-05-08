#include <iostream>
#include <vector>

using namespace std;

struct Vertice {
    int pai, nivel;
    long long int peso;
};

long long int ancestralMaisBaixo(vector<Vertice> &pais, int S, int T) {
    long long int somaS1 = 0, somaT1 = 0;
    int S1 = S, T1 = T;

    if(pais[S].nivel > pais[T].nivel) {
        for(int i = 0; i < (pais[S].nivel - pais[T].nivel); i++) {
            somaS1 += pais[S1].peso;
            S1 = pais[S1].pai;
        }
    } else {
        for(int i = 0; i < (pais[T].nivel - pais[S].nivel); i++) {
            somaT1 += pais[T1].peso;
            T1 = pais[T1].pai;
        }
    }

    while(S1 != T1) {
        somaS1 += pais[S1].peso;
        somaT1 += pais[T1].peso;
        S1 = pais[S1].pai;
        T1 = pais[T1].pai;
    }

    return somaS1 + somaT1;
}

void solve(int N) {
    vector<Vertice> pais(N);
    int Ai, Li, Q, S, T;

    pais[0].pai = -1;
    pais[0].nivel = 0;
    pais[0].peso = 0;

    for(int i = 1; i <= (N - 1); i++) {
        cin >> Ai >> Li;

        pais[i].pai = Ai;
        pais[i].nivel = pais[Ai].nivel + 1;
        pais[i].peso = Li;
    }

    cin >> Q;

    for(int i = 0; i < Q; i++) {
        cin >> S >> T;
        
        if(i != Q - 1) cout << ancestralMaisBaixo(pais,S,T) << " ";
        else cout << ancestralMaisBaixo(pais,S,T);
    }

    cout << "\n";
}

int main() {
    int N;

    while(true) {
        cin >> N;

        if(N == 0) break;

        solve(N);
    }

    return 0;
}