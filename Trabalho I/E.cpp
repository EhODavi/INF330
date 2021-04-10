#include <iostream>

using namespace std;

int main() {
    int n, contador, maiorQtdNiveis = 1, pai;

    cin >> n;

    int pais[n + 1];

    for(int i = 1; i <= n; i++) {
        cin >> pais[i];
    }

    for(int i = 1; i <= n; i++) {
        contador = 1;

        pai = pais[i];

        while(pai != -1) {
            contador++;
            pai = pais[pai];
        }

        if(contador > maiorQtdNiveis) maiorQtdNiveis = contador;
    }

    cout << maiorQtdNiveis << "\n";
    
    return 0;
}