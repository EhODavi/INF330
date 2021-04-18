#include <iostream>
#include <vector>

using namespace std;

bool protect(vector<vector<char>> &field) {
    for(int i = 0; i < field.size(); i++) {
        for(int j = 0; j < field[i].size(); j++) {
            if(field[i][j] == 'S') {
                if(i != field.size() - 1) {
                    if(field[i + 1][j] == 'W') return false;
                    else if(field[i + 1][j] == '.') field[i + 1][j] = 'D';
                }

                if(i != 0) {
                    if(field[i - 1][j] == 'W') return false;
                    else if(field[i - 1][j] == '.') field[i - 1][j] = 'D';
                }

                if(j != field[i].size() - 1) {
                    if(field[i][j + 1] == 'W') return false;
                    else if(field[i][j + 1] == '.') field[i][j + 1] = 'D';
                }

                if(j != 0) {
                    if(field[i][j - 1] == 'W') return false;
                    else if(field[i][j - 1] == '.') field[i][j - 1] = 'D';
                }
            }
        }
    }

    return true;
}

int main() {
    int R, C;
    string line;

    cin >> R >> C;

    vector<vector<char>> field(R,vector<char>(C));

    for(int i = 0; i < R; i++) {
        cin >> line;
        
        for(int j = 0; j < C; j++) {
            field[i][j] = line[j];
        }
    }

    if(protect(field)) {
        cout << "Yes\n";
        
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                cout << field[i][j];
            }
            cout << "\n";
        }
    } else {
        cout << "No\n";
    }

    return 0;
}