#include <stdio.h>

int main(void){

    unsigned short int h_trabajadas;    // Horas trabajadas
    float pxh = 100.50f; // Pago por hora
    float pago;

    printf("\n Ingrese las horas trabajadas: ");
    scanf("%hu", &h_trabajadas);

    if(h_trabajadas > 40){
        pago = 40 * pxh;    // Pago normal
        pago = pago + (h_trabajadas - 40) * 1.5f * pxh; // Pago horas extras
    }
    else{
        pago = h_trabajadas * pxh;  // Pago normal
    }

    printf("\n Salario en bruto: $%.2f",pago);

    if(pago > 5000){
        pago = pago * (1 - 0.10);   // Impuesto del 10%
    }
    else{
        pago = pago * (1 - 0.05);    // Impuesto del 5%
    }

    printf("\n Esta semana cobras: $%.2f",pago);

    return 0;
}