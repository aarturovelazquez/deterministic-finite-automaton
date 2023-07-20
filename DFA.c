#include <stdlib.h>
#include <stdio.h>
#include<string.h>  
#include <stdbool.h>
#include <cstring>

//declarations

void traduccion();
void validacion();
bool spanishPlz(char input[]);
bool EstadoDuplicado(const char input[], const char estados[][20], int size);


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
            system("cls");

    if (!spanishPlz(input)) {
            strcpy(entryalphabet[i], input);
            i++;      
        }
    }

  //Capturar estados
    char estados[15][20]; //rows and columns
    int size = 0;
    while(true)
    {
        // system("cls");

        if (size>0)
        {
            printf("Conjunto de estados: \n");
            for (int x = 0; x < size; x++)
            {
                 printf("%s ",estados[x], " ");
            }
            printf("\n");
        }

        
        printf("Registre el cojunto de estados Q: \n");
        scanf("%s", &input);

        if (strcmp(input, "S") == 0 && size > 0 or strcmp(input, "s") == 0 && size > 0 ) {
            break;
            system("cls");
        }
        else if (strcmp(input, "S") == 0 && size == 0 or strcmp(input, "s") == 0 && size == 0)
        {
            printf("Error, debe de haber por al menos un conjunto de estados \n");
        }       
        else{
            bool isDuplicate = EstadoDuplicado(input, estados, size);
            if (isDuplicate == true)
            {
                printf("Error, el estado ya existe \n");
            }
            else{
                strcpy(estados[size],input);
                size++;
            }
        
        }  
    }

    //Estados conjunto A 
    char estadoA[20][20];
    while (true)
    {
        printf("Registe el conjunto de estados A:"); 
        scanf("%s", &estadoA);
                    bool isDuplicate = EstadoDuplicado(input, estados, size);
            if (isDuplicate == true)
            {
                printf("Error, el estado ya existe \n");
            }
            else{
                strcpy(estados[size],input);
                size++;
            }

    }
     

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


bool EstadoDuplicado(const char input[], const char estados[][20], int size) {
    int result;
    bool duplicate = false;
    for (int i = 0; i < size; i++) {
        result = strcmp(estados[i], input);
        if (result == 0) {
            duplicate = true;
            break;
        }
    }
    return duplicate;
}


 

