#include"stdio.h"
typedef struct{
    int u, v;
}Edge;

typedef struct{
    int n, m;
    Edge A[50];
}Graph;

void init_Graph(Graph *G, int n){
    G->n = n;
    G->m = 0;
}

void add_edge(Graph *G, int u,int v){
    G->A[G->m].u = u;
    G->A[G->m].v = v;
    G->m++;
}

int adjacent(Graph *G, int u, int v){
	int i;
    for(i=0; i<G->m; i++){
        if((G->A[i].u == u && G->A[i].v == v) ||
        (G->A[i].u == v && G->A[i].v == u))
            return 1;
    }
    return 0;
}

typedef struct{
    int data[50];
    int front, rear;
}Queue;
void make_null(Queue *Q){
    Q->front = 0;
    Q->rear = -1;
}
int empty(Queue *Q){
    return Q->front > Q->rear;
}
void enQueue(Queue *Q, int u){
    Q->rear++;
    Q->data[Q->rear] = u;
}

void deQueue(Queue *Q){
    Q->front++;
}

int front(Queue *Q){
    return Q->data[Q->front];
}

void BFS(Graph *G, int s){
    Queue Q;
    make_null(&Q);
    enQueue(&Q, s);
    int mark[100];
    int i;
    for(i=1; i<=G->n; i++)
        mark[i] = 0;
    while(!empty(&Q)){
        int u = front(&Q);
        deQueue(&Q);
        if(mark[u]!=0)
            continue;
        printf("%d\n", u);
        mark[u] = 1;
        int i;
        for(i=1; i<=G->n; i++){
            if(adjacent(G, u, i))
                enQueue(&Q, i);
        }
    }
}




int main(){
    Graph G;
    freopen("dt.txt", "r", stdin);
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int i;
    for(i=0; i< m; i++){
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    BFS(&G, 1);
    return 0;
}


