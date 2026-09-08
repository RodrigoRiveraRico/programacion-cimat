#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define RANDOM (float)rand() / RAND_MAX

int main(void){

    srand(time(NULL));

    int n = 3000000;
    float S=0.0f;

    for(int i=0;i<n;i++){
        S += RANDOM;
    }

    float s = fabsf(S-0.5*n)/n;

    printf("%.2f",s);

    return 0;
}