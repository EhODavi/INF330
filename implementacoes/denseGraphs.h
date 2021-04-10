#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
using namespace std;

/*
"This code is from "Algorithms in C++, Third Edition,"
                by Robert Sedgewick, Addison-Wesley, 2002."
*/

#ifndef DENSE_GRAPHS_H
#define DENSE_GRAPHS_H

struct Edge 
{ int v, w;
    Edge(int v = -1, int w = -1) : v(v), w(w) { }
};

class DenseGRAPH
{ 
  int Vcnt, Ecnt; bool digraph;
  vector <vector <bool> > adj;
public:
  DenseGRAPH(int V, bool digraph);
  DenseGRAPH(const string &file);
  int V() const;
  int E() const;
  bool directed() const;
  void insert(Edge e);
  void remove(Edge e);
  bool edge(int v, int w) const; 
  void save(const string &file) const;

  class adjIterator;
  friend class adjIterator;  
};

class DenseGRAPH::adjIterator
{ 
  const DenseGRAPH &G;
  int i, v;
public:
  adjIterator(const DenseGRAPH &G, int v) ;
  int beg();
  int nxt();
  bool end();
};


#endif
