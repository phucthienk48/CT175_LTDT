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
            G->A[i][j] = NO_EDGE;
    }
}

void add_edge(Graph *G, int u, int v, int w){
    G->A[u][v] = w;
}

int mark[MAXN];
int pi[MAXN];
int p[MAXN];

void Dijkstra(Graph *pG, int s) {
    //Kh?i t?o
    int u, i, j;
    for (u = 1; u <= pG->n; u++){
        mark[u] = 0;
        pi[u] = oo; //Vô cung l?n, ví d?: 9999999
    }
    pi[s] = 0;
    
    //L?p i t? 1 d?n n - 1
    for ( i = 1; i <= pG->n - 1; i++) {
        //1. Tìm u
        int min_pi = oo;
        int u = -1;
        for ( j = 1; j <= pG->n; j++)
            if (!mark[j] && pi[j] < min_pi) {
                min_pi = pi[j];
                u = j;
            }
        if (u == -1) //không tìm du?c u
            break;
            
        //2. Ðánh d?u u
        mark[u] = 1;

        //3. Xét các d?nh k? v c?a u d? c?p nh?t (n?u th?a di?u ki?n)
        int v;
        for (v = 1; v <= pG->n; v++)
            if (pG->A[u][v] != NO_EDGE && !mark[v] && pi[u] + pG->A[u][v] < pi[v]) {
                pi[v] = pi[u] + pG->A[u][v]; //pG->A[u][v] là tr?ng s? c?a cung (u,v)
                p[v] = u;
            }
    }
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
    
    Dijkstra(&G, 1);
    int i;
    for(i=1; i<=n; i++){
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
    }
    
    return 0;
}
