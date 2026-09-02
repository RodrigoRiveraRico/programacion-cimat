#include <stdio.h>
#include <stdlib.h>

int sort(int, int *);

int main(void){
    int n;
    int *vec;

    scanf("%d",&n);
    vec = malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d",&vec[i]);
    }
    
    sort(n,vec);
    free(vec);

    return 0;
}

int sort(int n,int *vec){
    int min;
    int pos;
    int temp;
    int *p = vec;

    for(int j=n;j>0;j--){
        min = *p;
        pos = 0;
        for(int i=1;i<j;i++){
            if(*(p+i) < min){
                min = *(p+i);
                pos = i;
            }
        }
        temp = *p;
        *p = min;
        *(p+pos) = temp;

        p++;
    }      

    // printf("\n");
    for(int i=0;i<n;i++){
        printf("%d ",vec[i]);
    }

    return 0;
}