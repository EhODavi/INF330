#include <iostream>
#include <vector>

using namespace std;

#define f(i,k) for(int i = 0; i < k; i++)

struct Sat2 {
public:
    Sat2(int numVariaveis) {
        vars = numVariaveis;
        implica = vector<vector<vector<int>>>(numVariaveis + 1, vector<vector<int>>(2));
        valor = vector<int>(numVariaveis + 1, -1);     
    }
    
    void addClausula(int c1, bool v1, int c2, bool v2) {
        implica[c1][!v1].push_back(c2 * (v2 ? 1:-1));
        implica[c2][!v2].push_back(c1 * (v1 ? 1:-1));
    }

    void addImplicacao(int c1, bool valor, int c2, bool valor2) {
        addClausula(c1, !valor, c2, valor2);
    }

    bool satisfativel() {       
        for(int i = 1; i <= vars; ++i) {
           if(!verificaVariavel(i)) return false;
        }
        
        return true;
    }
private:
    vector<vector<vector<int>>> implica;
    vector<int> valor;
    int vars;
    
    bool funciona(int x, int val) {
        if(valor[x] != -1) return valor[x] == val;

        valor[x] = val;
        
        f(i, implica[x][val].size()) 
            if(!funciona(abs(implica[x][val][i]), (implica[x][val][i] < 0 ? 0:1))) {
                valor[x] = -1;
                return false;
            }                     
        return true; 
    }

    bool verificaVariavel(int i) { 
        f(k, vars + 1) valor[k] = -1;
        if(funciona(i,0)) return true;
        f(k, vars + 1) valor[k] = -1;
        if(funciona(i,1)) return true;
        
        return false; 
    }
};

void solve() {
    int S, A, m, s1, a1, s2, a2;

    cin >> S >> A >> m;

    Sat2 cidade(S + A);

    for(int i = 0; i < m; i++) {
        cin >> s1 >> a1 >> s2 >> a2;

        if(!(s1 == s2 && a1 == a2)) {
            a1 += S;
            a2 += S;

            if(s1 == s2 && a1 < a2) { // verificar
                cidade.addImplicacao(s1, false, s2, true);
            } else if(s1 == s2 && a1 > a2) { // verificar
                cidade.addImplicacao(s1, true, s2, false);
            } else if(a1 == a2 && s1 < s2) { // verificar
                cidade.addImplicacao(a1, true, a2, false);
            } else if(a1 == a2 && s1 > s2) { // verificar
                cidade.addImplicacao(a1, false, a2, true);
            } else if(s1 < s2 && a1 < a2) {
                cidade.addImplicacao(s1, false, a1, true);
                cidade.addImplicacao(s1, false, s2, true);
                cidade.addImplicacao(s2, false, s1, true);
                cidade.addImplicacao(s2, false, a2, true);
                cidade.addImplicacao(a1, false, s1, true);
                cidade.addImplicacao(a1, false, a2, true);
                cidade.addImplicacao(a2, false, a1, true);
                cidade.addImplicacao(a2, false, s2, true);
            } else if(s1 < s2 && a1 > a2) {
                cidade.addImplicacao(s1, true, a1, true);
                cidade.addImplicacao(s1, true, s2, false);
                cidade.addImplicacao(s2, true, s1, false);
                cidade.addImplicacao(s2, true, a2, true);
                cidade.addImplicacao(a2, false, a1, true);
                cidade.addImplicacao(a2, false, s2, false);
                cidade.addImplicacao(a1, false, s1, false);
                cidade.addImplicacao(a1, false, a2, true);
            } else if(s1 > s2 && a1 < a2) {
                cidade.addImplicacao(s1, false, a1, false);
                cidade.addImplicacao(s1, false, s2, true);
                cidade.addImplicacao(s2, false, s1, true);
                cidade.addImplicacao(s2, false, a2, false);
                cidade.addImplicacao(a1, true, s1, true);
                cidade.addImplicacao(a1, true, a2, false);
                cidade.addImplicacao(a2, true, a1, false);
                cidade.addImplicacao(a2, true, s2, true);
            } else if(s1 > s2 && a1 > a2) {
                cidade.addImplicacao(s1, true, a1, false);
                cidade.addImplicacao(s1, true, s2, false);
                cidade.addImplicacao(s2, true, s1, false);
                cidade.addImplicacao(s2, true, a2, false);
                cidade.addImplicacao(a1, true, s1, false);
                cidade.addImplicacao(a1, true, a2, false);
                cidade.addImplicacao(a2, true, a1, false);
                cidade.addImplicacao(a2, true, s2, false);
            }
        }
    }

    if(cidade.satisfativel()) cout << "Yes\n";
    else cout << "No\n";
}
 
int main() {
    int T;

    cin >> T;

    for(int i = 0; i < T; i++) {
        solve();
    }
}