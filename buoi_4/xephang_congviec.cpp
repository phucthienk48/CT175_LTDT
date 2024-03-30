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

void add_edge(Graph *pG, int u, int v){
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


int d[MAX_VERTICES];

void TopoSort(Graph *G, List *L){
	
	for(int u =1; u<=G->n; u++){
		d[u] = 0;
		for(int x = 1; x<=G->n; x++ )
			if(G->A[x][u] != 0)
				d[u]++;
	}
	Queue Q;
	make_null_queue(&Q);
	for(int u=1; u<=G->n; u++){
		if(d[u] == 0)
			enqueue(&Q, u);
	}
	while(!empty(&Q)){
		int u = front(&Q);
		dequeue(&Q);
		push_back(L, u);
		
		for(int v=1; v<=G->n; v++)
			if(G->A[u][v] !=0){
				d[v]--;
				if(d[v] == 0)
					enqueue(&Q, v);
			}
	}
	
}
#define max(x,y) (x > y) ? x : y
#define min(x,y) (x < y) ? x : y

int main(void){
	Graph G;
	freopen("dt.txt", "r", stdin);
	int n, u, x, v;
	scanf("%d",  &n);
	init_graph(&G, n+2);
	int alpha = n+1, beta = n+2;
	d[alpha] = 0;
	
	for(u=1; u<=n; u++){
		scanf("%d", &d[u]);
		do{
			scanf("%d", &x);
			if(x > 0)
				add_edge(&G, x, u);
		}while(x>0);
	}
	
	for( u=1; u<=n; u++){
		int deg_in = 0;
		for(x=1; x<=n; x++){
			if(G.A[x][u] > 0)
				deg_in++;
		}
		if(deg_in == 0)
			add_edge(&G, alpha, u);
	}
	for( u=1; u<=n; u++){
		int deg_out = 0;
		for(v=1; v<=n; v++){
			if(G.A[u][v] > 0)
				deg_out++;
		}
		if(deg_out == 0)
			add_edge(&G, u, beta);
	}
	
	List L;
	TopoSort(&G, &L);
	
	int t[100];
	t[alpha] = 0;
	for(int j=2; j<=L.size; j++){
		int u = element_at(&L, j);
		t[u] = -999;
		for(x=1; x<=G.n; x++)
			if(G.A[x][u] > 0)
				t[u] = max(t[u], t[x] + d[x]);
	}
	
	int T[100];
	T[beta] = t[beta];
	for(int j=L.size-1; j>=1; j--){
		int u = element_at(&L, j);
		T[u] = 999;
		for(v=1; v<=G.n; v++)
			if(G.A[u][v] > 0)
				T[u] = min(T[u], T[v] + d[u]);
	}
	for(u=1; u<=n; u++)
		printf("%d %d\n", t[u], T[u]);
		
	
	return 0;
}
