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



void dfsRecursivo(Graph &g,int verticeDescoberto[], const int v) {	
	verticeDescoberto[v] = true;
	visitaVertice(g,v);	

	Graph::adjIterator it(g,v);	
	for(int i=it.beg();!it.end();i=it.nxt()) {		
		if (!verticeDescoberto[i]) 
			dfsRecursivo(g,verticeDescoberto,i); //Visita o vertice adjacente a v que ainda não foi descoberto...	
	}
}


void dfsPilha(Graph &g, int verticeDescoberto[], const int v) {
	stack<int> pilha;
	pilha.push(v);
	verticeDescoberto[v] = true;	
	
	int vertice;
	while(!pilha.empty()) {
		vertice = pilha.top(); pilha.pop();		
		visitaVertice(g,vertice);

		Graph::adjIterator it(g,vertice);	
		for(int i=it.beg();!it.end();i=it.nxt()) {
			if (!verticeDescoberto[i]) {
				verticeDescoberto[i] = true;
				pilha.push(i);	
			}		
		}
	}
	
}

int main(int argc,char **argv) {
	assert(argc==2);

	Graph g(argv[1]);
	
	
	int *verticeDescoberto = new int[g.V()];
	for(int i=0;i<g.V();i++)
		verticeDescoberto[i] = false;
	

	int contador = 0;
	for(int i=0;i<g.V();i++) {
		if (!verticeDescoberto[i])
			contador++;
		dfsPilha(g, verticeDescoberto,i);
	}
	cout << "Numero de CC: " << contador << endl;
	
	delete []verticeDescoberto;
	return 0;
}
