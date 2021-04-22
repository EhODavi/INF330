#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <sstream>
#include <queue>
#include <cstdlib>
using namespace std;

typedef int tipoPeso;

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
int kruskal(vector<Edge> &arestas, vector<bool> &arestasUtilizadas,int numVerticesGrafo) {
	arestasUtilizadas = vector<bool>(arestas.size(),false);
	sort(arestas.begin(),arestas.end());

	UnionFind conjuntos;
	conjuntos.createSet(numVerticesGrafo);
	
	int sz = arestas.size();
	int tamArvore = numVerticesGrafo-1;
	int ctArestas = 0;
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


int main() {
	int nt;
	scanf("%d",&nt);
	for(int i=0;i<nt;i++) {
		int nescolas, conexoes;
		scanf("%d %d",&nescolas,&conexoes);
		vector<Edge > arestas;
		Edge e;
		for(int i=0;i<conexoes;i++) {
			scanf("%d %d %d",&e.v,&e.w,&e.peso);
			e.v--; e.w--;
			arestas.push_back(e);
		}

		vector<bool> arestasUtilizadas;
		kruskal(arestas, arestasUtilizadas,nescolas);

		int custoMinimo = 0;

		vector<int> listaIdsArestasUtilizadas;
		for(int i=0;i<arestas.size();i++) {
			if (arestasUtilizadas[i]) {
				listaIdsArestasUtilizadas.push_back(i);
				custoMinimo += arestas[i].peso;
			}
		}


		#define INF 999999999
		int segundoCustoMinimo = INF;
		//Para cada aresta que estiver na AGM...
		for(int i=0;i<listaIdsArestasUtilizadas.size();i++) {
				int idArestaRemover = listaIdsArestasUtilizadas[i];
				Edge arestaARemover = arestas[idArestaRemover];
				UnionFind uf;
				uf.createSet(nescolas);
				int pesoSemArestaRemovida = 0 ; //Peso da floresta (ou seja, da AGM sem a aresta "arestasARemover";
				//Ao remover a aresta "arestaARemover", teremos uma floresta com duas arvores...
				//Vamos representar cada floresta pelo UnionFind uf
				for(int j=0;j<listaIdsArestasUtilizadas.size();j++) 
					if (j!=i) {
						Edge aresta= arestas[listaIdsArestasUtilizadas[j]];
						pesoSemArestaRemovida += aresta.peso;
						uf.mergeSets(aresta.v,aresta.w);
					}

				int pesoMinimo = INF;
				//Agora precisamos pegar a aresta de custo minimo (com id != istaIdsArestasUtilizadas[i]) que liga as duas arvores...
				for(int j=0;j<arestas.size();j++) {
					if (j!=idArestaRemover) {
						Edge aresta= arestas[j];
						if (!uf.isSameSet(aresta.v,aresta.w)) {
							pesoMinimo = aresta.peso;
							break;
						}
					}
				}
				
				int pesoArvore = pesoMinimo + pesoSemArestaRemovida;
				segundoCustoMinimo = min(segundoCustoMinimo,pesoArvore);

		}
		
		
		

		printf("%d %d\n",custoMinimo,segundoCustoMinimo);
		


	}

}



