#include <stdio.h>
#define MAX_VERTICES 100

typedef struct Graph{
	int n, m;
	int A[MAX_VERTICES][MAX_VERTICES];
}Graph;

void init_graph(Graph *pG, int n){
	pG->m++;
	pG->n = n;
	
	for(int i = 0; i < n ;++i){
		for(int j = 0; j<n;++j){
			pG->A[i][j] = 0;
		}
	}
}

void add_edges(Graph *pG, int u, int v, int w){
	pG->A[u][v] = w;
	pG->A[v][u] = w;		
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0 && pG->A[v][u] > 0;
}
#define oo 999
int pi[MAX_VERTICES];
int p[MAX_VERTICES];
int mark[MAX_VERTICES];

int prim(Graph *pG, Graph *pT, int s){
	int i, u, v, x;
	for(u = 1; u<=pG->n;++u){
		pi[u] = oo;
		p[u] = -1;
		mark[u] = 0;
	}
	
	pi[s] = 0;
	
	for(int it = 1; it < pG->n;++it){
		int min_dist = oo;

		for(x = 1; x<=pG->n; ++x){
			if(!mark[x] && pi[x] < min_dist){
				min_dist = pi[x];
				u = x;
			}
		}
		
		mark[u] = 1;
		
		for(int v = 1; v<=pG->n;++v){
			if(adjacent(pG, u, v)){
				if(mark[v] == 0 && pG->A[u][v] < pi[v]){
					pi[v] = pG->A[u][v];
					p[v] = u;
				}
			}
		}
	}
	
	init_graph(pT, pG->n);
	int sum_w = 0;
	
	for(int u = 1; u<=pG->n;++u){
		if(p[u]!= -1){
			int w = pG->A[p[u]][u];
			add_edges(pT, p[u], u, w);
			sum_w += w;
		}
	}
	return sum_w;
}

int main(void){
	Graph G;
	freopen("dt.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for(int i = 0; i<m;++i){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edges(&G, u, v, w);
	}
	
	Graph T;
	int sum = prim(&G, &T, 1);
	
	printf("%d\n", sum);
	
	for(int i = 1; i <= n ;++i){
		for(int j = i; j<=n;++j){
			if(adjacent(&T, i, j)){
				printf("%d %d %d\n", i, j, T.A[i][j]);
			}
		}
	}
	return 0;
}
