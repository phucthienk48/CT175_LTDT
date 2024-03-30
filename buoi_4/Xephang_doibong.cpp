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

void add_edges(Graph *pG, int u, int v){
	pG->A[u][v]++;
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
}
// khai bao danh sach List
typedef struct{
	int data[100];
	int size;
}List;
void makenull_list(List *L){
	L->size = 0;
}
void push_back(List *L, int x){
	L->data[L->size] = x;
	L->size++;
}
int element_at(List *L, int i){
	return L->data[i-1];
}
void copy_list(List *pL1, List *pL2){
	makenull_list(pL1);
	pL1->size = pL2->size;
	for(int i = 0; i < pL2->size; ++i){
		pL1->data[i] = pL2->data[i];
	}
}


int r[MAX_VERTICES];

void rank(Graph *G){
	int d[MAX_VERTICES];
	for(int u=1; u<=G->n; u++)
		d[u] = 0;
	for(int u=1; u<=G->n; u++){
		for(int v=1; v<=G->n; v++){
			if(G->A[u][v] !=0)
				d[v]++;
		}
	}
	List S1, S2;
	makenull_list(&S1);
	for(int u=1; u<=G->n; u++){
		if(d[u] == 0)
			push_back(&S1, u);
	}
	
	int k = 1;
	while(S1.size > 0){
		makenull_list(&S2);
		for(int i=1; i<=S1.size; i++){
			int u = element_at(&S1, i);
			r[u] = k;
			
			for(int v=1; v<=G->n; v++){
				if(G->A[u][v] != 0){
					d[v]--;
					if(d[v] == 0)
						push_back(&S2, v);
				}
			}
		}
		copy_list(&S1, &S2);
		k++;
	}

}

int main(void){
	Graph G;
	freopen("dt.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for(int i = 0; i<m;++i){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edges(&G, u, v);
	}

	
	rank(&G);
	for(int i = 1; i<=n; ++i){
		printf("%d ",r[i]);
	}
	
	return 0;
}
