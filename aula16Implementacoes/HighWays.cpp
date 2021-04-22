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



inline double distancia(pair<int,int> p1, pair<int,int> p2) {
	return sqrt((p1.first-p2.first)*(p1.first-p2.first) + (p1.second-p2.second)*(p1.second-p2.second));
}

int main() {
	int nt;
	scanf("%d",&nt);
	bool primeiro = true;
	for(int i=0;i<nt;i++) {
		if (primeiro) 
			primeiro = false;
		else printf("\n");

		int conexoes;
		scanf("%d",&conexoes);
		
		vector<pair<int,int> > pontos;
		for(int i=0;i<conexoes;i++) {
			pair<int,int> p;
			scanf("%d %d",&p.first,&p.second);

			pontos.push_back(p);
		}
		
		vector<Edge> arestas;
		for(int i=0;i<conexoes;i++) 
			for(int j=0;j<conexoes;j++)
				if(i!=j)
					arestas.push_back( Edge(i,j, distancia(pontos[i],pontos[j])) );


		sort(arestas.begin(),arestas.end());

		UnionFind conjuntos;
		conjuntos.createSet(conexoes);
	
		int sz = arestas.size();
		int tamArvore = conexoes-1;

		int ctArestas  = 0;
		
		int arestasJaNoGrafo;
		scanf("%d",&arestasJaNoGrafo);
		for(int i=0;i<arestasJaNoGrafo;i++) {
			pair<int,int> p;
			scanf("%d %d",&p.first,&p.second); 
			p.first--; p.second--;
			ctArestas++;
			conjuntos.mergeSets(p.first,p.second);
		}
		double custo = 0;
		bool entrou = false;
		for(int i=0;i<sz;i++) {
			if ( !conjuntos.isSameSet( arestas[i].v, arestas[i].w ) ) {
				ctArestas++;				
				custo+= arestas[i].peso;
				
				conjuntos.mergeSets(arestas[i].v, arestas[i].w );
				printf("%d %d\n",arestas[i].v+1,arestas[i].w+1);

				entrou = true;
			}
		}
		if (!entrou) {
			printf("No new highways need\n");
		} 
		


	}

}



