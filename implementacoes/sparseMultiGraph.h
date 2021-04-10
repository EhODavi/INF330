#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <cstdlib>
using namespace std;

/*
"This code is from "Algorithms in C++, Third Edition,"
                by Robert Sedgewick, Addison-Wesley, 2002."
*/

#ifndef SPARSE_GRAPHS_H
#define SPARSE_GRAPHS_H

struct Edge 
{ int v, w;
    Edge(int v = -1, int w = -1) : v(v), w(w) { }
};

class SparseMultiGRAPH
{ 
  int Vcnt, Ecnt; bool digraph;
  vector <list <int> > adj;
public:
  SparseMultiGRAPH(int V, bool digraph);
  SparseMultiGRAPH(const string &file);
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

class SparseMultiGRAPH::adjIterator
{ 
  const SparseMultiGRAPH &G;
  list<int>::const_iterator it;
  int v;
public:
  adjIterator(const SparseMultiGRAPH &G, int v) ;
  int beg();
  int nxt();
  bool end();
};


#endif
