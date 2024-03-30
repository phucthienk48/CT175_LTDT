#include <stdio.h>
#include <limits.h>
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
#define MAX_N 100

typedef struct List{
	int data[100];
	int size;
}List;

void make_null(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
}

int element_at(List *pL, int i){
	return pL->data[i-1];
}

int emptyList(List *pL){
	return pL->size == 0;
}

// khai báo queue
#define MAX_Q 100

typedef struct Queue{
	int front, rear;
	int data[MAX_Q];
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

//**********************************************************************
int d[MAX_VERTICES];

void TopoSort(Graph *pG, List *pL){
	
	for(int u =1; u<=pG->n; u++){
		d[u] = 0;
	}
	for(int u =1; u<=pG->n; u++){
		for(int x = 1; x<=pG->n; x++ )
			if(pG->A[x][u] != 0)
				d[u]++;
	}
	
	Queue Q;
	make_null_queue(&Q);
	
	for(int u = 1; u<=pG->n;++u){
		if(d[u]==0){
			enqueue(&Q, u);
			
		}
	}
	
	while(!empty(&Q)){
		int u = front(&Q);
		dequeue(&Q);
		push_back(pL, u);
		
		for(int v = 1; v<=pG->n;++v){
			if(adjacent(pG, u, v)){
				d[v]--;
				if(d[v] == 0){
					enqueue(&Q, v);
				}
			}
		}
	}
}

#define max(x,y) (x > y) ? x : y

int main(void){
	Graph G;
	freopen("dt.txt", "r", stdin);
	
	int n;
	scanf("%d", &n);
	n+=2;
	init_graph(&G, n);
	
	int weight[MAX_VERTICES];
	for(int i = 1; i<=n-2;++i){
		scanf("%d", &weight[i]);
	}
	
	int m;
	scanf("%d", &m);
	
	for(int i = 0; i<m;++i){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edges(&G, u, v);
	}
	
	int alpha = n - 1;
	int beta  = n;
	
	for(int u = 1; u <= n - 2;++u){ // lap cac dinh khong ke alpha va beta
		int deg1 = deg_in(&G, u);
		int deg2 = deg_out(&G, u);
		
		if(deg1 == 0){
			add_edges(&G, alpha, u);
		}
		
		if(deg2 == 0){
			add_edges(&G, u, beta);
		}
	}
	
	List L;
	make_null(&L);
	
	TopoSort(&G, &L);

	int t[MAX_VERTICES];
	t[alpha] = 0;
	weight[alpha] = 0;
	
	for(int i = 1; i<L.size;++i){
		int u = L.data[i];
		t[u] = INT_MIN;
		for(int p = 1; p<=n;++p){
			if(adjacent(&G, p, u)){
				t[u] = max(t[u], t[p] + weight[p]);
			}
		}
	}
	
	printf("%d", t[beta]);
	
	return 0;
}
