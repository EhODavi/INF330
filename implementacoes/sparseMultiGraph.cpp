#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "sparseMultiGraph.h"
using namespace std;

/*
"This code is from "Algorithms in C++, Third Edition,"
                by Robert Sedgewick, Addison-Wesley, 2002."
*/




SparseMultiGRAPH::SparseMultiGRAPH(int V, bool digraph = false) :
    adj(V), Vcnt(V), Ecnt(0), digraph(digraph) 
    { adj.resize(V); }


int SparseMultiGRAPH::V() const { return Vcnt; }

int SparseMultiGRAPH::E() const { return Ecnt; }

bool SparseMultiGRAPH::directed() const { return digraph; }

void SparseMultiGRAPH::insert(Edge e)
{    
      int v = e.v, w = e.w;
      adj[v].push_back(w);
      if (!digraph) adj[w].push_back(v);
      Ecnt++;
} 

void SparseMultiGRAPH::remove(Edge e) {
      int v = e.v, w = e.w;

      for(list<int>::iterator it= adj[v].begin();it!=adj[v].end();it++) 
		if (*it == w) {
			adj[v].erase(it);
			Ecnt--;
			break;
		}      

      if (!digraph) {
      		for(list<int>::iterator it= adj[w].begin();it!=adj[w].end();it++) {
			if (*it == v) { 
				adj[w].erase(it);
				break;
			}    
		}
      }      
      
}

bool SparseMultiGRAPH::edge(int v1, int w1) const {
	adjIterator it(*this,v1);
	for(int w=it.beg();!it.end();w = it.nxt())
		if (w==w1) return true;
	return false;
}







void SparseMultiGRAPH::save(const string &file) const {
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


SparseMultiGRAPH::SparseMultiGRAPH(const string &file) {
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

	
	for(int i=0;i<vt.size();i++) { 
		insert(Edge(vt[i].first-1,vt[i].second-1));	
	}
	cerr << "Grafo carregado com " << V() << " vertices " << " e " << E() << " arestas " <<endl;
	fin.close();

}


SparseMultiGRAPH::adjIterator::adjIterator(const SparseMultiGRAPH &G, int v): 
   G(G),v(v) { 
	it = G.adj[v].begin(); 
}

int SparseMultiGRAPH::adjIterator::beg() { 
	it = G.adj[v].begin(); 
	return (it!=G.adj[v].end())?(*it):-1; 
}

int SparseMultiGRAPH::adjIterator::nxt() { 
	it++;
	return (it!=G.adj[v].end())?(*it):-1; 
}

bool SparseMultiGRAPH::adjIterator::end() { 
	return it == G.adj[v].end(); 
}


