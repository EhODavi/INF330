#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stack>
#include <cassert>
#include "sparseMultiGraph.h"
using namespace std;

typedef SparseMultiGRAPH Graph;

void visitaVertice(Graph &g,const int v) {
	cout << "Visitando vertice: "<< v+1 << endl;
}

void visitaAresta(int u,int v) {
	cout << "Visitando aresta: ( " << u+1<< " , " << v+1 << " ) " << endl;
}

void dfsRecursivo(Graph &g,int verticeDescoberto[],int verticeProcessado[], const int v) {	
	verticeDescoberto[v] = true;
	visitaVertice(g,v);	

	Graph::adjIterator it(g,v);	
	for(int i=it.beg();!it.end();i=it.nxt()) {		
		if (!verticeDescoberto[i]) {
			dfsRecursivo(g,verticeDescoberto,verticeProcessado,i); //Visita o vertice adjacente a v que ainda não foi descoberto...	
		} else if (!verticeProcessado[i]) //Se o vertice i ja foi descoberto mas nao foi completamente processado, entao visitamos a aresta (v,i)
			visitaAresta(v,i);
	}


	verticeProcessado[v] = true;
}



int main(int argc,char **argv) {
	assert(argc==3);
	cerr << argv[1] <<endl;
	int v0 = atoi(argv[2])-1;
	Graph g(argv[1]);
	
	
	int *verticeDescoberto = new int[g.V()];
	int *verticeProcessado = new int[g.V()];
	for(int i=0;i<g.V();i++)
		verticeProcessado[i] = verticeDescoberto[i] = false;
	
	cout << "DFS recursivo " << endl;
	dfsRecursivo(g, verticeDescoberto,verticeProcessado, v0);
	

	
	delete []verticeProcessado;
	delete []verticeDescoberto;
	return 0;
}
