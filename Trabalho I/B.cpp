#include <iostream>
#include <vector>

using namespace std;

// Função que insere as pérolas no colar. Dada uma pérola,
// está função tenta inserir todas as pérolas possíveis a partir desta pérola
void insereColar(vector<vector<int>> &matriz, vector<pair<int,int>> &colar, int i) {
    for(int j = 1; j <= 50; j++) {
        // Se existir uma pérola da cor i j, tentaremos inserir outras pérolas a partir dela
        if(matriz[i][j] != 0) {
            // Informando que a pérola acabou de ser usada
            matriz[i][j]--;
            matriz[j][i]--;

            // Chamando a função insereColar para inserir o vizinho da pérola atual
            insereColar(matriz,colar,j);

            // Como a função é recursiva, inserimos na ordem contrária
            colar.push_back(make_pair(j,i));
        }
    }
}

// Função que verifica se um grafo pode ser euleriano, ou seja,
// todos os vértices possuem grau par (mas não verifica se o grafo é CONEXO!)
bool podeSerEuleriano(const vector<vector<int>> &matriz) {
    // Criando grau (representa o grau de um vértice)
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

// Função que armazena as pérolas em uma matriz e tenta montar o colar
void colar() {
    // Criando matriz (representa uma matriz de adjacência de todas as cores possíveis) e
    // N (representa a quantidade de pérolas que serão informadas)
    // cor1 (representa a primeira cor de uma pérola)
    // cor2 (representa a segunda cor de uma pérola)
    vector<vector<int>> matriz(51, vector<int>(51, 0));
    int N, cor1, cor2;
    
    cin >> N;

    for(int i = 0; i < N; i++) {
        cin >> cor1 >> cor2;

        matriz[cor1][cor2]++;
        matriz[cor2][cor1]++;
    }
    
    // Se o grafo pode ser euleriano, ou seja, todos os vértices possuem grau par
    // tentaremos montar o colar (mas o grafo ainda pode ser DESCONEXO!).
    // Se o grafo não pode ser euleriano, imprimimos que não será possível montar o colar
    if(podeSerEuleriano(matriz)) {
        // Criando colar (representa o colar da menina)
        vector<pair<int,int>> colar;
        
        // Inserindo as pérolas no colar
        for(int i = 1; i <= 50; i++) {
            insereColar(matriz,colar,i);
        }
        
        // Criando ehColar (para verificar se o colar é válido ou não)
        bool ehColar = true;
        
        // Verificando se o colar é válido ou não
        for(int i = 0; i < colar.size() - 1; i++) {
            if(colar[i].second != colar[i + 1].first) {
                ehColar = false;
                break;
            }
        }

        // Verificando se o colar fecha
        if(colar[0].first != colar[colar.size() - 1].second) ehColar = false;

        // Se for um colar válido, imprimimos a sequência de pérolas.
        // Se não, informamos que não será possível montar o colar.
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
    // Criando T (representa a quantidade de casos de teste)
    int T;

    cin >> T;

    for(int i = 1; i <= T; i++) {
        cout << "Case #" << i << "\n";
        
        colar();
        
        if(i != T) cout << "\n";
    }

    return 0;
}