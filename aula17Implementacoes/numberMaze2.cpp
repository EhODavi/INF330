#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <sstream>
#include <set>
#include <queue>
#include <cstdlib>
using namespace std;



#define id(i,j) ((i)*c+j)
#define idToY(i) ((i)/c)
#define idToX(i) ((i)%c)

int maze[1000][1000];
int custo[1000][1000];
int l,c;




int main() {
	int nt;
	scanf("%d",&nt);	
	for(int i=0;i<nt;i++) {
		scanf("%d %d",&l,&c);

		for(int i=0;i<l;i++) {
			for(int j=0;j<c;j++) {
				scanf("%d ",&(maze[i][j]));			
			} 
		}

		

		/**** Algoritmo de Dijkstra ****/
		#define INF 987654321
		//Como a prioryt_queue  do C++ nao oferece uma função "diminui_prioridade"
		//vamos utilizar um set para simulá-la 
		//(isso será bastante eficiente.. O(log(n)) por chamada)
		set<pair<int,int> > heap; 
		int s = id(0,0);
		int d = id(l-1,c-1);	
		for(int i=0;i<l;i++) 
			for(int j=0;j<c;j++) 
				custo[i][j] = INF;
		custo[0][0] = maze[0][0];
		
		int adjs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
		//O primeiro elemento de cada par é o seu custo
		//e o segundo elemento é o id do nodo...
		heap.insert(pair<int,int>(custo[0][0],s));
		//Queremos achar o caminho mínimo de s até t
		while(!heap.empty()) {
			//Remove o topo do "heap"
			int v= heap.begin()->second;
			int peso = heap.begin()->first;
			heap.erase(heap.begin());	

			
			if (v==d) break;
			//Para cada w adjacente a v...
			int vy = idToY(v);
			int vx = idToX(v);
			int w,wy,wx;
			for(int i=0;i<4;i++) {
				wy = vy + adjs[i][0];
				wx = vx + adjs[i][1];
				if(wy<0 || wx<0 || wy>=l || wx>=c) 
					continue;
				w = id(wy,wx);

				if (custo[vy][vx] + maze[wy][wx] < custo[wy][wx]) {
					//Apaga vertice se ele ja existe no heap com outro peso...
					if (custo[wy][wx]!=INF)
						heap.erase(heap.find(pair<int,int>(custo[wy][wx],w) ));					

					custo[wy][wx] = custo[vy][vx] + maze[wy][wx]; 
					//Insere vertice com novo custo
					heap.insert(pair<int,int>(custo[wy][wx],w));
				}
			}
			
		}			
		
		/****   ****/

		printf("%d\n",custo[l-1][c-1]);
		
	}

}



