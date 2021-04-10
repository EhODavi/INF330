#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stack>
#include <cassert>
#include "sparseMultiGraph.h"
using namespace std;

typedef SparseMultiGRAPH Graph;

void visitaVertice(Graph &g,const int v) {

}

void visitaAresta(int u,int v,int pai[]) {
	if (pai[u]!=v) {
		cout << "O grafo possui um ciclo que passa pela aresta: (" << u+1 << " , " << v+1 << ")" <<endl;
		exit(0);
	}
}



void dfsRecursivo(Graph &g,int verticeDescoberto[],int verticeProcessado[], int pai[], const int v) {	
	verticeDescoberto[v] = true;
	visitaVertice(g,v);	

	Graph::adjIterator it(g,v);	
	for(int i=it.beg();!it.end();i=it.nxt()) {		
		if (!verticeDescoberto[i]) {
			pai[i]=v;
			dfsRecursivo(g,verticeDescoberto,verticeProcessado,i); //Visita o vertice adjacente a v que ainda não foi descoberto...	
		} else if (!verticeProcessado[i]) //Se o vertice i ja foi descoberto mas nao foi completamente processado, entao visitamos a aresta (v,i)
			visitaAresta(v,i,pai);
	}


	verticeProcessado[v] = true;
}


void encontraCiclo(Graph &g) {
	int *verticeDescoberto = new int[g.V()];
	int *verticeProcessado = new int[g.V()];
	int *pai = new int[g.V()];
	
	for(int i=0;i<g.V();i++) {
		verticeProcessado[i] = verticeDescoberto[i] = false;
		pai[i] = -1;
	}

	for(int i=0;i<g.V();i++) {
		if (!verticeProcessado[i])
			dfsRecursivo(g,  verticeDescoberto, verticeProcessado, pai,  i);
	}

	delete []pai;
	delete []verticeProcessado;
	delete []verticeDescoberto;
}

int main(int argc,char **argv) {
	assert(argc==3);
	cerr << argv[1] <<endl;
	int v0 = atoi(argv[2])-1;
	Graph g(argv[1]);
	encontraCiclo(g);	

	return 0;
}
