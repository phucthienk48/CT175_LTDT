#include <stdio.h>
typedef struct{
    int u,v;
}Edge;
typedef struct{
    Edge edges[100];
    int n,m;
}Graph;
void init_graph(Graph *pG, int n){
    pG->n=n;
    pG->m=0;
}
void add_egde(Graph *pG, int u, int v){
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}
int adjacent(Graph *pG, int u, int v){
    int e;
    for(e = 0; e < pG->m; e++){
        if(pG->edges[e].u == u && pG->edges[e].v == v)
            return 1;
    }
    return 0;
}
typedef struct{
    int data[100];
    int front, rear;
}Queue;
void make_null(Queue *pQ){
    pQ->front = 0;
    pQ->rear = -1;
}
void enqueue(Queue *pQ, int u){
    pQ->rear++;
    pQ->data[pQ->rear] = u;
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

void BFS(Graph *pG, int s, int mark[], int parent[]){
    Queue Q;
    make_null(&Q);
    enqueue(&Q, s);
    parent[s]=-1;
    while(!empty(&Q)){
        int u = front(&Q); dequeue(&Q);
        if(mark[u] != 0) continue;
        // printf("%d\n",u);
        mark[u] = 1;
        int v;
        for(v=1; v <= pG->n; v++){
            if(adjacent(pG, u, v) && (mark[v]==0)) {
                enqueue(&Q, v);
                if(parent[v] == 0)
                    parent[v] = u;
                
            }
        }
    }
}
int main(){
    int n,m;
    freopen("dt6.txt", "r", stdin);
    Graph G;
    scanf("%d%d",&n,&m);
    init_graph(&G, n);
    int u,v,i;
    for(i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        add_egde(&G, u, v);
    }
    int mark[100], parent[100];
    for(i=1; i<=n; i++) mark[i] = 0;
    for(i=1; i<=n; i++) parent[i] = 0;
    for(i=1; i<=n; i++){
        if(mark[i] == 0)
            BFS(&G, i, mark, parent);
    }
    for(i=1; i<=n; i++){
        printf("%d %d\n",i,parent[i]);
    }
 

    return 0;
}
