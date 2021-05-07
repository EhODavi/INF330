#include <iostream>
#include <vector>
#include <set>

using namespace std;

long long int dijkstra(vector<vector<pair<int, long long int>>> &listaAdjacencia, int S, int T, int N) {
    set<pair<long long int, int>> heap;
    vector<long long int> custo(N, 10987654321);
    vector<int> pai(N, -1);

    custo[S] = 0;
    pai[S] = S;

    heap.insert(make_pair(custo[S],S));

    while(!heap.empty()) {
        int v = heap.begin()->second;

        if(v == T) return custo[T];

		long long int peso = heap.begin()->first;
		heap.erase(heap.begin());

        for(int i = 0; i < listaAdjacencia[v].size(); i++) {
            pair<int, long long int> x = listaAdjacencia[v][i];

            if(custo[x.first] == 10987654321) {
                custo[x.first] = custo[v] + x.second;
                heap.insert(make_pair(custo[x.first],x.first));
                pai[x.first] = v;
            } else if(custo[v] + x.second < custo[x.first]) {
                heap.erase(heap.find(make_pair(custo[x.first],x.first)));
                custo[x.first] = custo[v] + x.second;
                heap.insert(make_pair(custo[x.first],x.first));
                pai[x.first] = v;
            }
        }
    }

    return 0;
}

void solve(int N) {
    vector<vector<pair<int, long long int>>> listaAdjacencia(N);
    int Ai, Li, Q, S, T;

    for(int i = 1; i <= (N - 1); i++) {
        cin >> Ai >> Li;

        listaAdjacencia[i].push_back(make_pair(Ai, Li));
        listaAdjacencia[Ai].push_back(make_pair(i, Li));
    }

    cin >> Q;

    for(int i = 0; i < Q; i++) {
        cin >> S >> T;
        
        if(i != Q - 1) cout << dijkstra(listaAdjacencia,S,T,N) << " ";
        else cout << dijkstra(listaAdjacencia,S,T,N);
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