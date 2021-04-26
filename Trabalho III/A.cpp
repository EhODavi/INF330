#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

void bfs(const string &tabuleiroInicial, map<string,bool> &visitado, map<string,pair<int,string>> &tabuleirosPossiveis) {
    queue<pair<string,string>> tabuleiros;
    pair<string,string> tabuleiro;
    vector<pair<string,string>> vizinhos(6);
    int qtd = 1, tamanhoTabuleiros;

    tabuleiros.push(make_pair(tabuleiroInicial,""));
    visitado[tabuleiroInicial] = true;

    while(!tabuleiros.empty()) {
        tamanhoTabuleiros = tabuleiros.size();

        for(int i = 0; i < tamanhoTabuleiros; i++) {
            tabuleiro = tabuleiros.front();
            tabuleiros.pop();

            vizinhos[0] = tabuleiro;
            swap(vizinhos[0].first[0],vizinhos[0].first[2]);
            swap(vizinhos[0].first[0],vizinhos[0].first[1]);
            vizinhos[0].second = "H1" + vizinhos[0].second;

            vizinhos[1] = tabuleiro;
            swap(vizinhos[1].first[3],vizinhos[1].first[5]);
            swap(vizinhos[1].first[3],vizinhos[1].first[4]);
            vizinhos[1].second = "H2" + vizinhos[1].second;

            vizinhos[2] = tabuleiro;
            swap(vizinhos[2].first[6],vizinhos[2].first[8]);
            swap(vizinhos[2].first[6],vizinhos[2].first[7]);
            vizinhos[2].second = "H3" + vizinhos[2].second;

            vizinhos[3] = tabuleiro;
            swap(vizinhos[3].first[0],vizinhos[3].first[6]);
            swap(vizinhos[3].first[3],vizinhos[3].first[6]);
            vizinhos[3].second = "V1" + vizinhos[3].second;

            vizinhos[4] = tabuleiro;
            swap(vizinhos[4].first[1],vizinhos[4].first[7]);
            swap(vizinhos[4].first[4],vizinhos[4].first[7]);
            vizinhos[4].second = "V2" + vizinhos[4].second;

            vizinhos[5] = tabuleiro;
            swap(vizinhos[5].first[2],vizinhos[5].first[8]);
            swap(vizinhos[5].first[5],vizinhos[5].first[8]);
            vizinhos[5].second = "V3" + vizinhos[5].second;

            for(int i = 0; i < 6; i++) {
                if(!visitado[vizinhos[i].first]) {
                    visitado[vizinhos[i].first] = true;
                    tabuleirosPossiveis[vizinhos[i].first] = make_pair(qtd,vizinhos[i].second);
                    tabuleiros.push(vizinhos[i]);
                }
            }
        }

        qtd++;
    }
}

int main() {
    string tabuleiro;
    char numero;
    int contador = 0;
    map<string,bool> visitado;
    map<string,pair<int,string>> tabuleirosPossiveis;
    string tabuleiroInicial = "123456789";

    bfs(tabuleiroInicial,visitado,tabuleirosPossiveis);

    while(true) {
        cin >> numero;

        if(numero == '0') break;

        tabuleiro += numero;

        contador++;

        if(contador % 9 == 0) {
            if(visitado[tabuleiro]) {
                cout << tabuleirosPossiveis[tabuleiro].first << " " << tabuleirosPossiveis[tabuleiro].second << "\n";
            } else cout << "Not solvable\n";
            
            tabuleiro = "";
        }
    }

    return 0;
}