#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <sstream>
#include <set>
#include <queue>
#include <cstdlib>
using namespace std;

typedef int tipoPeso;

struct Edge 
{
	int v, w;
	tipoPeso peso;
	Edge(int v = -1, int w = -1) : v(v), w(w), peso(peso) { }
};

bool operator <(const Edge &i,const Edge &j) {
	return i.peso<j.peso;
}


class SparseMultiGRAPH
{ 
  int Vcnt, Ecnt; bool digraph;
  vector <list <int> > adj;
public:
  SparseMultiGRAPH(int V, bool digraph);
  SparseMultiGRAPH(string file);
  int V() const;
  int E() const;
  bool directed() const;
  void insert(Edge e);
  void remove(Edge e);
  bool edge(int v, int w) const; 
  void save(string file);

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


/**************************************************************************
***************************************************************************/

typedef SparseMultiGRAPH Graph;



int maze[1000][1000];
int custo[1000*1000];
int l,c;

#define id(i,j) ((i)*c+j)
#define idToY(i) ((i)/c)
#define idToX(i) ((i)%c)


int main() {
	int nt;
	scanf("%d",&nt);	
	for(int i=0;i<nt;i++) {
		scanf("%d %d",&l,&c);
		Graph g(l*c);
		for(int i=0;i<l;i++) {
			for(int j=0;j<c;j++) {
				scanf("%d",&(maze[i][j]));			
			} 
		}

		
		/***** Criacao do Grafo ******/
		for(int i=0;i<l;i++)
			for(int j=0;j<c;j++) { 
				if (i>0)
					g.insert(Edge(id(i,j),id(i-1,j)));
				if (j>0)
					g.insert(Edge(id(i,j),id(i,j-1))); 

				if (i<l-1)
					g.insert(Edge(id(i,j),id(i+1,j)));
				if (j<c-1)
					g.insert(Edge(id(i,j),id(i,j+1)));
			}

		/**** Algoritmo de Dijkstra ****/
		#define INF 987654321
		//Como a priority_queue  do C++ nao oferece uma função "diminui_prioridade"
		//vamos utilizar um set para simulá-la 
		//(isso será bastante eficiente.. O(log(n)) por chamada)
		set<pair<int,int> > heap; 
		int s = id(0,0);
		int d = id(l-1,c-1);	
		for(int i=0;i<=d;i++)
			custo[i] = INF;
		custo[s] = maze[0][0];
		
		//O primeiro elemento de cada par é o seu custo
		//e o segundo elemento é o id do nodo...
		heap.insert(pair<int,int>(custo[0],s));
		//Queremos achar o caminho mínimo de s até t
		while(!heap.empty()) {
			//Remove o topo do "heap"
			int v= heap.begin()->second;
			int peso = heap.begin()->first;
			heap.erase(heap.begin());
			
			SparseMultiGRAPH::adjIterator it(g,v);


			//Note que ao olhar os vizinhos nao checamos se estamos "voltando" ao vertice de onde vimos... por que?			
			//Para cada w adjacente a v...
			for(int w=it.beg();!it.end();w = it.nxt()) {
				if (custo[v] + maze[idToY(w)][idToX(w)] < custo[w]) {
					//Apaga vertice se ele ja existe no heap com outro peso...
					if (custo[w]!=INF)
						heap.erase(heap.find(pair<int,int>(custo[w],w) ));					
					custo[w] = custo[v] + maze[idToY(w)][idToX(w)]; 
					//Insere vertice com novo custo
					heap.insert(pair<int,int>(custo[w],w));
				}
			}
			
		}			
		
		/****   ****/

		printf("%d\n",custo[d]);
		
	}

}



