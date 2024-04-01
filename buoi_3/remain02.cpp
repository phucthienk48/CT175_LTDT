#include"stdio.h"
#define MAX_X 100
typedef struct{
    int u, v;
    int w;
}Edges;
typedef struct{
    int n, m;
    Edges edge[MAX_X];
}Graph;

void init_graph(Graph *G, int n){
    G->n = n;
    G->m = 0;
}
void add_edges(Graph *G, int u, int v, int w){
    G->edge[G->m].u = u;
    G->edge[G->m].v = v;
    G->edge[G->m].w = w;
    G->m++;
}

#define oo 100
int pi[MAX_X];
int p[MAX_X];
int negative_cycle;

void Bellman_Rord(Graph *G, int s){
    int u, v, w;
    for(int i=1; i<=G->n; i++)
        pi[i] = oo;
        
    pi[s] = 0;
    p[s] = -1;
    
    for(int it=1; it<G->n; it++){
    	for(int k=0; k<G->m; k++){
	    	u = G->edge[k].u;
	        v = G->edge[k].v;
	        w = G->edge[k].w;
	        if(pi[u]==oo){
	            continue;
	        }
	        if(pi[u] + w < pi[v]){
	            pi[v] = pi[u] + w;
	            p[v] = u;
	        }	
		}    
            
    }
    negative_cycle = 0;
    for(int k=0; k<G->m; k++){
	    	u = G->edge[k].u;
	        v = G->edge[k].v;
	        w = G->edge[k].w;
	        if(pi[u] + w < pi[v] && pi[u]!=oo){
	        	negative_cycle = 1;
	        	return;
			}
	}
}

int main(){
    Graph G;
    freopen("dt.txt", "r", stdin);
    int u, v, w, n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    
    for(int i=0; i<m; i++){
        scanf("%d%d%d", &u, &v, &w);
        add_edges(&G, u, v, w);
    }
    int start ;
    scanf("%d", &start);
    Bellman_Rord(&G, start);
    if(negative_cycle){
        printf("YES");
    }else{
        printf("NO");
    }
    
    return 0;
}

