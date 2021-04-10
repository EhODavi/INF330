#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include "denseGraphs.h"
using namespace std;

typedef DenseGRAPH Graph;


/*
Verifica se o digrafo é simetrico,ou seja,
se para cada arco (u,v) existe um arco (v,u) 
*/
bool ehSimetrico(Graph &g) {
	for(int i=0;i<g.V();i++)
		for(int j=i;j<g.V();j++) {
			if (g.edge(i,j) != g.edge(j,i))
				return false;
		}
	return true;
}


/*
Calcula o grau de entrada de um vertice v
*/
int grauEntrada(Graph &g,int v) {
	if (!g.directed()) {
		cerr << "Erro ao calcular grau de entrada: o grafo não é direcionado!" <<endl;
		exit(1);
	}

	int gr= 0;
	Graph::adjIterator it(g,v);
	
	for(int i=0;i<g.V();i++)
		if (g.edge(i,v))
			gr++;
	return gr;
}


/*
Calcula o grau de saida de um vertice v
*/
int grauSaida(Graph &g,int v) {
	if (!g.directed()) {
		cerr << "Erro ao calcular grau de saida: o grafo não é direcionado!" <<endl;
		exit(1);
	}


	Graph::adjIterator it(g,v);
	
	for(int i=it.beg();!it.end();i=it.nxt())
		gr++;
	return gr;
}

/*
Calcula o grau de um vertice v
*/
int grau(Graph &g,int v) {
	if (g.directed())
		return grauEntrada(g,v) + grauSaida(g,v);

	int gr= 0;
	Graph::adjIterator it(g,v);
	
	for(int i=it.beg();!it.end();i=it.nxt())
		gr++;
	return gr;
}




int main(int argc, char **argv) {
	assert(argc==2);
	Graph g(argv[1]);
		
	if (ehSimetrico(g))
		cout << "O grafo eh simetrico" <<endl;
	else cout << "O grafo nao eh simetrico " << endl;

	for(int i=0;i<g.V();i++) {
		if (g.directed()) {
			cout << "Grau de entrada do vertice " << i+1 << " eh: " << grauEntrada(g,i) <<endl;
			cout << "Grau de saida do vertice   " << i+1 << " eh: " << grauSaida(g,i) <<endl << endl;
		} else {
			cout << "Grau do vertice " << i+1 << " eh " << grau(g,i) <<endl;
		}	
		
	}	
		
	return 0;	
}

