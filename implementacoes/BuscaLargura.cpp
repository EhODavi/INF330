#include <iostream>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <stack>
#include <cassert>
#include "sparseMultiGraph.h"
using namespace std;

typedef SparseMultiGRAPH Graph;

void visitaVertice(Graph &g,const int v,int ordem[]) {
	cout << "Visitando vertice: "<< v+1 << " . Ordem: " << ordem[v] <<  endl;
}




void bfsFila(Graph &g, bool verticeDescoberto[], int ordem[],const int v) {
	queue<int> fila;
	fila.push(v);
	verticeDescoberto[v] = true;	
	ordem[v]=0;
	
	int vertice;
	while(!fila.empty()) {
		vertice = fila.front(); fila.pop();		
		visitaVertice(g,vertice,ordem);

		Graph::adjIterator it(g,vertice);	
		for(int i=it.beg();!it.end();i=it.nxt()) {
			if (!verticeDescoberto[i]) {
				verticeDescoberto[i] = true;
				ordem[i] = ordem[vertice]+1;
				fila.push(i);	
			}		
		}
	}
	
}

int main(int argc,char **argv) {
	assert(argc==3);
	cerr << argv[1] <<endl;
	int v0 = atoi(argv[2])-1;
	Graph g(argv[1]);
	bool *verticeDescoberto = new bool[g.V()];
	int *ordem =  new int[g.V()];

	for(int i=0;i<g.V();i++)
		verticeDescoberto[i]= false;
		
	bfsFila(g,verticeDescoberto, ordem, v0);
 
	
	delete []ordem;
	delete []verticeDescoberto;
	return 0;
}
