#include <stdio.h>
#define MAX_N 100

typedef struct Edge {
	int u, v;
	int weight;
} Edge;

typedef struct Graph {
	int n, m;
	Edge edges[MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
	pG->n = n;
	pG->m = 0;
}

void add_edges(Graph *pG, int u, int v, int w) {
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->edges[pG->m].weight = w;

	pG->m++;
}

#define oo 100

int pi[MAX_N];
int p[MAX_N];

int negative_cycle;

void BellmanFord(Graph *pG, int s) {
	for (int i = 1; i <= pG->n; i++) {
		pi[i] = oo;
	}

	pi[s] = 0;
	p[s] = -1;

	for (int i = 1; i <= pG->n - 1; ++i) { //lap so dinh - 1 lan
		for (int j = 0; j < pG->m; ++j) { // lap so cung lan
			int u = pG->edges[j].u;
			int v = pG->edges[j].v;
			int w = pG->edges[j].weight; //lay gia tri cua moi cung

			if (pi[u] == oo) { //neu cung tu u den v chua duyet thi bo qua
				continue;
			}

			if (pi[u] + w < pi[v]) { //neu cung do co gia tri tot hon thi cap nhat lai
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
	
	negative_cycle = 0;
	
	for (int k = 0; k < pG->m; ++k) {
		int u = pG->edges[k].u;
		int v = pG->edges[k].v;
		int w = pG->edges[k].weight;
		
		if (pi[u] + w < pi[v]) {
			negative_cycle = 1;
			return;
		}
	}
}

int main(void) {
	freopen("dt.txt", "r", stdin);

	Graph G;

	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for (int i = 0; i < m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edges(&G, u, v, w);
	}
	
	int start, end;
	
	scanf("%d%d", &start, &end);

	BellmanFord(&G, start);
	
	if(pi[end] == oo){
		printf("-1");
	}else{
		printf("%d", pi[end]);
	}

	return 0;
}
