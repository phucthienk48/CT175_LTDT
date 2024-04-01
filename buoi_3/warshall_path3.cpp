#define oo 99999
#define NO_EDGE 0
#define MAXN 100
#include"stdio.h"
typedef struct{
    int n, w;
    int A[100][100];
}Graph;
void init_Graph(Graph *G, int n){
    int i, j;
    G->n = n;
    for(i=1; i<=n; i++){
        for(j=1; j<=n; j++)
            G->A[i][j] = 0;
    }
}

void add_edge(Graph *G, int u, int v, int w){
    G->A[u][v] = w;
}

int pi[MAXN][MAXN];
int next[MAXN][MAXN];

void FloydWarshall(Graph *G){
    int u, v, k;
    for(u=1; u<=G->n; u++){
    	for(v=1; v<=G->n; v++){
    		pi[u][v]= oo;
        	next[u][v] = -1;	
		} 
    }
    for(u=1; u<=G->n; u++){
    	pi[u][u] = 0;
    	next[u]
	}
	for(u=1; u<=G->n; u++){
		for(v=1; v<=G->n; v++){
			if(G->A[u][v] != 0){
				pi[u][v] = G->A[u][v];
				next[u][v] = v;
			}
		}
	}
	for(k=1; k<=G->n; k++)
		for(u=1; u<=G->n; u++)
			for(v=1; v<=G->n; v++){
				if(pi[u][k] + pi[k][v] < pi[u][v] && pi[u][k] != oo && pi[k][v] != oo){ 
					pi[u][v] = pi[u][k] + pi[k][v];
					next[u][v] = next[u][k];
				}
			}
    
}
void print_path(Graph *G, int start, int end){
	printf("path(%d -> %d): ",start, end);
	
	if(next[start][end] == -1 ){
		printf("NO PATH\n");
		return;
	}
	
	while(start!=end){
		printf("%d -> ", start);
		start = next[start][end];
	}
	
	printf("%d\n", end);
}

int main(){
    Graph G;
    int n, m, u, v, w, e;
    freopen("dt.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    for (e = 0; e < m; e++) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    
	FloydWarshall(&G);
	
	
	for(int i=1;i<=G.n;++i){
		for(int j=1;j<=G.n;++j){
			print_path(&G, i, j);
		}
	}
    return 0;
}
