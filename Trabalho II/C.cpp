#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfs(vector<vector<char>> &map) {
    queue<pair<int,int>> joe, fogo;
    int qtdJoe = 0;

    for(int i = 1; i <= map.size() - 2; i++) {
        for(int j = 1; j <= map[i].size() - 2; j++) {
            if(map[i][j] == 'J') joe.push(make_pair(i,j));
            else if(map[i][j] == 'F') fogo.push(make_pair(i,j));
        }
    }

    while(true) {
        if(joe.empty()) return -1; // Se a fila de Joe esvaziar, quer dizer que ele não conseguiu sair do labirinto

        int tamanhoFogo = fogo.size();

        // Alastrando o fogo
        for(int i = 0; i < tamanhoFogo; i++) {
            pair<int,int> posicao = fogo.front();
            fogo.pop();

            // Verificando se o fogo pode "andar"
            if(map[posicao.first + 1][posicao.second] == '.' || map[posicao.first + 1][posicao.second] == 'J') {
                fogo.push(make_pair(posicao.first + 1,posicao.second));
                map[posicao.first + 1][posicao.second] = 'F';
            }
            
            // Verificando se o fogo pode "andar"
            if(map[posicao.first - 1][posicao.second] == '.' || map[posicao.first - 1][posicao.second] == 'J') {
                fogo.push(make_pair(posicao.first - 1,posicao.second));
                map[posicao.first - 1][posicao.second] = 'F';
            }
            
            // Verificando se o fogo pode "andar"
            if(map[posicao.first][posicao.second + 1] == '.' || map[posicao.first][posicao.second + 1] == 'J') {
                fogo.push(make_pair(posicao.first,posicao.second + 1));
                map[posicao.first][posicao.second + 1] = 'F';
            }
            
            // Verificando se o fogo pode "andar"
            if(map[posicao.first][posicao.second - 1] == '.' || map[posicao.first][posicao.second - 1] == 'J') {
                fogo.push(make_pair(posicao.first,posicao.second - 1));
                map[posicao.first][posicao.second -1] = 'F';
            }
        }

        int tamanhoJoe = joe.size();
        
        // Andando com o Joe
        for(int i = 0; i < tamanhoJoe; i++) {
            pair<int,int> posicao = joe.front();
            joe.pop();
            
            // Verificando se o Joe pode "andar". Se ele chegar na saída, retornamos em quantos passos ele saiu
            if(map[posicao.first + 1][posicao.second] == '.' || map[posicao.first + 1][posicao.second] == 'E') {
                if(map[posicao.first + 1][posicao.second] == 'E') return qtdJoe + 1;
                
                joe.push(make_pair(posicao.first + 1,posicao.second));
                map[posicao.first + 1][posicao.second] = 'J';
            }
            
            // Verificando se o Joe pode "andar". Se ele chegar na saída, retornamos em quantos passos ele saiu
            if(map[posicao.first - 1][posicao.second] == '.' || map[posicao.first - 1][posicao.second] == 'E') {
                if(map[posicao.first - 1][posicao.second] == 'E') return qtdJoe + 1;
                
                joe.push(make_pair(posicao.first - 1,posicao.second));
                map[posicao.first - 1][posicao.second] = 'J';
            }
            
            // Verificando se o Joe pode "andar". Se ele chegar na saída, retornamos em quantos passos ele saiu
            if(map[posicao.first][posicao.second + 1] == '.' || map[posicao.first][posicao.second + 1] == 'E') {
                if(map[posicao.first][posicao.second + 1] == 'E') return qtdJoe + 1;
                
                joe.push(make_pair(posicao.first,posicao.second + 1));
                map[posicao.first][posicao.second + 1] = 'J';
            }
            
            // Verificando se o Joe pode "andar". Se ele chegar na saída, retornamos em quantos passos ele saiu
            if(map[posicao.first][posicao.second - 1] == '.' || map[posicao.first][posicao.second - 1] == 'E') {
                if(map[posicao.first][posicao.second - 1] == 'E') return qtdJoe + 1;
                
                joe.push(make_pair(posicao.first,posicao.second - 1));
                map[posicao.first][posicao.second - 1] = 'J';
            }
        }

        qtdJoe++;
    }

	return qtdJoe;
}

void solve() {
    int R, C, qtdJoe; // qtdJoe indica quantos passos o Joe precisou para sair do labirinto
    string line;

    cin >> R >> C;

    vector<vector<char>> map(R + 2,vector<char>(C + 2,'E')); // A matriz tem 2 linhas e 2 colunas a mais. Preenchi com 'E' que significa saída. Ou seja, se o Joe chegar em um E, ele saiu do labirinto

    for(int i = 1; i <= R; i++) {
        cin >> line;
        for(int j = 1; j <= C; j++) {
            map[i][j] = line[j - 1];
        }
    }

    qtdJoe = bfs(map);

    if(qtdJoe != -1) cout << qtdJoe << "\n";
    else cout << "IMPOSSIBLE\n";
}

int main() {
    int T;

    cin >> T;

    for(int i = 0; i < T; i++) {
        solve();
    }

    return 0;
}