#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "denseGraphs.h"
using namespace std;

/*
"This code is from "Algorithms in C++, Third Edition,"
                by Robert Sedgewick, Addison-Wesley, 2002."
*/

DenseGRAPH::DenseGRAPH(int V, bool digraph = false) :
    adj(V), Vcnt(V), Ecnt(0), digraph(digraph)
    { 
      for (int i = 0; i < V; i++) 
        adj[i].assign(V, false);
    }

int DenseGRAPH::V() const { return Vcnt; }
int DenseGRAPH::E() const { return Ecnt; }
bool DenseGRAPH::directed() const { return digraph; }

void DenseGRAPH::insert(Edge e) { 
      int v = e.v, w = e.w;
      if (adj[v][w] == false) Ecnt++;
      adj[v][w] = true;
      if (!digraph) adj[w][v] = true; 
} 

void DenseGRAPH::remove(Edge e){ 
      int v = e.v, w = e.w;
      if (adj[v][w] == true) Ecnt--;
      adj[v][w] = false;
      if (!digraph) adj[w][v] = false; 
} 

bool DenseGRAPH::edge(int v, int w) const {    
      return adj[v][w]; 
}



void DenseGRAPH::save(const string &file) const {
	ofstream f(file.c_str(),ios::out);	
	
	if (directed()) {	
		f << "digraph G{ " << '\n';	
		for(int i=0;i<V();i++) 
			f << i+1 << ";" << '\n';
		for(int i=0;i<V();i++) {
			adjIterator it(*this,i);
			for(int w=it.beg();!it.end();w = it.nxt())
				f << i+1 << " -> "<< w+1 << ";\n";
		}
	} else {
		f << "graph G{ " << '\n';	
		for(int i=0;i<V();i++) 
			f << i+1 << ";" << '\n';
		for(int i=0;i<V();i++) {
			adjIterator it(*this,i);
			for(int w=it.beg();!it.end();w = it.nxt())
				if (i<w)
					f << i+1 << " -- "<< w+1 << ";\n";
		}
	}
	f << "}" <<endl;
	f.close();
}


DenseGRAPH::DenseGRAPH(const string &file) {
	ifstream fin(file.c_str(),ios::in);
	
	string str;
	fin >> str;
	
	if (str!="digraph" && str!="graph") {
		cerr << "Erro ao abrir arquivo dot! formato de arquivo invalido"<< endl;
		exit(0);
	}
	digraph = (str=="digraph");

	char c=' ';
	while(c!='{') {
		fin >> c;
		if (fin.eof()) {
			cerr << "Erro ao abir arquivo dot! eof alcançado";
			exit(0);
		} 
	}
	
	string linha;
	vector<pair<int,int> > vt;
	Vcnt = 0;
	Ecnt =0;

	while(c!='\n') fin.get(c);
	while(true) {
		getline(fin,linha); 
		stringstream st(linha);

		if (linha.find("}")!=string::npos) //Se estivermos no final do grafo..
			break;
		int a,b;
		if (linha.find("--")==string::npos && linha.find("->")==string::npos) {
			st >> a;
			Vcnt = max(Vcnt,a);
			continue;
		}
		st >> a >> str >> b;
		Vcnt = max(max(Vcnt,a),b);
		vt.push_back(pair<int,int>(a,b));	

	} 
	adj.resize(Vcnt);
  for (int i = 0; i < Vcnt; i++) 
    adj[i].assign(Vcnt, false);

	
	for(int i=0;i<vt.size();i++) { 
		insert(Edge(vt[i].first-1,vt[i].second-1));	
	}
	cerr << "Grafo carregado com " << V() << " vertices " << " e " << E() << " arestas " <<endl;
	fin.close();
}


DenseGRAPH::adjIterator::adjIterator(const DenseGRAPH &G, int v) : 
    G(G), v(v), i(-1) { }

int DenseGRAPH::adjIterator::beg() { i = -1; 
	return nxt(); 
}
int DenseGRAPH::adjIterator::nxt() {
  for (i++; i < G.V(); i++)
    if (G.adj[v][i] == true) return i;
  return -1;
}
bool DenseGRAPH::adjIterator::end(){ 
	return i >= G.V(); 
}




