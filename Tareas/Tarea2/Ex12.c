#include <stdio.h>
#include <stdlib.h>

/*
* Sort in-place
*/
void bu_sort(float *, unsigned int);
float mediana(float *, unsigned int);

int main(void){

    unsigned int N,K;
    float *arr, med;

    scanf("%u",&N);
    scanf("%u",&K);

    // Memoria dinámica para el arreglo
    arr = malloc(N*sizeof(float));
    if(!arr){
        free(arr);
        return 1;
    }
    // Elementos del arreglo
    for(int i=0;i<N;i++){
        scanf("%f",&arr[i]);
    }

    // Bubble sort
    bu_sort(arr,N);

    // Verificar el sort
    // printf("\n");
    // for(int i=0;i<N;i++){
    //     printf("%f ",arr[i]);
    // }

    // Mediana
    med = mediana(arr,N);
    printf("\n%.2f",med);

    // Primeros K elementos
    int i=0;
    printf("\n");
    while(K>i){
        printf("%.2f ",arr[i]);
        i++;
    }

    free(arr);
    return 0;
}

void bu_sort(float *arr, unsigned int N){

    int i,k;
    float temp;

    for(k=0;k<(N-1);k++){
        for(i=0;i<N-1-k;i++){
            if(arr[i]>arr[i+1]){
                temp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

float mediana(float *arr, unsigned int N){
    unsigned int pos = N/2; //Parte entera

    return N%2==0 ? (arr[pos]+arr[pos-1])/2.0 : arr[pos];
}