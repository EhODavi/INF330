#include <iostream>
#include <algorithm>
#include <vector>
#include "sparseMultiGraph.h"

typedef SparseMultiGRAPH Graph;
using namespace std;

/*
"This code is based in "Algorithms in C++, Third Edition,"
                by Robert Sedgewick, Addison-Wesley, 2002."
*/



void geraGrafoCompleto(Graph &g, int n) {
	g = Graph(n,false);
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			g.insert(Edge(i,j));
}

void geraGrafoKmn(Graph &g, int m,int n) {
	g = Graph(n+m,false);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			g.insert(Edge(i,j+n));
}

//Gera um grafo aleatorio com v vertices e e arestas
//O grafo pode possuir arestas multiplas e loop (a funcao insert deve tratar isso)
void geraGrafoRandE(Graph &g, int v, int e,bool digrafo) { 
	g = Graph(v,digrafo);
	for(int i=0;i<e;i++) {
		int x = rand()%v;
		int y = rand()%v; 
		g.insert(Edge(x,y));
	}	
}

void geraGrafoRandG(Graph &g, int v, int e, bool digrafo) {
	g = Graph(v,digrafo);
	double p = 2.0*e/(v*(v-1));
	if (digrafo)
		p/=2;

	for(int i=0;i<v;i++) {
		for(int j=i+1;j<v;j++) {
			if (rand() <p*RAND_MAX)
				g.insert(Edge(i,j));
			if (digrafo && rand() <p*RAND_MAX)
				g.insert(Edge(j,i));
		}
	}	
}

void geraGrafoProbAresta(Graph &g, int v, double p, bool digrafo) {
	g = Graph(v,digrafo);
	for(int i=0;i<v;i++) {
		for(int j=0;j<v;j++) {
			if (rand() <p*RAND_MAX)
				g.insert(Edge(i,j));
		}
	}	
}

void geraGrafoBipartidoProbAresta(Graph &g, int m,int n, double p, bool digrafo) { 
	g = Graph(m+n,digrafo);
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			int u = i;
			int v = j+n;
			if (rand() <p*RAND_MAX) {
				g.insert(Edge(u,v));
			}
			if (digrafo && rand() <p*RAND_MAX) {
				g.insert(Edge(v,u));
			}
		}
	}	
}

void geraGrafoHamiltoniano(Graph &g,int v, double p) { 
	g = Graph(v,false);
	vector<int> vt;
	for(int i=0;i<v;i++)
		vt.push_back(i);	
	random_shuffle(vt.begin(), vt.end()) ;
	vt.push_back(vt[0]);
	for(int i=0;i<v;i++)
		g.insert(Edge(vt[i],vt[i+1]));
	

	for(int i=0;i<v;i++) {
		for(int j=0;j<v;j++) {
			if (rand() <p*RAND_MAX)
				g.insert(Edge(i,j));
		}
	}		
}

int main(int argc, char **argv) {
	Graph g(1,false);
	if (argc<=1) {
		cerr << "Erro, use: " << endl;
		cerr << "./geraGrafo NomeDoGrafo.dot Opcao Parametros" <<endl;
		cerr << " Opcoes                                 |     parametros: " <<endl;
		cerr << "1: grafo completo                       |      |V|" << endl;
		cerr << "2: grafo geraGrafoKmn                   |       m   n" << endl;
		cerr << "3: grafo geraGrafoRandE                 |      |V| |E| Digrafo(0 para nao e 1 para sim)" << endl;
		cerr << "4: grafo geraGrafoRandG                 |      |V| |E| Digrafo(0 para nao e 1 para sim)" << endl;
		cerr << "5: grafo geraGrafoProbAresta            |      |V|  p  Digrafo(0 para nao e 1 para sim)" << endl;
		cerr << "6: grafo geraGrafoBipartidoProbAresta   |       m   n  p   Digrafo(0 para nao e 1 para sim)" << endl;
		cerr << "7: grafo geraGrafoHamiltoniano          |      |V|  p " << endl;
	}
	int opcao = atoi(argv[2]);
	switch(opcao) {
		case 1:
			geraGrafoCompleto(g, atoi(argv[3]) );
			break;
		case 2:
			geraGrafoKmn(g,  atoi(argv[3]), atoi(argv[4]));
			break;
		case 3:
			geraGrafoRandE(g,  atoi(argv[3]), atoi(argv[4]), atoi(argv[5]) );
			break;
		case 4:
			geraGrafoRandG(g, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
			break;
		case 5:
			geraGrafoProbAresta(g, atoi(argv[3]), atof(argv[4]), atoi(argv[5]));
			break;
		case 6:
			geraGrafoBipartidoProbAresta(g,  atoi(argv[3]),atoi(argv[4]), atof(argv[5]), atoi(argv[6]) );
			break;
		case 7:
			geraGrafoHamiltoniano(g, atoi(argv[3]), atof(argv[4]));
			break;
		default:
			cerr << "Erro" <<endl;	
			exit(1); 
	}
	g.save(argv[1]);
}

