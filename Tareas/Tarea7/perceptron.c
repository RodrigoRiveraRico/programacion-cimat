#include <stdio.h>
#include <stdlib.h>

#define MAX_EPOCHS 1000
#define LEARNING_RATE 0.01

typedef struct {
    double x;
    double y;
    int target;
}point;

int predict(double x, double y, double w1, double w2, double bias);

int main(void){

    // Conjunto de entrenamiento
    int n;
    scanf("%d", &n);

    point *training_set = malloc(n * sizeof *training_set);
    if(!training_set){
        return 1;
    }

    // Llenamos el conjunto de entrenamiento
    for(int i=0;i<n;i++){
        scanf(" %lf %lf %d", &training_set[i].x, &training_set[i].y, &training_set[i].target);
    }

    // Parámetros a entrenar
    // ini
    double w1   = 0;
    double w2   = 0;
    double bias = 0;

    ///////// Entrenamiento /////////
    int n_epochs = 0;
    while(n_epochs < MAX_EPOCHS){
        for(int i=0;i<n;i++){
            int guess = predict(training_set[i].x, training_set[i].y, w1, w2, bias);
            int error = training_set[i].target - guess;
            if(error != 0){
                w1   = w1   + (LEARNING_RATE*error*training_set[i].x);
                w2   = w2   + (LEARNING_RATE*error*training_set[i].y);
                bias = bias + (LEARNING_RATE*error);
            }
        }
        n_epochs++;
    }

    ///////// Evaluacion /////////
    // Conjunto evaluación
    int m;
    scanf("%d", &m);
    point *eval_set = malloc(m * sizeof *eval_set);
    if(!eval_set){
        free(training_set);
        return 1;
    }
    // Llenamos el conjunto de evaluación
    for(int i=0;i<m;i++){
        scanf(" %lf %lf %d", &eval_set[i].x, &eval_set[i].y, &eval_set[i].target);
    }

    // Contamos el número de aciertos
    int contador_aciertos = 0;
    for(int i=0;i<m;i++){
        if( predict(eval_set[i].x, eval_set[i].y, w1, w2, bias) == eval_set[i].target){
            contador_aciertos++;
        }
    }

    // Razón de puntos de evaluación que fueron clasificados correctamente
    float p = (float)contador_aciertos / (float)m;
    printf("%.4f", p);

    free(training_set);
    free(eval_set);
    return 0;
}

int predict(double x, double y, double w1, double w2, double bias)
{
    double suma = w1*x + w2*y + bias;

    if(suma < 0){
        return 0;
    }
    else if(suma >= 0){
        return 1;
    }
}
