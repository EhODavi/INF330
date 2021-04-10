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

void visitaAresta(int u,int v,int verticeDescoberto[],int verticeProcessado[]) {

}




void dfsRecursivo(Graph &g,int verticeDescoberto[],int verticeProcessado[], const int v) {	
	verticeDescoberto[v] = true;
	visitaVertice(g,v);	

	Graph::adjIterator it(g,v);	
	for(int i=it.beg();!it.end();i=it.nxt()) {		
		if (!verticeDescoberto[i]) {
			dfsRecursivo(g,verticeDescoberto,verticeProcessado,i); //Visita o vertice adjacente a v que ainda não foi descoberto...	
		} else if (!verticeProcessado[i]) //Se o vertice i ja foi descoberto mas nao foi completamente processado, entao visitamos a aresta (v,i)
			visitaAresta(v,i,verticeDescoberto,verticeProcessado);
	}


	verticeProcessado[v] = true;
}


void encontraCiclo(Graph &g) {
	int *verticeDescoberto = new int[g.V()];
	int *verticeProcessado = new int[g.V()];

	
	for(int u=0;u<g.V();u++) {
		Graph::adjIterator it(g,u);	
		for(int v=it.beg();!it.end();v=it.nxt()) {
			Graph g2(g.V(),false);
			for(int i=0;i<g.V();i++)
				verticeProcessado[i] = verticeDescoberto[i] = false;

			g2 = g;

			g2.remove(Edge(u,v));


			dfsRecursivo(g2, verticeDescoberto,verticeProcessado, v);
			if (verticeDescoberto[u]) {
				cout << "O grafo possui um ciclo que passa na aresta: ( " << u+1 <<  " , " << v+1 << " ) " << endl;
				return;
			}
		}

	}
	cout << "O grafo não possui ciclo" <<endl;
	delete []verticeDescoberto;
	delete []verticeProcessado;
}

int main(int argc,char **argv) {
	assert(argc==3);
	cerr << argv[1] <<endl;
	int v0 = atoi(argv[2])-1;
	Graph g(argv[1]);
	encontraCiclo(g);	

	return 0;
}
