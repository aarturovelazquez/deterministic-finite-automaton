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
        validacion();
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

    while (input != "\n")
    {
        scanf("%c",&input);
        alfabeto_entrada[20][i] = input;
    }
    

       
}

void validacion(){
    
}

//char validCharacters[] = {'a', 'á', 'A', 'Á', 'b', 'c', 'd', 'e', 'é', 'E', 'É', 'f', 'g', 'h', 'i', 'í', 'I', 'Í', 'j', 'k', 'l', 'm', 'n', 'ñ', 'N', 'Ñ', 'o', 'ó', 'O', 'Ó', 'p', 'q', 'r', 's', 't', 'u', 'ú', 'U', 'Ú', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
