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

void add_edge(Graph *G, int u, int v){
    G->A[G->m].u = u;
    G->A[G->m].v = v;
    G->m++;
}

int adjacent(Graph *G, int u, int v){
	int i;
    for(i=0; i<=G->m; i++){
        if(G->A[i].u == u && G->A[i].v == v)
            return 1;
    }
    return 0;
}

typedef struct{
    int data[100];
    int front, rear;
}Queue;

void make_null(Queue *Q){
    Q->front = 0;
    Q->rear = -1;
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
int empty(Queue *Q){
    return Q->front > Q->rear;
}

void BFS(Graph *G, int s){
    Queue Q;
    make_null(&Q);
    enQueue(&Q, s);
    int make[100];
    int i;
    for(i=1; i<=G->n; i++)
        make[i] = 0;
    while(!empty(&Q)){
        int u = front(&Q);
        deQueue(&Q);
        if(make[u] !=0)
            continue;
        printf("%d\n", u);
        make[u] = 1;
        int i;
        for(i=1; i<=G->n; i++){
            if(adjacent(G, u, i))
                enQueue(&Q, i);
        }
    }
}


int main(){
    Graph G;
    int n, m;
    freopen("dt.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v;
    int i;
    for(i=0; i<m; i++){
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    int s;
    scanf("%d",&s);
    BFS(&G, s);
    
    return 0;
    
}
