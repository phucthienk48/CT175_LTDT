#include"stdio.h"
typedef struct{
    int n, m;
    int A[10][10];
}Graph;

int main(){
    Graph G;
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++){
            scanf("%d", &G.A[i][j]);
        }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int e=1; e<=G.A[i][j]; e++){
                printf("%d %d\n", i, j);
                G.A[j][i]--;
            }
        }
    }
    return 0;
}
