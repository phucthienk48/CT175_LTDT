#define MAXN 99
#define NO_EDGE -10
#define INF 9999

#include "stdio.h"

typedef struct{
    int n, m;
    int A[MAXN][MAXN];
}Graph;

void init_graph(Graph *G, int n){
    G->n = n;
    G->m = 0;
    for(int i=1; i<=G->n; i++)
        for(int j=1; j<=G->n; j++)
            G->A[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int u, int v, int w){
    G->A[u][v] = w;
    G->m++;
}

int mark[MAXN], pi[MAXN], p[MAXN];

void MooreDijkstra(Graph *G, int s){
    int u, v, it;
    for(u=1; u<=G->n; u++){
        pi[u] = INF;
        mark[u] = 0;
    }
    
    pi[s] = 0;
    p[s] = -1;
    for(it=1; it<G->n; it++){
        int min_pi = INF;
        int i;
        for(i=1; i<=G->n; i++){
            if((mark[i] == 0) && (pi[i] < min_pi )){
                min_pi = pi[i];
                u = i;
            }
        }
        mark[u] = 1;
        for(v=1; v<=G->n; v++)
            if(G->A[u][v] != NO_EDGE && mark[v] == 0){
                if(pi[u] + G->A[u][v] < pi[v]){
                    pi[v] = pi[u] + G->A[u][v];
                    p[v] = u;
                }
            }
    }

}

int main(){
    Graph G;
    freopen("dt.txt", "r", stdin);
    int n, m, u, v, w, e;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    
    for (e = 0; e < m; e++) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    
    MooreDijkstra(&G, 1);
    for(u=1; u<=G.n; u++)
        printf("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, p[u]);
    
    
    return 0;
}
