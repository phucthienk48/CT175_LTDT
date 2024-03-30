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
// khai bao hang doi Queue
typedef struct Queue{
	int front, rear;
	int data[100];
}Queue;

void make_null_queue(Queue *pQ){
	pQ->rear = -1;
	pQ->front = 0;
}

void enqueue(Queue *pQ, int x){
	pQ->rear++;
	pQ->data[pQ->rear] = x;
}

void dequeue(Queue *pQ){
	pQ->front++;
}

int front(Queue *pQ){
	return pQ->data[pQ->front];
}

int empty(Queue *pQ){
	return pQ->front > pQ->rear;
}

//**************************************
int deg_in(Graph *pG, int u){
	int deg = 0;
	for(int v = 1; v <= pG->n; ++v){
		deg += pG->A[v][u];
	}
	return deg;
}


int d[MAX_VERTICES];
int mark[MAX_VERTICES];

void dfs(Graph *G, int u, List *L){
	mark[u] = 1;
	for(int v=1; v<=G->n; v++){
		if(adjacent(G, u, v) && mark[v] == 0){
			dfs(G, v, L);
		}
	}
	push_back(L, u);
}

void TopoSort(Graph *G, List *L){
	
	for(int u =1; u<=G->n; u++){
		mark[u] = 0;
		d[u] = deg_in(G, u);
	}
	for(int v=1; v<=G->n; v++){
		if(mark[v] == 0){
			dfs(G, v, L);
		}
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
	
	
	List L;
	makenull_list(&L);
	
	TopoSort(&G, &L);
	
	for(int i = L.size-1; i>=0;--i){
		printf("%d\n", L.data[i]);
	}
	
	return 0;
}
