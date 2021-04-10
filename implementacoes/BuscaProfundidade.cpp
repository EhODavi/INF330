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

void dfsRecursivo(Graph &g,int verticeDescoberto[], const int v) {	
	verticeDescoberto[v] = true;
	visitaVertice(g,v);	

	Graph::adjIterator it(g,v);	
	for(int i=it.beg();!it.end();i=it.nxt()) {		
		if (!verticeDescoberto[i]) 
			dfsRecursivo(g,verticeDescoberto,i); //Visita o vertice adjacente a v que ainda não foi descoberto...	
	}
}


void dfsPilha(Graph &g, int verticeProcessado[], const int v) {
	stack<int> pilha;
	pilha.push(v);
	
	int vertice;
	while(!pilha.empty()) {
		vertice = pilha.top(); pilha.pop();
		if (verticeProcessado[vertice]) 
			continue;
		
		verticeProcessado[vertice] = true;	
		visitaVertice(g,vertice);

		Graph::adjIterator it(g,vertice);	
		for(int i=it.beg();!it.end();i=it.nxt()) {
			if (!verticeProcessado[i]) {				
				pilha.push(i);	
			}		
		}
	}
	
}

int main(int argc,char **argv) {
	assert(argc==3);
	cerr << argv[1] <<endl;
	int v0 = atoi(argv[2])-1;
	Graph g(argv[1]);
	
	
	int *verticeDescoberto = new int[g.V()];
	for(int i=0;i<g.V();i++)
		verticeDescoberto[i] = false;
	
	cout << "DFS recursivo " << endl;
	dfsRecursivo(g, verticeDescoberto, v0);
	

	for(int i=0;i<g.V();i++)
		 verticeDescoberto[i] = false;
	cout << "DFS utilizando pilha..." << endl << endl;
	dfsPilha(g, verticeDescoberto,v0);
	
	delete []verticeDescoberto;
	return 0;
}
