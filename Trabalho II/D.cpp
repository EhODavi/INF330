#include <iostream>
#include <vector>

using namespace std;

/*
Sample Input
8 4
0 4
1 2
2 3
2 4
3 5
3 6
3 7
6 7
-1 -1
0 0
Sample Output
2 3
3 3
4 2
0 1
*/

void solve(int m, int n) {
    vector<vector<int>> listaAdjacencia(m);
    int x,y;

    while(cin >> x >> y) {
        if(x == -1 && y == -1) break;

        listaAdjacencia[x].push_back(y);
        listaAdjacencia[y].push_back(x);
    }
}


int main() {
    // grau = 10 (de cada estação ferroviária)
    // grafo bidirecional
    // grafo conexo
    // Bombardear estações (vértices)
    // Bombardear apenas um vértice (alvo)
    // Determinar os melhores vértice para bombardear com base no "valor pombo"
    // Valor pombo é o numero minimo de pombos que o inimigo devera lançar (componentes conexos)
    // Vários casos de teste
    // Cada caso de teste começa com uma linha contendo dois inteiros
    // n = número de vértices (são numeradas de 0 a n - 1)
    // m = número de estações a serem determinadas como alvos
    // As proximas linhas serao x y (aresta de x a y)
    // Termina quando há -1 -1
    // n = m = 0 termina o programa
    // Informar quais estações são as melhores para bombardear (m linhas, cada uma com dois inteiros). O primeiro inteiro será o número da estação e o segundo será o valor pombo (numero de componentes conexos)
    // Valor pombo em ordem decrescente, numero de estações em ordem crescente
    // Imprimir uma linha em branco após a saída para cada conjunto de entrada

    int m,n;

    while(cin >> m >> n) {
        if(m == 0 && n == 0) break;

        solve(m,n);
    }

    return 0;
}