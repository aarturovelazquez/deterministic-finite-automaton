#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Estructura de la linked list del alfabeto de entrada
struct simbolo_entrada {
    char simbolo;
    struct simbolo_entrada* next;
};

// Funcion para crear un nuevo simbolo
struct simbolo_entrada* crearSimbolo(char simbolo) {
    struct simbolo_entrada* nuevoSimbolo = (struct simbolo_entrada*)malloc(sizeof(struct simbolo_entrada));
    nuevoSimbolo->simbolo = simbolo;
    nuevoSimbolo->next = NULL;
    return nuevoSimbolo;
}

// Funcion para imprimir la lista
void imprimirLista(struct simbolo_entrada* head) {
    struct simbolo_entrada* current = head;
    while (current != NULL) {
        printf("%c ", current->simbolo);
        current = current->next;
    }
    printf("\n");
}

// Funcion para verificar que el simbolo exista en la linked list
int simboloExiste(struct simbolo_entrada* head, char simbolo) {
    struct simbolo_entrada* current = head;
    while (current != NULL) {
        if (current->simbolo == simbolo) {
            return 1; // Symbol already exists in the list
        }
        current = current->next;
    }
    return 0; // Symbol does not exist in the list
}

//Funcion para revisar si los caracters son validos
int esSimboloValido(char simbolo) {
    char spanish_characters[] = "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "áéíóúÁÉÍÓÚ"
                                "ñÑ"
                                "üÜ"
                                "0123456789";

    for (int i = 0; i < strlen(spanish_characters); i++) {
        if (simbolo == spanish_characters[i]) {
            return 1; // Symbol is valid
        }
    }

    return 0; // Symbol is not valid
}



// Function para insertar un simbolo en la lista ligada
void insertarSimbolo(struct simbolo_entrada** head, char simbolo) {
    if (esSimboloValido(simbolo)) {
        printf("Character %c is a valid symbol.\n", simbolo);

        if (!simboloExiste(*head, simbolo)) {
            printf("Character %c does not exist in the list. Inserting...\n", simbolo);
            struct simbolo_entrada* nuevoSimbolo = crearSimbolo(simbolo);

            if (*head == NULL) {
                *head = nuevoSimbolo;
            } else {
                struct simbolo_entrada* current = *head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = nuevoSimbolo;
            }
        } else {
            printf("Character %c already exists in the list. Skipping...\n", simbolo);
        }
    } else {
        printf("Character %c is not a valid symbol. Skipping...\n", simbolo);
    }
}

// Estructura del los conjuntos de estado
struct conjunto_estados {
    char estado[20];
    struct conjunto_estados* next;
};

// Funcion para crear un nuevo conjunto de estado
struct conjunto_estados* crearEstado(char estado[20]) {
    struct conjunto_estados* nuevoEstado = (struct conjunto_estados*)malloc(sizeof(struct conjunto_estados));
    strncpy(nuevoEstado->estado, estado, sizeof(nuevoEstado->estado) - 1); // Use strncpy to copy the string correctly
    nuevoEstado->next = NULL;
    return nuevoEstado;
}

// Function to check if the state already exists in the linked list
int estadoExiste(struct conjunto_estados* head, char estado[20]) {
    struct conjunto_estados* current = head;
    while (current != NULL) {
        if (strcmp(current->estado, estado) == 0) {
            printf("Error, estado ya existe");
            return 1; // State already exists in the list
        }
        current = current->next;
    }
    return 0; // State does not exist in the list
}

void insertarEstado(struct conjunto_estados** head, char estado[20]) {
    if (!estadoExiste(*head, estado)) {
        struct conjunto_estados* nuevoEstado = crearEstado(estado);

        if (*head == NULL) {
            *head = nuevoEstado;
        } else {
            struct conjunto_estados* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = nuevoEstado;
        }
    }
}

struct conjunto_estados* buscarEstado(struct conjunto_estados* head, char estado[20]) {
    struct conjunto_estados* current = head;
    while (current != NULL) {
        if (strcmp(current->estado, estado) == 0) {
            return current; // Return the pointer to the matching state
        }
        current = current->next;
    }
    return NULL; // Return NULL if the state is not found in the list
}

