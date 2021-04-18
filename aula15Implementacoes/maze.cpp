#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
using namespace std;

void espalha(int l,int c,char carac,vector<string > &m,int rows,int cols) {
	if (l<0 || c<0 || c>=cols || l>=rows || m[l][c]!=carac ) 
		return;
	
	m[l][c] = '#';
	espalha(l-1,c,carac,m,rows,cols);
	espalha(l+1,c,carac,m,rows,cols);
	espalha(l,c-1,carac,m,rows,cols);
	espalha(l,c+1,carac,m,rows,cols);
}

int main() {
	int nc;	
	char temp;
	scanf("%d",&nc);
	scanf("%c",&temp);
	for(int i=1;i<=nc;i++) {
		int rows,cols;
		int px,py;		
		vector<string > m(101);

		int linhas;
		for(linhas=0;true;linhas++) {
			getline(cin,m[linhas]);
			int len = m[linhas].size();
			for(int c=0;c<len;c++)
				if(m[linhas][c]=='*') {
					py=linhas; px=c;
				}
			if (m[linhas][0]=='_') break;
		} 
		m[py][px]=' ';
		espalha(py,px,' ',m,linhas,m[0].size());

		for(int l=0;l<=linhas;l++) {
			int len = m[l].size();
			for(int c=0;c<len;c++) {
				printf("%c",m[l][c]);
			}
			printf("\n");
		}
		
	}
	
}
