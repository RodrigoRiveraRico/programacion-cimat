#include <stdio.h>
#include <windows.h>
#include <string.h>

#define PASSWORD_LENGTH 20
#define SAVED_PASSWORD "Pa$$w0rD"

int GetCh(void){

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInputRecord;
    DWORD dwEventsRead;

    while(ReadConsoleInputA(hStdin, &irInputRecord, 1, &dwEventsRead)) {

        if (irInputRecord.EventType == KEY_EVENT &&
            irInputRecord.Event.KeyEvent.bKeyDown) {

            WORD key = irInputRecord.Event.KeyEvent.wVirtualKeyCode;

            if (key == VK_SHIFT || key == VK_MENU || key == VK_CONTROL)
                continue;

            return irInputRecord.Event.KeyEvent.uChar.AsciiChar;
        }
    }

    return EOF;
}

int main(void){

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    FlushConsoleInputBuffer(hStdin);            // Limpiar eventos pendientes en la consola

    int c;
    char password_array[PASSWORD_LENGTH + 1];   // Longitud de la contraseña + '\0'
    int i = 0;                                  // Password índice

    while((c = GetCh()) != 13 && c != EOF) {    // 13 es el código ASCII para Enter en Windows

        if(i < PASSWORD_LENGTH){                // Password de longitud máxima fija.

            if (c == 8) {                       // 8 es el código ASCII para Backspace en Windows
                printf("\b \b");                // Imprime retroceso, espacio (para borrar el asterisco) y otro retroceso
                
                if(i==0) {
                    continue;                   // No es válido tener índices negativos
                } else{
                    i--;
                }

            } else if (c != 0) {                // c != 0 Para evitar imprimir asteriscos cuando se presionan teclas que no generan un carácter ASCII. Ejemplo: flechas up, down, left, right.
                printf("*");                    // Si es cualquier otro carácter, imprime el asterisco
                password_array[i] = c;          // Guardamos el carácter
                i++;                            // Avanzamos índice
            }

            fflush(stdout);                     // Forzar la actualización visual en la terminal

        } else{                                 // Se alcanzó la longitud máxima del password

            if(c == 8){                         // Solo se permite Backspace
                printf("\b \b");
                i--;
            }

            fflush(stdout);
        }
    }

    password_array[i] = '\0';                   // Final del password

    if (strcmp(SAVED_PASSWORD, password_array) == 0) {
        printf("\nCorrect Password :D\nWelcome!");
    } else {
        printf("\nIncorrect Password >:(\nBye!");
    }

    return 0;
}