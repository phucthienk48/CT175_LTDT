#include"stdio.h"
#define MAX_M 500
typedef struct{
	int u, v;
}Edge;
typedef struct{
	int n, m;
	Edge edges[MAX_M];
}Graph;
void init_Graph(Graph *G, int n){
	G->n = n;
	G->m = 0;
}
//them cung vao do thi
void add_edge(Graph *G, int u, int v){
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->m++;
}


int main(){
	Graph G;
	init_Graph(&G, 5);
	printf("%d %d",G.n, G.m);
	return 0;
}
