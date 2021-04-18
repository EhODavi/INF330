
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <queue>
#include <cstdlib>
using namespace std;

struct Edge 
{ int v, w;
    Edge(int v = -1, int w = -1) : v(v), w(w) { }
};

class SparseMultiGRAPH
{ 
  int Vcnt, Ecnt; bool digraph;
  vector <list <int> > adj;
public:
  SparseMultiGRAPH(int V, bool digraph);
  int V() const;
  int E() const;
  bool directed() const;
  void insert(Edge e);
  void remove(Edge e);
  bool edge(int v, int w) const; 
  void apagaArestasCom(int v);

  class adjIterator;
  friend class adjIterator;  
};

class SparseMultiGRAPH::adjIterator
{ 
  const SparseMultiGRAPH &G;
  list<int>::const_iterator it;
  int v;
public:
  adjIterator(const SparseMultiGRAPH &G, int v) ;
  int beg();
  int nxt();
  bool end();
};

SparseMultiGRAPH::SparseMultiGRAPH(int V, bool digraph = false) :
    adj(V), Vcnt(V), Ecnt(0), digraph(digraph) 
    { adj.resize(V); }


int SparseMultiGRAPH::V() const { return Vcnt; }

int SparseMultiGRAPH::E() const { return Ecnt; }

bool SparseMultiGRAPH::directed() const { return digraph; }

void SparseMultiGRAPH::insert(Edge e)
{    
      int v = e.v, w = e.w;
      adj[v].push_back(w);
      if (!digraph) adj[w].push_back(v);
      Ecnt++;
} 

void SparseMultiGRAPH::remove(Edge e) {
      int v = e.v, w = e.w;

      for(list<int>::iterator it= adj[v].begin();it!=adj[v].end();it++) 
		if (*it == w) {
			adj[v].erase(it);
			Ecnt--;
			break;
		}      

      if (!digraph) {
      		for(list<int>::iterator it= adj[w].begin();it!=adj[w].end();it++) {
			if (*it == v) { 
				adj[w].erase(it);
				break;
			}    
		}
      }      
      
}

bool SparseMultiGRAPH::edge(int v1, int w1) const {
	adjIterator it(*this,v1);
	for(int w=it.beg();!it.end();w = it.nxt())
		if (w==w1) return true;
	return false;
}

SparseMultiGRAPH::adjIterator::adjIterator(const SparseMultiGRAPH &G, int v): 
   G(G),v(v) { 
	it = G.adj[v].begin(); 
}

int SparseMultiGRAPH::adjIterator::beg() { 
	it = G.adj[v].begin(); 
	return (it!=G.adj[v].end())?(*it):-1; 
}

int SparseMultiGRAPH::adjIterator::nxt() { 
	it++;
	return (it!=G.adj[v].end())?(*it):-1; 
}

bool SparseMultiGRAPH::adjIterator::end() { 
	return it == G.adj[v].end(); 
}

void SparseMultiGRAPH::apagaArestasCom(int v) {
	for(int i=0;i<Vcnt;i++) {
		adj[i].remove(v);
	}
	adj[v].clear();
}







/******


******/

typedef SparseMultiGRAPH Graph;



int main() {
	int nv;
	while(true) {
		int v,e;
		scanf("%d %d",&v,&e);
		if (v+e==0) return 0;
		Graph g(v,true);
		vector<int> grauEntrada(v,0);

		for(int i=0;i<e;i++) {
			int x,y;
			scanf("%d %d",&x,&y);
			g.insert(Edge(x-1,y-1));
			grauEntrada[y-1]++;
		}	
		queue<int> grausZero;
		for(int i=0;i<v;i++) {
			if(grauEntrada[i]==0) {
				grausZero.push(i);
			}
		}
		while(!grausZero.empty()) {
			int x = grausZero.front(); grausZero.pop();
			printf("%d ",x+1);
			
			SparseMultiGRAPH::adjIterator it(g,x);
			for(int v=it.beg();!it.end();v=it.nxt()) {
				grauEntrada[v]--;
				if(grauEntrada[v]==0) grausZero.push(v);
			}

		}
		printf("\n");
			
	}

}
