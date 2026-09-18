#include <stdio.h>
#include <stdlib.h>

int main(void){
    int N,M;
    int **mat;    

    scanf("%d",&N);
    scanf("%d",&M);

    mat = malloc(N*sizeof(int *));
    if(!mat){
        // no hay memoria
        return 1;
    }
    mat[0] = malloc(N*M*sizeof(int));
    if(!mat[0]){
        // no hay memoria
        free(mat);
        return 1;
    }
    for(int i=1;i<N;i++){
        mat[i] = mat[i-1] + M;
    }

    // Cada que se reciba '.' se guarda 0. Caso contrario, se guarda 1 (las reinas valen 1).
    char casilla;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf(" %c",&casilla);  // Espacio antes de %c para ignorar saltos de línea
            mat[i][j] = casilla=='.' ? 0 : 1;
        }
    }

    // Verificamos la matriz generada.
    // for(int i=0;i<N;i++){
    //     printf("\n");
    //     for(int j=0;j<M;j++){
    //         printf("%d ",mat[i][j]);
    //     }
    // }

    int cont = 0;
    int reinas; // Ocurrencias de reinas
    // Si reinas == 0 --> no hay reinas
    // Si reinas == 1 --> Hay una reina.
    // Si reinas == 2 --> Hay un enfretamiento entre reinas.

    // Recorremos verticalmente
    for(int j=0;j<M;j++){
        reinas = 0;
        for(int i=0;i<N;i++){
            if(mat[i][j]==1){reinas++;}
            if(reinas==2){cont++; reinas=1;}
        }
    }

    // Recorremos horizontalmente
    for(int i=0;i<N;i++){
        reinas = 0;
        for(int j=0;j<M;j++){
            if(mat[i][j]==1){reinas++;}
            if(reinas==2){cont++; reinas=1;}
        }
    }

    // Recorremos diagonal: de izq a der
    for(int k=0;k<M;k++){
        reinas = 0;
        for(int i=0;i<N;i++){
            if(i+k<M && mat[i][i+k]==1){reinas++;}
            if(reinas==2){cont++; reinas=1;}
        }
    }
    for(int k=1;k<N;k++){
        reinas = 0;
        for(int i=0;i<M;i++){
            if(k+i<N && mat[k+i][i]==1){reinas++;}
            if(reinas==2){cont++; reinas=1;}
        }
    }

    // Recorremos diagonal: de der a izq
    for(int k=0;k<M;k++){
        reinas = 0;
        for(int i=0;i<N;i++){
            if((M-1)-i-k>=0 && mat[i][(M-1)-i-k]==1){reinas++;}
            if(reinas==2){cont++; reinas=1;}
        }
    }
    for(int k=1;k<N;k++){
        reinas = 0;
        for(int i=0;i<M;i++){
            if(k+i<N && M-1-i>=0 && mat[k+i][M-1-i]==1){reinas++;}
            if(reinas==2){cont++; reinas=1;}
        }
    }

    printf("\n%d",cont);

    free(mat[0]); free(mat);

    return 0;
}