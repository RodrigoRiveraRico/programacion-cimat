#include <stdio.h>

double depsilon(void);
float fepsilon(void);

int main(void){

    int presicion;
    scanf("%d",&presicion);

    if(presicion==1){
        //float
        printf("%.15f",fepsilon());
        return 0;
    } 
    else{
        //double
        printf("%.25f",depsilon());
        return 0;
    }
}
double depsilon(void){
    
    double eps = 0.5;
    double unit = 1.0;
    double val = unit + eps;

    while(val > unit){
        eps/=2;
        val = unit + eps;
    }
    eps = 2*eps;

    return eps;
}

float fepsilon(void){
    
    float eps = 0.5;
    float unit = 1.0;
    float val = unit + eps;

    while(val > unit){
        eps/=2;
        val = unit + eps;
    }
    eps = 2*eps;

    return eps;
}