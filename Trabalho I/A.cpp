#include <iostream>
#include <vector>

using namespace std;

bool check(const vector<vector<int>> &M, int n, int m) {
    int sum;
    bool columnEqual = true;

    for(int j = 0; j < m; j++) {
        sum = 0;
            
        for(int i = 0; i < n; i++) {
            sum += M[i][j];
        }

        if(sum != 2) return false;
    }

    
    for(int j = 0; j < m - 1; j++) {
        for(int j1 = j + 1; j1 < m; j1++) {
            columnEqual = true;
            
            for(int i = 0; i < n; i++) {
                if(M[i][j] != M[i][j1]) {
                    columnEqual = false;
                    break;    
                }
            }

            if(columnEqual) return false;
        }
    }

    return true;
}

int main() {
    int t, n, m;

    cin >> t;

    for(int h = 0; h < t; h++) {
        cin >> n >> m;
        
        vector<vector<int>> M(n, vector<int>(m, 0));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> M[i][j];
            }
        }

        if(check(M,n,m)) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}