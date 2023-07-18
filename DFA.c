#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
    int selection;
    
    printf("1. AFD Traduccion \n");
    printf("2. AFD Validacion \n");
    printf("3. Salir \n");
    scanf("%d", &selection);
    switch (selection)
    {
    case 1:
        traduccion();
        break;

    case 2:
        break;

    case 3:
        return 0;
    
    default:
        printf("Intenta otra vez");
    }
    return 0;

}

void traduccion() {
    printf("Capture el alfabeto de entrada \n");
    char alfabeto_entrada[15][20];
    char input;
    int i=0;

    while (input != 'S')
    {   
        scanf("%c",&input);
        alfabeto_entrada[i][20] = input;
        i++;
    }      
}
