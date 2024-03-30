#include"stdio.h"
typedef struct{
    int u, v;
}Edge;

typedef struct{
    int n, m;
    Edge A[100];
}Graph;

void init_Graph(Graph *G, int n){
    G->n = n;
    G->m = 0;
}
void add_egde(Graph *G, int u, int v){
    G->A[G->m].u = u;
    G->A[G->m].v = v;
    G->m++;
}
int adjacent(Graph *G, int  u, int v){
	int i;
    for(i=0; i<G->m; i++){
        if((G->A[i].u == u && G->A[i].v == v) ||
        (G->A[i].u == v && G->A[i].v == u))
            return 1;
    }
    return 0;
}

typedef struct{
    int data[100];
    int top_idx;
}Stack;
void make_null(Stack *S){
    S->top_idx = -1;
}
void push(Stack *S, int x){
    S->top_idx++;
    S->data[S->top_idx] = x;
}
void pop(Stack *S){
    S->top_idx--;
}
int top(Stack *S){
    return S->data[S->top_idx];
}
int empty(Stack *S){
    return S->top_idx == -1;
}
void DFS(Graph *G, int s, int make[]){
    Stack S;
    make_null(&S);
    push(&S, s);
    // int make[100];
    // for(int i=1; i<=G->n; i++) make[i] = 0;
    while(!empty(&S)){
        int u = top(&S);
        pop(&S);
        if(make[u] != 0) continue;
        printf("%d\n", u);
        make[u] = 1;
        int i;
        for(i=G->n; i>=1; i--){
            if(adjacent(G, u, i))
                push(&S, i);
        }
    }
}

int main(){
    int n,m;
    Graph G;
    freopen("dt.txt", "r", stdin);
    scanf("%d%d",&n,&m);
    init_Graph(&G, n);
    int u,v,i;
    for(i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        add_egde(&G, u, v);
    }
    int make[100];
    for(i=1; i<=n; i++) make[i] = 0;
    int s;
    for(s=1; s<=n; s++){
        if(make[s] == 0)
            DFS(&G, s, make);
    }
    
    return 0;
}

