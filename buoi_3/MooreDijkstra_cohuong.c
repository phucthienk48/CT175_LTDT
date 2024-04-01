#include <stdio.h>
#include <limits.h>

#define MAX_N 100

typedef struct Edge{
	int u, v;
	int weight;
}Edge;

typedef struct Graph{
	int n, m;
	Edge edges[MAX_N];
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edges(Graph *pG, int u, int v, int w){
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->edges[pG->m].weight = w;
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){
	int i;
	for( i=0;i<pG->m;++i){
		if(pG->edges[i].u == u && pG->edges[i].v == v){
			return 1;
		}
	}
	return 0;
}

#define oo INT_MAX

int pi[MAX_N];
int p[MAX_N];
int mark[MAX_N];

int getWeight(Graph *pG, int u, int v){
	int i;
	for(i=0;i<pG->m;++i){
		if(pG->edges[i].u == u && pG->edges[i].v == v){
			return pG->edges[i].weight;
		}
	}
	return 0;
}

void MooreDijkstra(Graph *pG, int s){
	int i, j;
	for(i=1;i<=pG->n;++i){
		pi[i] = oo;
		p[i] = 0;
		mark[i] = 0;
	}
	
	pi[s] = 0;
	p[s] = -1;
	for( i=1;i<=pG->n-1;++i){
		int u, min_pi = oo;
		for(j=1;j<=pG->n;++j){
			if(pi[j] < min_pi && !mark[j]){
				u = j;
				min_pi = pi[j];
			}
		}
		
		mark[u] = 1;
		int v;
		for(v=1;v<=pG->n;++v){
			if(adjacent(pG, u, v) && !mark[v]){
				if(pi[u] + getWeight(pG, u, v) < pi[v]){
					pi[v] = pi[u] + getWeight(pG, u, v);
					p[v] = u;
				}
			}
		}
	}
}

int main(void){
	freopen("dt.txt", "r", stdin);
	
	Graph G;
	
	int n,m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	int i;
	for(i = 0;i<m;++i){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edges(&G, u,v,w);
	}
	
	MooreDijkstra(&G, 1);
	
	for(i=1;i<=n;++i){
		printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
	}
	
	return 0;
}
