#include <iostream>

using namespace std;

/*
Sample Input
3
6 6 2
1 1 6 6
6 6 1 1
7 7 4
1 1 1 6
6 1 6 6
6 6 1 1
4 3 5 1
9 8 6
2 2 4 4
4 5 3 2
3 4 2 2
3 2 4 4
4 5 2 2
2 1 3 4
Sample Output
Yes
No
No
*/

int main() {
    // Problema de transito
    // Tornar as ruas de mão única (novo plano de malha viária) enquanto mantêm uma curta distância entre alguns pares ordenados de locais
    // As ruas formam uma grade ortogonal
    // Avenidas (norte-sul) | Ruas (leste-oeste)
    // Uma rota na cidade é definida por dois cruzamento de ruas, o local de partida e de meta
    // Uma rota tem um caminho legal se for possível dirigir sem transgredir a lei e sair do inicio e chegar no destino
    // Pode haver muitos caminhos possíveis para cada rota
    // Um caminho legal é considerado simples se requer no máximo uma conversão, ou seja, podemos usar no máximo uma rua e uma avenida
    // Um caminho simples terá preferência sobre um não simples por ser mais rápido
    // Como a grade é de mão única, pode haver rotas para as quais não existe um caminho simples
    // Na secretaria, há uma lista de percursos importantes que devem ter caminhos simples
    // Escrever um programa que determina se será possível fixar as direções das ruas e avenidas de modo que cada rota da lista tenha pelo menos um caminho simples
    // Na primeira linha da entrada há um único inteiro n informando quantos casos de testes
    // Cada descrição de cidade começa com uma linha com três inteiros: S A m (S é o número de ruas, A é o número de avenidas, m é o número de rotas que devem ter pelo menos um caminho simples)
    // As proximas m linhas definem estas rotas, uma em cada linha
    // Cada definição de rota é da forma s1 a1 s2 a2 (em que o local de inicio é no cruzamento da rua s1 com a avenida a1 e o destino é o cruzamento da rua s2 com a avenida a2)
    // Imprimir 'Yes' ou 'No'

    return 0;
}