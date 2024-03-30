#include <stdio.h>

#define MAX_SIZE 100
typedef int ElementType;

typedef struct {
	ElementType data[MAX_SIZE];
	int top_idx;
} Stack;

void make_null_stack(Stack *pS) {
	pS->top_idx = -1;
}

void push(Stack *pS, ElementType u) {
	pS->top_idx++;
	pS->data[pS->top_idx] = u;
}

ElementType top(Stack *pS) {
	return pS->data[pS->top_idx];
}

void pop(Stack *pS) {
	pS->top_idx--;
}

int empty(Stack *pS) {
	return pS->top_idx == -1;
}

#define MAX_VERTICES 100
typedef struct {
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n=n;
	int i, j;
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			pG->A[i][j]=0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v]++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
}

void print_adjacent(Graph *pG, int u){
	printf("adjacent[%d] = ", u);
	int v;
	for(v = 1; v<=pG->n;++v){
		if(adjacent(pG, u, v)){
			printf("%d ", v);
		}
	}
	printf("\n");
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
	for(i=1;i<=pG->n;++i){
		if(adjacent(pG, u, i)){
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

int main(void){
	freopen("dt.txt", "r", stdin); //Khi n?p b�i nh? b? d�ng n�y.
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int i;
	for(i=1;i<=n;++i){
		parent[i] = -1;
		color[i] = WHITE;
	}
	
	has_circle = 0;
	
	for(i=1;i<=n;++i){
		if(color[i]==WHITE){
			dfs(&G, i, -1);
		}
	}
	
	Stack S;
	make_null_stack(&S);
	
	if(has_circle){
		push(&S, end);
		push(&S, start);
		int temp = parent[start];
		while(temp!=parent[end]){
			push(&S, temp);
			temp = parent[temp];
		}
		
		while(!empty(&S)){
			printf("%d ", top(&S));
			pop(&S);
		}
	}else{
		printf("-1");
	}
	
	return 0;
}

