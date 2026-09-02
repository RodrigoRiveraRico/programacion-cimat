#include <stdio.h>

int main(void){

    // printf("\n");
    for(int i=-100;i<1000;i++){
        if(i%2==0 && i<=0){
            printf("%d ",i);
        }
        else if(i>0 && i<=500){
            printf("%d ",i);
        }
        else if(i>500 && i<600){
            continue;
        }
        else if(i%3==0 && i>0 && i<999){
            printf("%d ",i);
        }
        else if(i==999){
            printf("%d",i);
        }
    }
    return 0;
}