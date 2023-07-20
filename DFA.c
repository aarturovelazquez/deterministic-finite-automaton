#include <stdlib.h>
#include <stdio.h>
#include<string.h>  
#include <stdbool.h>
#include <cstring>

//declarations

void traduccion();
void validacion();
bool spanishPlz(char input[]);
bool EstadoDuplicado(char input[],char estados[]);


int main() {
    int selection;
    
    printf("1. AFD Traduccion \n");
    printf("2. AFD Validacion \n");
    printf("3. Salir \n");
    scanf("%d", &selection);
    while (selection !=3)
    {
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

    }
    }
    
   

}

void traduccion() {
    system("cls"); //to clear the terminal screen so it looks cleaner. This does not take effect in visual studio codde
    printf("Capture el alfabeto de entrada \n");
    char entryalphabet;
    scanf("%s", &entryalphabet);

    printf("Capture el alfabeto de salida: \n");  
    char exitalphabet;
    scanf("%s", &exitalphabet);

    printf("Registre el cojunto de estados Q: \n");
    char estados;
    scanf("%s", &estados); 

    printf("Registe el conjunto de estados A:");  
    char estadoA;
    scanf("%s", &estadoA); 

    printf("Registe el estado inicial q0");
    char estadoQ0;
    scanf("%s", &estadoQ0); 

}

void validacion(){
    system("cls");
    int i = 0;
    char input[20];


    //Capturar el alfabeto
    char entryalphabet[20][20]; 
    while (1)
    {
        system("cls");

        // if (spanishPlz(input)) {
        //     printf("Error, el simbolo ingresado no pertenece al español");  
        // }

        if (0<i)
        {
        printf("Alfabeto de entrada: \n");
            for (int x = 0; x < i; x++)
            {
                 printf("%s \n",entryalphabet[x]);
            }
        }
            
        printf("Capture el alfabeto de entrada \n");
        scanf("%s", &input);

        if (strcmp(input,"S") == 0)
            break;

    if (!spanishPlz(input)) {
            strcpy(entryalphabet[i], input);
            i++;      
        }
    }

  //Capturar estados
    char estados[15][20]; //rows and columns
    i = 0;
    while(true)
    {
        // system("cls");

        if (i>0)
        {
            printf("Conjunto de estados: \n");
            for (int x = 0; x < i; x++)
            {
                 printf("%s ",estados[x], " ");
            }
            printf("\n");
        }

        
        printf("Registre el cojunto de estados Q: \n");
        scanf("%s", &input);

        if (strcmp(input, "S") == 0 && i > 0 or strcmp(input, "s") == 0 && i > 0 ) {
            break;
        }
        else if (strcmp(input, "S") == 0 && i == 0 or strcmp(input, "s") == 0 && i == 0)
        {
            printf("Error, debe de haber por al menos un conjunto de estados \n");
        }       
        else{
            //validation that the state doesn't exist
            strcpy(estados[i],input);
            i++;
        }  
    }

    printf("Registe el conjunto de estados A:");  
    char estadoA;
    scanf("%s", &estadoA); 

    printf("Registe el estado inicial q0");
    char estadoQ0;
    scanf("%s", &estadoQ0);

    //funcion de transicion


}

bool spanishPlz(char input[]){
       // Array of all possible characters in the Spanish language
    char spanish_characters[] = "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "áéíóúÁÉÍÓÚ"
                                "ñÑ"
                                "üÜ"
                                "0123456789";

    for (int i = 0; input[i] != '\0'; i++) {
        bool found = false;
        for (int j = 0; spanish_characters[j] != '\0'; j++) {
            if (input[i] == spanish_characters[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return true; // Return true if any character is not from the Spanish language
        }
    }
    return false; // Return false if all characters are from the Spanish language
}

// bool EstadoDuplicado(char input[], char estados[][20]) {
//     int result;
//     bool duplicate = false;
//     for (int i = 0; estados[i] != '\0'; i++) {
//         printf("El estado actual es %s",estados[i], "\n");
//         result = strcmp(estados + i, input); // Use estados + i to get the address of the current substring
//         if (result == 1) {
//             duplicate = true;
//             break;
//         }
//     }
//     printf("%d",result, "\n");
//     return duplicate;
// }


 

