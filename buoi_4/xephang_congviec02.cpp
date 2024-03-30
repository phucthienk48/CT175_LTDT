#include <stdio.h>
#include <limits.h>

#define max(x,y) (x > y) ? x : y
#define min(x,y) (x < y) ? x : y

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

int deg_in(Graph *pG, int u){
	int deg = 0;
	for(int v = 1; v <= pG->n; ++v){
		deg += pG->A[v][u];
	}
	return deg;
}

int deg_out(Graph *pG, int u){
	int deg = 0;
	for(int v = 1; v <= pG->n; ++v){
		deg += pG->A[u][v];
	}
	return deg;
}
// khai bao danh sach List
typedef struct{
	int data[100];
	int size;
}List;
void make_null(List *L){
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
	make_null(pL1);
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

int deg[MAX_VERTICES];

List TopoSort(Graph *pG){
	List L;
	make_null(&L);
	
	Queue Q;
	make_null_queue(&Q);
	
	for(int u = 1; u<=pG->n;++u){
		deg[u] = deg_in(pG, u);
		if(deg[u] == 0) enqueue(&Q, u);
	}
	
	while(!empty(&Q)){
		int u = front(&Q);
		dequeue(&Q);
		push_back(&L, u);
		
		for(int v = 1; v<=pG->n;++v){
			if(adjacent(pG, u, v)){
				deg[v]--;
				if(deg[v] == 0) enqueue(&Q, v);
			}
		}
	}
	return L;
}

int main(void){
	Graph G;
	freopen("dt.txt", "r", stdin);
	
	int n;
	scanf("%d", &n);
	
	n = n + 2;
	
	init_graph(&G, n);
	
	int d[n + 1];
	
	for(int u = 1; u<=n;++u){
		scanf("%d", &d[u]); 
		int x;
		
		do{
			scanf("%d", &x);
			if(x > 0){ 
				add_edges(&G, x, u);
			}
		}while(x > 0);
	}
	
	int alpha = n - 1;
	int beta = n;
	
	for(int u = 1; u<=n - 2;++u){
		int deg_1 = deg_in(&G, u);
		int deg_2 = deg_out(&G, u);
		
		if(deg_1 == 0){
			add_edges(&G, alpha, u);
		}
		
		if(deg_2==0){
			add_edges(&G, u, beta);
		}
	}

	
	List L = TopoSort(&G);
	
	
	int t[MAX_VERTICES]; 
	t[alpha] = 0;
	d[alpha] = 0;
	
	for(int i = 1; i<L.size;++i){ 
		int u = L.data[i];
		t[u] = INT_MIN;
		for(int p = 1;p<= G.n;++p){
			if(adjacent(&G, p, u))
				t[u] = max(t[u], t[p] + d[p]);
		}
	}
	
	int T[n+1]; 
	T[beta] = t[beta];
	d[beta] = 0;
	
	for(int i = L.size -2; i > 0;--i){ 
		int u = L.data[i];
		T[u] = INT_MAX;
		for(int v = 1; v<=G.n;++v){ 
			if(adjacent(&G, u, v)){
				T[u] = min(T[u], T[v] - d[u]); 
			}
		}
	}
	for(int u = 1; u<=n - 2;++u){ 
		printf("%d %d\n", t[u], T[u]);
	}
	
	
	return 0;
}
