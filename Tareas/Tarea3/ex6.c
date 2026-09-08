#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n;
    float **L,*b,*x;

    // printf("\nIngresa n: ");
    scanf("%d",&n);

    L = malloc(n * sizeof(float *));
    if(!L){return 1;}
    for(int i=0;i<n;i++){
        L[i] = malloc((i+1)*sizeof(float));
        if(!L[i]){
            for(int k=0;k<i;k++){
                free(L[k]);
            }
            free(L);
            return 1;
        }
    }

    b = malloc(n*sizeof(float));
    if(!b){
        for(int k=0;k<n;k++){
            free(L[k]);
        }
        free(L);
        return 1;
    }

    x = malloc(n*sizeof(float));
    if(!x){
        for(int k=0;k<n;k++){
            free(L[k]);
        }
        free(L);
        return 1;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            // printf("\nIngresa L %d%d ",i,j);
            scanf("%f",&L[i][j]);
        }
    }
    
    for(int i=0;i<n;i++){
        // printf("\nIngresa b %d ",i);
        scanf("%f",&b[i]);
    }

    float suma;
    for(int i=0;i<n;i++){
        suma = 0;
        for(int j=0;j<i;j++){
            suma+=L[i][j]*x[j];
        }
        x[i]=(b[i]-suma)/L[i][i];
    }

    for(int i=0;i<n;i++){
        printf("\n%f ",x[i]);
    }

    free(L); free(b); free(x);
    return 0;
}