#include <stdio.h>

#define FOCO_PRENDIDO 1
#define AUTO_EN_COCHERA 2
#define ALARMA_ACTIVADA 4
#define PUERTA_CERRADA 8
#define PERRO_SUELTO 16
#define VENTANA_CERRADA 32
#define TINACO_DE_AGUA_LLENO 64
#define HAY_LUZ_ELECTRICA 128
#define REFRIGERADOR_CONECTADO 256

#define SALTO printf("\n")

// Los estados válidos son enteros tales que 0 <= s < 512
void state(unsigned s);

int main(void){

    unsigned estado;
    scanf("%u",&estado);
    state(estado);

    return 0;
}

void state(unsigned s){
    
    unsigned bits = s;

    SALTO;
    printf(s & FOCO_PRENDIDO ? "foco_prendido : SI" : "foco_prendido : NO"); SALTO;
    printf(s & AUTO_EN_COCHERA ? "auto_en_cochera : SI" : "auto_en_cochera : NO"); SALTO;
    printf(s & ALARMA_ACTIVADA ? "alarma_activada : SI" : "alarma_activada : NO"); SALTO;
    printf(s & PUERTA_CERRADA ? "puerta_cerrada : SI" : "puerta_cerrada : NO"); SALTO;
    printf(s & PERRO_SUELTO ? "perro_suelto : SI" : "perro_suelto : NO"); SALTO;
    printf(s & VENTANA_CERRADA ? "ventana_cerrada : SI" : "ventana_cerrada : NO"); SALTO;
    printf(s & TINACO_DE_AGUA_LLENO ? "tinaco_de_agua_lleno : SI" : "tinaco_de_agua_lleno : NO"); SALTO;
    printf(s & HAY_LUZ_ELECTRICA ? "hay_luz_electrica : SI" : "hay_luz_electrica : NO"); SALTO;
    printf(s & REFRIGERADOR_CONECTADO ? "refrigerador_conectado : SI" : "refrigerador_conectado : NO"); SALTO;


}