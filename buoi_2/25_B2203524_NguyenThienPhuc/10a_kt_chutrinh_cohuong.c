#include <stdio.h>

#define MAX_VERTICES 100
typedef struct {
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n=n;
	int i,j;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;++j){
			pG->A[i][j]=0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v]++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
}


#define WHITE 0
#define GRAY 1
#define BLACK 2

int color[MAX_VERTICES];
int has_circle;
void dfs(Graph *pG, int u){	
	if(color[u]==BLACK)
		return;

		
	color[u] = GRAY;
	int i;
	for(i=1;i<=pG->n;i++)
		if(adjacent(pG, u, i)){
		    if(color[i]==WHITE)
				dfs(pG, i);
			else if(color[i]==GRAY)
				has_circle = 1;
		}
			
	color[u] = BLACK;
}






int main(){
	freopen("dt.txt", "r", stdin);
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int i;
	for(i=1;i<=n;i++)
		color[i] = WHITE;
	
	has_circle = 0;
	
	for(i=1;i<=n;i++)
		if(color[i]==WHITE)
			dfs(&G, i);

	
	if(has_circle)
		printf("CIRCLED");
	else
		printf("NO CIRCLE");
	
	
    return 0;
}
