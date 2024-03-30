#include <stdio.h>

#define MAX_VERTICES 100
typedef struct {
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n=n;
	int i, j;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;++j){
			pG->A[i][j]=0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v]++;
	pG->A[v][u]++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0 && pG->A[u][v] > 0;
}


#define WHITE 0
#define GRAY 1
#define BLACK 2

int color[MAX_VERTICES], parent[MAX_VERTICES];
int has_circle, start, end;

void dfs(Graph *pG, int u, int p){	
	if(color[u]==BLACK){
		return;
	}
		
	color[u] = GRAY;
	parent[u] = p;
	int i;
	for(i=1;i<=pG->n;i++){
		if(adjacent(pG, u, i)){
			if(i==p){
				continue;
			}
			if(color[i]==WHITE){
				dfs(pG, i, u);	
			}else if(color[i]==GRAY){ //neu cac dinh ke dang trong trang thai duyet -> chu trinh
				start = u;
				end = i;
				has_circle = 1;
			}
		}
	}
	color[u] = BLACK;
}

int main(){
	Graph G;
	freopen("dt.txt", "r", stdin);
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int i;
	for(i=1;i<=n;i++){
		color[i] = WHITE;
	}
	
	has_circle = 0;
	
	for(i=1;i<=n;i++){
		if(color[i]==WHITE){
			dfs(&G, i,-1);
		}
	}
	
	if(has_circle){
		
		int d[n], k = 0;
		
		d[k++] = end;
		d[k++] = start;
		
		int temp = parent[start];
		while(temp!=parent[end]){
			d[k++] = temp;
			temp = parent[temp];
		}

		for(i=k-1;i>=0;--i){
			printf("%d ", d[i]);
		}
	}else{
		printf("-1");
	}
	
	return 0;
}

