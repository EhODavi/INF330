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



inline double distancia(pair<int,int> p1, pair<int,int> p2) {
	return sqrt((p1.first-p2.first)*(p1.first-p2.first) + (p1.second-p2.second)*(p1.second-p2.second));
}


int main() {
	double adj[200][200]; //Matriz de adjacencia...
	int ct =1;
	while(true) {
		int npedras;
		scanf("%d",&npedras);
		
		if(npedras==0)
			return 0;
		
		vector<pair<int,int> > pedras;
		for(int i=0;i<npedras;i++) {
			pair<int,int> pedra;
			scanf("%d %d",&pedra.first, &pedra.second);	
			pedras.push_back(pedra);			
		}

		for(int i=0;i<npedras;i++) 
			for(int j=0;j<npedras;j++)
				adj[i][j] = distancia(pedras[i],pedras[j]);

		for(int k=0;k<npedras;k++)
			for(int i=0;i<npedras;i++)
				for(int j=0;j<npedras;j++)
						adj[i][j] = min(adj[i][j], max(adj[i][k],adj[k][j]));

		printf("Scenario #%d\n",ct++);
		printf("Frog Distance = %.3lf\n\n",adj[0][1]);
		
	}

}