struct conjunto_estados* seleccionarEstadoInicial(struct conjunto_estados* head) {
    char input[20]; // Assuming that the input state will have at most 20 characters

    printf("Seleccione el estado inicial (q0) de la lista de estados:\n");

    while (1) {
        printf("Estado seleccionado: ");
        fgets(input, sizeof(input), stdin);

        // Remove the newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Find the selected state in the linked list
        struct conjunto_estados* selectedState = buscarEstado(head, input);

        // Check if the selected state exists in the linked list
        if (selectedState != NULL) {
            return selectedState; // Return the pointer to the selected state
        } else {
            printf("El estado seleccionado no existe en la lista de estados. Intente nuevamente.\n");
        }
    }
}




// Declarations
void validacion();

// Global Variables
struct estatisticas {
    int palabras_validas;
    int palabras_invalidas;
    int palabras_traducidas;
    int total_DFA;
};

int main() {
    int selection;
    printf("1. AFD Traduccion \n");
    printf("2. AFD Validacion \n");
    printf("3. Salir \n");
    scanf("%d", &selection);
    while (selection != 3) {
        switch (selection) {
            case 1:
                // Add the code for AFD Traduccion here
                break;

            case 2:
                validacion();
                break;

            case 3:
                return 0;
        }
    }
}


void validacion() {

    system("cls");
    char input[100]; // Assuming that the input will have at most 100 characters
    struct simbolo_entrada* headAlfabetoEntrada = NULL;
    struct conjunto_estados* estadoshead = NULL;

    int inputEntered = 0; // Variable to track whether input has been entered

    while (!inputEntered) { // Loop until input is entered
        printf("Ingresa los simbolos del alfabeto de entrada separados por espacios: ");
        fgets(input, sizeof(input), stdin);

        // Check if input has been entered
        if (strlen(input) > 1) {
            inputEntered = 1; // Set the flag to break the loop
        } else {
            printf("No se ha ingresado ningun caracter. Intentalo nuevamente.\n");
        }
    }

    // Remove the newline character from the input
    input[strcspn(input, "\n")] = '\0';

    // Tokenize the input to extract symbols and store them in the linked list
    char* token = strtok(input, " ");
    
    while (token != NULL) {
        insertarSimbolo(&headAlfabetoEntrada, token[0]);
        token = strtok(NULL, " ");
    }

    system("cls");

    printf("Alfabeto de entrada: ");
    imprimirLista(headAlfabetoEntrada);

    //Estados

    while (1) { 

        if (estadoshead != NULL)
        {
            
            printf("Alfabeto de entrada: ");
            imprimirLista(headAlfabetoEntrada);

            printf("Conjunto de estados ingresados:\n");
            struct conjunto_estados* current = estadoshead;
            while (current != NULL) {
                printf("%s|", current->estado); 
            current = current->next;
            }
            printf("\n");
        }

        printf("Inserte el conjunto de estados. Para salir, ingrese S o s: ");
        fgets(input, sizeof(input), stdin);

        // Remove the newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Check if input has been entered
        if (strlen(input) > 0) {
            // Check if the entered character is 's' or 'S'
            if (input[0] == 's' || input[0] == 'S') {
                break; // Exit the loop if 's' or 'S' is entered
            } else {
                // Insert the entered state into the linked list
                insertarEstado(&estadoshead, input);
                system("cls");
            }
        } else {
            printf("No se ha ingresado ningun estado. Intentalo nuevamente.\n");
        }

    }

    printf("Alfabeto de entrada: ");
    imprimirLista(headAlfabetoEntrada);

    printf("Conjunto de estados ingresados:\n");
    struct conjunto_estados* current = estadoshead;
    while (current != NULL) {
        printf("%s|", current->estado); 
    current = current->next;
    }
    printf("\n");
    struct conjunto_estados* q0 = seleccionarEstadoInicial(estadoshead);
    printf("Estado inicial seleccionado (q0): %s\n", q0->estado);
        
    
}
