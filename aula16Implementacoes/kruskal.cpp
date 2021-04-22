#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <queue>
#include <cstdlib>
using namespace std;

typedef double tipoPeso;

class UnionFind {
	private:
		vector<int> representante;
	public:
		void createSet(int tam) {
			representante.resize(tam);
			for(int i=0;i<tam;i++)
				representante[i] = i;
		}
		//Retorna o representante do conjunto que contem
		//o elemento "elemento"
		int findSet(int elemento) {
			if (representante[elemento]==elemento) 
				return elemento;
			//Compressao do caminho...
			representante[elemento] = findSet(representante[elemento]);
			return representante[elemento];
		}
		void mergeSets(int i,int j) {
			representante[ findSet(i) ] = findSet(j);
		}
		bool isSameSet(int i,int j) {
			return (findSet(i)==findSet(j));
		}

};



struct Edge 
{
	int v, w;
	tipoPeso peso;
	Edge(int v = -1, int w = -1,tipoPeso peso = 0) : v(v), w(w), peso(peso) { }
};

bool operator <(const Edge &i,const Edge &j) {
	return i.peso<j.peso;
}

//Tenta criar uma AGM utilizando o algoritmo de Kruskal
//Marca em "arestasUtilizadas" as arestas que foram utilizadas na AGM
//Retorna o número de arestas utilizadas (se < numVerticesGrafo-1 --> o grafo era desconexo e nao possui AGM!)
//Os vértices devem ser identificados por números entre 0 e numVerticesGrafo-1
//Obs: o vetor de arestas sera reordenado!
int Kruskal(vector<Edge> &arestas, vector<bool> &arestasUtilizadas,int numVerticesGrafo) {
	arestasUtilizadas = vector<bool>(arestas.size(),false);
	sort(arestas.begin(),arestas.end());

	UnionFind conjuntos;
	conjuntos.createSet(numVerticesGrafo);
	
	int sz = arestas.size();
	int tamArvore = numVerticesGrafo-1;
	int ctArestas =0;
	for(int i=0;i<sz;i++) {
		if ( !conjuntos.isSameSet( arestas[i].v, arestas[i].w ) ) {
			arestasUtilizadas[i] = true;
			ctArestas++;

			if (ctArestas==tamArvore)
				return ctArestas;

			conjuntos.mergeSets(arestas[i].v, arestas[i].w );
		}
	}
	return ctArestas;
}



