#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <map>



using namespace std;


/*
dip
lip
mad
map
maple
may
pad
pip
pod
pop
sap
sip
slice
slick
spice
stick
stock
*
spice stock
may pod
*/
bool isAdj(const string &a,const string &b) {
	if(a.size()!=b.size()) return false;
	int ctDiff = 0;
	for(int i=0;i<a.size();i++) if(a[i]!=b[i]) ctDiff++;
	return ctDiff == 1;
}

void bfsFila(const vector<vector<int> > &adj, vector<bool> &verticeDescoberto, vector<int> &ordem,const int v) {
	queue<int> fila;
	fila.push(v);
	verticeDescoberto[v] = true;	
	ordem[v]=0;
	
	int vertice;
	while(!fila.empty()) {
		vertice = fila.front(); fila.pop();		
		//visitaVertice(g,vertice,ordem);

		for(int v:adj[vertice]) {
			if (!verticeDescoberto[v]) {
				verticeDescoberto[v] = true;
				ordem[v] = ordem[vertice]+1;
				fila.push(v);	
			}		
		}
	}	
}

int main() {
	int nt;
	cin >> nt;

	bool primeira = true;
	while(nt--) {
		string st;
		vector<string> words;
		map<string,int> wordId;
		while(true) {
			cin >> st;
			if(st[0]=='*') break;
			words.push_back(st);
			int id  = wordId.size();
			wordId[st] = id;
		}

		int nv = wordId.size();
		vector<vector<int> > adj(nv);
		for(int i=0;i<nv;i++) {
			for(int j=0;j<nv;j++) {
				if(isAdj(words[i],words[j])) {
					adj[i].push_back(j);
					adj[j].push_back(i);
				}
			}
		}

		cin.ignore();
		//ATENCAO: e' possivel deixar esse codigo mais eficiente! 
		string a,b;

		while(true) {
			string st;
			getline(cin,st);
			if(st.size()==0) break;
			stringstream ss;
			ss << st;
			ss >> a >> b;

			vector<bool> verticeDescoberto(nv,false);
			vector<int> ordem(nv,0);
			int idA = wordId[a];
			int idB = wordId[b];
			bfsFila(adj, verticeDescoberto, ordem,idA);

			if(!primeira) cout << "\n";
			primeira = false;
			cout << a << " " << b << " " << ordem[idB];
		}
	}
}
