#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <locale.h>
#include <windows.h>
#include <conio.h> // Include the _getch() function




BOOL CtrlHandler(DWORD fdwCtrlType) {
    switch (fdwCtrlType) {
        // Handle the Ctrl+C signal
        case CTRL_C_EVENT:
            return TRUE; // Return TRUE to indicate that the signal has been handled
        default:
            return FALSE;
    }
}


struct estadisticas {
    int palabras_registradas;
    int palabras_validas;
    int palabras_invalidas;
    int palabras_traducidas;
};

struct estadisticas_globales {
    int palabras_registradas;
    int palabras_validas;
    int palabras_invalidas;
    int palabras_traducidas;
    int AFD_registrados;
};

//Funcion para imprimir el encabezado
void encabezado(){
    time_t t;   
    time(&t);
    printf("Desarollado por Arturo Velazquez \n");
    printf("%s", ctime(&t));
    printf("Metodos Formales");
    printf("\n \n");
}

int esValidoAlfabeto(const char* str) {
    const char* valid_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZñÑáéíóúÁÉÍÓÚüÜ0123456789";
    for (int i = 0; str[i] != '\0'; i++) {
        if (strchr(valid_characters, str[i]) == NULL) {
            return 0; // Invalid character found
        }
    }
    return 1; // All characters are valid
}


// Alfabeto de entrada
struct simbolo_entrada {
    wchar_t simbolo;
    struct simbolo_entrada* next; //Apunta al siguente simoblo en la lista ligada
};

// Funcion para crear un nuevo simbolo
struct simbolo_entrada* crearSimbolo(wchar_t simbolo) {
    struct simbolo_entrada* nuevoSimbolo = (struct simbolo_entrada*)malloc(sizeof(struct simbolo_entrada));
    nuevoSimbolo->simbolo = simbolo;
    nuevoSimbolo->next = NULL;
    return nuevoSimbolo;
}

// Funcion para imprimir la lista
void imprimirLista(struct simbolo_entrada* head) {
    struct simbolo_entrada* current = head;
    while (current != NULL) {
        wprintf(L"%lc ", current->simbolo);
        current = current->next;
    }
    wprintf(L"\n");
}

// Funcion para verificar que el simbolo exista en la linked list
int simboloExiste(struct simbolo_entrada* head, wchar_t simbolo) {
    struct simbolo_entrada* current = head;
    while (current != NULL) {
        if (current->simbolo == simbolo) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

//Funcion para revisar si los caracters son validos
int esSimboloValido(wchar_t simbolo) {
    wchar_t spanish_characters[] = L"abcdefghijklmnopqrstuvwxyz"
                                   L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   L"áéíóúÁÉÍÓÚ"
                                   L"ñÑ"
                                   L"üÜ"
                                   L"0123456789";

    for (int i = 0; i < wcslen(spanish_characters); i++) {
        if (simbolo == spanish_characters[i]) {
            return 1;
        }
    }

    return 0;
}


// Function para insertar un simbolo en la lista ligada
void insertarSimbolo(struct simbolo_entrada** head, wchar_t simbolo) {
    if (esSimboloValido(simbolo)) {

        if (!simboloExiste(*head, simbolo)) {
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
            // Debug print to check the symbol being stored
            printf("Stored symbol: %c\n", simbolo);
        }
    } 
}

//Simbolo Salida

struct simbolo_salida {
    char simbolo;
    struct simbolo_salida* next;
};

// Funcion para crear un nuevo simbolo de salida
struct simbolo_salida* crearSimboloSalida(char simbolo) {
    struct simbolo_salida* nuevoSimboloSalida = (struct simbolo_salida*)malloc(sizeof(struct simbolo_salida));
    nuevoSimboloSalida->simbolo = simbolo;
    nuevoSimboloSalida->next = NULL;
    return nuevoSimboloSalida;
}

// Funcion para imprimir la lista de salida
void imprimirListaSalida(struct simbolo_salida* head) {
    struct simbolo_salida* current = head;
    while (current != NULL) {
        printf("%c ", current->simbolo);
        current = current->next;
    }
    printf("\n");
}

// Funcion para verificar que el simbolo de salida exista en la linked list
int simboloSalidaExiste(struct simbolo_salida* head, char simbolo) {
    struct simbolo_salida* current = head;
    while (current != NULL) {
        if (current->simbolo == simbolo) {
            return 1; 
        }
        current = current->next;
    }
    return 0;
}

// //Funcion para revisar si los caracteres de salida son validos
// int esSimboloSalidaValido(char simbolo) {
//     char spanish_characters[] = "abcdefghijklmnopqrstuvwxyz"
//                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//                                 "0123456789";

//     for (int i = 0; i < strlen(spanish_characters); i++) {
//         if (simbolo == spanish_characters[i]) {
//             return 1;
//         }
//     }

//     return 0;
// }

// Function para insertar un simbolo de salida en la lista ligada
void insertarSimboloSalida(struct simbolo_salida** head, char simbolo) {
    if (esSimboloValido(simbolo)) {

        if (!simboloSalidaExiste(*head, simbolo)) {
            struct simbolo_salida* nuevoSimboloSalida = crearSimboloSalida(simbolo);

            if (*head == NULL) {
                *head = nuevoSimboloSalida;
            } else {
                struct simbolo_salida* current = *head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = nuevoSimboloSalida;
            }
        }
    } 
}


// Estructura del los conjuntos de estado
struct conjunto_estados {
    char estado[20];
    struct conjunto_estados* next;
    bool isFinal;
};

// Funcion para crear un nuevo conjunto de estado
struct conjunto_estados* crearEstado(char estado[20]) {
    struct conjunto_estados* nuevoEstado = (struct conjunto_estados*)malloc(sizeof(struct conjunto_estados));
    strncpy(nuevoEstado->estado, estado, sizeof(nuevoEstado->estado) - 1); // Use strncpy to copy the string correctly
    nuevoEstado->next = NULL;
    return nuevoEstado;
}

// Funcion para ver si el estado ya existe
int estadoExiste(struct conjunto_estados* head, char estado[20]) {
    struct conjunto_estados* current = head;
    while (current != NULL) {
        if (strcmp(current->estado, estado) == 0) {
            printf("Error, estado ya existe");
            return 1;
        }
        current = current->next;
    }
    return 0;
}

//Funcion para insertar el estado
void insertarEstado(struct conjunto_estados** head, const char* estado) {
    // Check if the state is not longer than 15 characters and does not have spaces
    if (strlen(estado) > 15 || strchr(estado, ' ') != NULL) {
        system("cls");
        encabezado();
        printf("Error: El estado no puede ser mayor a 15 caracteres o contener espacios. Intente nuevamente.\n");
        return;
    }

    // Check if the state contains valid characters from the Spanish alphabet
    if (!esValidoAlfabeto(estado)) {
        system("cls");
        encabezado();
        printf("Error: El estado contiene caracteres no validos. Intente nuevamente.\n");
        return;
    }

    // Create a new state node
    struct conjunto_estados* nuevoEstado = (struct conjunto_estados*)malloc(sizeof(struct conjunto_estados));
    strcpy(nuevoEstado->estado, estado);
    nuevoEstado->isFinal = 0;
    nuevoEstado->next = NULL;

    // Insert the state node into the linked list
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

void imprmirEstados(struct conjunto_estados* estadoshead){
    struct conjunto_estados* current = estadoshead;
    while (current != NULL) {
        printf("%s|", current->estado); 
    current = current->next;
    }
    printf("\n");
}



struct conjunto_estados* buscarEstado(struct conjunto_estados* head, char estado[20]) {
    struct conjunto_estados* current = head;
    while (current != NULL) {
        if (strcmp(current->estado, estado) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct conjunto_estados* seleccionarEstadoInicial(struct conjunto_estados* head) {
    char input[20];

    printf("Seleccione el estado inicial (q0) de la lista de estados:\n");

    while (1) {
        
        printf("Estado seleccionado: ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        struct conjunto_estados* selectedState = buscarEstado(head, input);

        if (selectedState != NULL) {
            return selectedState;
        } else {
            system("cls");
            encabezado();
            printf("El estado seleccionado no existe en la lista de estados. Intente nuevamente.\n");
        }
    }
}

struct transicion {
    char estado_actual[15];
    char simbolo;
    char estado_siguiente[15];
    struct transicion* next;
};

void insertarTransicion(struct transicion** head, char estado_actual[15], char simbolo, char estado_siguiente[15]) {
    struct transicion* nuevaTransicion = (struct transicion*)malloc(sizeof(struct transicion));
    strncpy(nuevaTransicion->estado_actual, estado_actual, sizeof(nuevaTransicion->estado_actual) - 1);
    nuevaTransicion->simbolo = simbolo;
    strncpy(nuevaTransicion->estado_siguiente, estado_siguiente, sizeof(nuevaTransicion->estado_siguiente) - 1);
    nuevaTransicion->next = NULL;

    if (*head == NULL) {
        *head = nuevaTransicion;
    } else {
        struct transicion* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = nuevaTransicion;
    }
}

int validarPalabra(struct transicion* transiciones_head, struct conjunto_estados* q0, struct conjunto_estados* estadoshead, char* palabra) {
    
    struct conjunto_estados* estado_actual = q0;


    for (int i = 0; i < strlen(palabra); i++) {
        char simbolo = palabra[i];

        
        struct transicion* current_transicion = transiciones_head;
        while (current_transicion != NULL) {
            if (strcmp(current_transicion->estado_actual, estado_actual->estado) == 0 && current_transicion->simbolo == simbolo) {

                struct conjunto_estados* estado_siguiente = buscarEstado(estadoshead, current_transicion->estado_siguiente);
                if (estado_siguiente != NULL) {
                    estado_actual = estado_siguiente;
                } else {
                    
                    return 0;
                }
                break;
            }
            current_transicion = current_transicion->next;
        }

        if (current_transicion == NULL) {
            return 0;
        }

    }

    if (estado_actual->isFinal) {
        return 1;
    } else {
        return 0;
    }
}


int validarPalabraAlfabeto(struct simbolo_entrada* headAlfabeto, char* palabra) {
    for (int i = 0; i < strlen(palabra); i++) {
        char simbolo = palabra[i];
        if (!simboloExiste(headAlfabeto, simbolo)) {
            return 0;
        }
    }
    return 1; 
}

//Traduccion

// Estructura de las traducciones de simbolos
struct traduccion_simbolo {
    char simbolo_entrada;
    char estado_actual[15];
    char estado_siguiente[15];
    char simbolo_salida;
    struct traduccion_simbolo* next;
};


// Funcion para crear una nueva traduccion
struct traduccion_simbolo* crearTraduccion(char simbolo_entrada, char estado_actual[15], char simbolo_salida) {
    struct traduccion_simbolo* nuevaTraduccion = (struct traduccion_simbolo*)malloc(sizeof(struct traduccion_simbolo));
    nuevaTraduccion->simbolo_entrada = simbolo_entrada;
    strncpy(nuevaTraduccion->estado_actual, estado_actual, sizeof(nuevaTraduccion->estado_actual) - 1);
    nuevaTraduccion->simbolo_salida = simbolo_salida;
    nuevaTraduccion->next = NULL;
    return nuevaTraduccion;
}

// Funcion para insertar una traduccion en la lista ligada
void insertarTraduccion(struct traduccion_simbolo** head, char simbolo_entrada, char estado_actual[15], char simbolo_salida) {
    struct traduccion_simbolo* nuevaTraduccion = crearTraduccion(simbolo_entrada, estado_actual, simbolo_salida);

    if (*head == NULL) {
        *head = nuevaTraduccion;
    } else {
        struct traduccion_simbolo* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = nuevaTraduccion;
    }
}

char traducirSimbolo(struct traduccion_simbolo* head, char simbolo_entrada) {
    struct traduccion_simbolo* current = head;
    while (current != NULL) {
        if (current->simbolo_entrada == simbolo_entrada) {
            return current->simbolo_salida;
        }
        current = current->next;
    }
    return simbolo_entrada;
}

// Function to check if the symbol is part of the exit alphabet
bool isValidExitSymbol(char symbol, struct simbolo_salida* headExitAlphabet) {
    struct simbolo_salida* current = headExitAlphabet;
    while (current != NULL) {
        if (current->simbolo == symbol) {
            return true; // Symbol is part of the exit alphabet
        }
        current = current->next;
    }
    return false; // Symbol is not part of the exit alphabet
}

char getValidCharacterInput() {
    char ch;
    while (1) {
        ch = _getch();
        if (ch == 0 || ch == -32) {
            // Special key detected (e.g., arrow keys, function keys)
            _getch(); // Consume the second character of the special key
        } else if (ch == 3 || ch == 18) {
            // Ctrl+C (3) and Alt+F4 (18) detected
        } else {
            return ch; // Valid character input received
        }
    }
}



// Declaraciones
void validacion();
void traduccion();

struct estadisticas_globales estadisticas_globales = {0,0,0,0,0};


int main() {
    // if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE)) {
    //     printf("Error setting control handler.\n");
    //     return 1;
    // }
    
    system("cls");
    encabezado();
    while (1) {
    int selection;
    while (1) {

        char c;
        printf("1. AFD Traduccion\n");
        printf("2. AFD Validacion\n");
        printf("3. Salir\n");
        printf("Selecciona una opcion: ");
        selection = getValidCharacterInput() - '0'; // Convert char to integer
        switch (selection) {
            case 1:
                traduccion();
                break;

            case 2:
                validacion();
                break;

            case 3:
                system("cls");
                encabezado();
                
                while ((c = getchar()) != '\n' && c != EOF);
                printf("\n\nEstadisticas:\n\n");
                printf("Palabras registradas: %d\n", estadisticas_globales.palabras_registradas);
                printf("Palabras validas: %d\n", estadisticas_globales.palabras_validas);
                printf("Palabras invalidas: %d\n", estadisticas_globales.palabras_invalidas);
                printf("Palabras traducidas: %d\n", estadisticas_globales.palabras_traducidas);
                printf("AFD registrados: %d\n", estadisticas_globales.AFD_registrados);
                printf("Gracias por usar el programa. I had the time of my life fighting dragons with you. Hasta luego.\n\n");
                printf("Presiona enter para continuar \n");
                while ((c = getchar()) != '\n' && c != EOF);
                break;

            default:
                system("cls");
                encabezado();
                printf("ERROR: Opcion no valida. Favor de seleccionar una opcion valida.\n \n");
        }
        if (selection==3){
                return 0;
        }
    }
    

    }
}



void validacion() {
    struct estadisticas estadisticas = {0, 0, 0, 0};
    int c;
    char input[100];
    struct simbolo_entrada* headAlfabetoEntrada = NULL;
    struct conjunto_estados* estadoshead = NULL;
    int inputEntered = 0;

    system("cls");
    encabezado();

    //Alfabeto
    while (!inputEntered) { 

        printf("Ingresa los simbolos del alfabeto de entrada separados por espacios: ");
        fgets(input, sizeof(input), stdin);

        // Revisar que no este vacio
        if (!isspace(input[0])) {
            inputEntered = 1;
        } else {
            system("cls");
            encabezado();
            printf("ERROR: No se ha ingresado ningun caracter. Presiona Enter para intentarlo nuevamente.\n");
        }
    }

    // Quitar la nueva linea
    input[strcspn(input, "\n")] = '\0';

    char* token = strtok(input, " ");
    
    while (token != NULL) {
        insertarSimbolo(&headAlfabetoEntrada, token[0]);
        token = strtok(NULL, " ");
    }

    system("cls");
    encabezado();
    
    //Estados
    while (1) {
        printf("Alfabeto de entrada: ");
        imprimirLista(headAlfabetoEntrada);

        if (estadoshead != NULL) {
            printf("Conjunto de estados ingresados:\n");
            struct conjunto_estados* current = estadoshead;
            while (current != NULL) {
                printf("%s|", current->estado);
                current = current->next;
            }
            printf("\n");
        }

        printf("Inserte el conjunto de estados. Debe de ser maximo 15 caracteres y no puede tener espacios. Ingrese el simbolo y despues presione enter. Para salir, ingrese S o s: ");
        fgets(input, sizeof(input), stdin);

            input[strcspn(input, "\n")] = '\0';

            if (strlen(input) > 0) {
                if (input[0] == 's' || input[0] == 'S') { //
                    break; 
                } else {
                    int len = strlen(input);
                    bool hasNonWhitespace = false;
                    for (int i = 0; i < len; i++) {
                        if (!isspace(input[i])) {
                            hasNonWhitespace = true;
                            break;
                        }
                    }

                    if (hasNonWhitespace) {
                        insertarEstado(&estadoshead, input);
                        system("cls");
                        encabezado();
                    } else {
                        system("cls");
                        encabezado();
                        printf("ERROR: No se ha ingresado ningun estado o se ha ingresado solo espacios. Intentalo nuevamente. Presiona enter\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                }
            } else {
                system("cls");
                encabezado();
                printf("ERROR: No se ha ingresado ningun estado o se ha ingresado solo espacios. Intentalo nuevamente. Presiona enter\n");
                while ((c = getchar()) != '\n' && c != EOF);
            }
    }


    //Estado q0
    system("cls");
    encabezado();
    struct conjunto_estados* q0 = NULL;
    while (q0 == NULL) {
        q0 = seleccionarEstadoInicial(estadoshead);
        if (q0 == NULL) {
            system("cls");
            printf("ERROR: El estado inicial (q0) no puede estar vacio. Por favor, selecciona un estado inicial valido.\n");
            encabezado();
        } else {
            printf("Estado inicial seleccionado (q0): %s\n", q0->estado);
        }
    }

    system("cls");
    encabezado();
    // Estados de aceptacion
    while (1) {
        
        int show;
        struct conjunto_estados* current = estadoshead;

        if (show==1)
        {
            printf("Conjunto de estados de aceptacion ingresados: ");
            current = estadoshead;
            while (current != NULL) {
                if (current->isFinal) {
                    printf("%s|", current->estado);
                }
                printf("\n");
                current = current->next;
            }
        }
        
        printf("Inserte los estados de aceptacion. Para finalizar, ingrese S o s:\n");
        char input[20];

        printf("Estado final: ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "S") == 0 || strcmp(input, "s") == 0) {
            break;
        }

        current = estadoshead;
        while (current != NULL) {
            if (strcmp(current->estado, input) == 0) {
                current->isFinal = true;
                show = 1;
                break;
                
            }
            current = current->next;
        }

        if (current == NULL) {
            system("cls");
            encabezado();
            printf("ERROR: El estado final '%s' no existe en la lista de estados. Entrada negada.\n", input);
            while ((c = getchar()) != '\n' && c != EOF);
        }

    }
  
    //Funcion de transicion
    system("cls");
    encabezado();
    struct transicion* transiciones_head = NULL;
    struct simbolo_entrada* current_symbol = headAlfabetoEntrada;
    struct conjunto_estados* current_state = estadoshead;

    while (current_symbol != NULL) {
        char simbolo = current_symbol->simbolo;

        current_state = estadoshead;

        while (current_state != NULL) {
            char estado_siguiente[20];

            printf("Ingrese el estado siguiente para el simbolo '%c' y el estado '%s':\n", simbolo, current_state->estado);

            printf("Estado siguiente: ");
            fgets(estado_siguiente, sizeof(estado_siguiente), stdin);
            estado_siguiente[strcspn(estado_siguiente, "\n")] = '\0';

            if (!buscarEstado(estadoshead, estado_siguiente)) {
                printf("ERROR: El estado siguiente '%s' no existe en la lista de estados. Intente nuevamente.\n", estado_siguiente);
                system("cls");
                encabezado();
                continue;
            }

            insertarTransicion(&transiciones_head, current_state->estado, simbolo, estado_siguiente);
            system("cls");
            encabezado();

            current_state = current_state->next;
        }

        current_symbol = current_symbol->next;
    }

    
    system("cls");
    encabezado();
    while (1) {

        printf("Alfabeto de entrada: ");
        imprimirLista(headAlfabetoEntrada);
        printf("Conjunto de estados ingresados:\n");
        imprmirEstados(estadoshead);
        printf("Estado inicial seleccionado (q0): %s\n", q0->estado);
        printf("Conjunto de estados finales ingresados: ");
        struct conjunto_estados* current = estadoshead;
        current = estadoshead;
        while (current != NULL) {
                if (current->isFinal) {
                    printf("%s|", current->estado);
                }
                printf("\n");
                current = current->next;
        }
        printf("Inserte la palabra a validar. Para salir, ingrese S o s:\n");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "S") == 0 || strcmp(input, "s") == 0) {
            break;
        }

        if (validarPalabraAlfabeto(headAlfabetoEntrada, input)) {
            int isValid = validarPalabra(transiciones_head, q0, estadoshead, input);
             if (isValid) {
                system("cls");
                encabezado();
                printf("RESULTADO: Palabra '%s' es valida.\n \n", input);
                estadisticas.palabras_registradas++;
                estadisticas.palabras_validas++;
            } else {
                system("cls");
                encabezado();
                printf("RESULTADO: Palabra '%s' es invalida.\n \n", input);
                estadisticas.palabras_registradas++;
                estadisticas.palabras_invalidas++;
            }
        } else {
            system("cls");
            encabezado();
            printf("ERROR: La palabra '%s' contiene caracteres que no pertenecen al alfabeto de entrada. Intente nuevamente.\n", input);
        }
    }
    system("cls");
    encabezado();
    
    printf("\n\nEstadisticas:\n");
    printf("Palabras registradas: %d\n", estadisticas.palabras_registradas);
    printf("Palabras validas: %d\n", estadisticas.palabras_validas);
    printf("Palabras invalidas: %d\n", estadisticas.palabras_invalidas);

    printf("Presiona enter para continuar");
    while ((c = getchar()) != '\n' && c != EOF);

    estadisticas_globales.palabras_registradas += estadisticas.palabras_registradas;
    estadisticas_globales.palabras_validas += estadisticas.palabras_validas;
    estadisticas_globales.palabras_invalidas += estadisticas.palabras_invalidas;
    estadisticas_globales.AFD_registrados++;

}

void traduccion(){
    struct estadisticas estadisticas = {0, 0, 0, 0};
    int c;
    char input[100];
    struct simbolo_entrada* headAlfabetoEntrada = NULL;
    struct simbolo_salida* headSalidaEntrada = NULL;
    struct conjunto_estados* estadoshead = NULL;
    int inputEntered = 0;
    struct traduccion_simbolo* headTraducciones = NULL;

    system("cls");
    encabezado();
    //Alfabeto Entrada
    while (!inputEntered) { 
        
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Ingresa los simbolos del alfabeto de entrada separados por espacios: ");
        fgets(input, sizeof(input), stdin);

        // Revisar que no este vacio
        if (!isspace(input[0])) {
            inputEntered = 1;
        } else {
            system("cls");
            encabezado();
            printf("ERROR: No se ha ingresado ningun caracter. Presiona Enter para intentarlo nuevamente.\n");
        }
    }

    // Quitar la nueva linea
    input[strcspn(input, "\n")] = '\0';

    char* token = strtok(input, " ");
    
    while (token != NULL) {
        insertarSimbolo(&headAlfabetoEntrada, token[0]);
        token = strtok(NULL, " ");
    }

    int exitAlphabetEntered = 0;
    struct simbolo_salida* headAlfabetoSalida = NULL;

    //Alfabeto Salida
    system("cls");
    encabezado();

    while (!exitAlphabetEntered) {
        //while ((c = getchar()) != '\n' && c != EOF); para esperar enter
        printf("Ingresa los simbolos del alfabeto de salida separados por espacios: ");
        fgets(input, sizeof(input), stdin);

        // Revisar que no este vacio
        if (!isspace(input[0])) {
            exitAlphabetEntered = 1;
        } else {
            printf("ERROR: No se ha ingresado ningun caracter. Presiona Enter para intentarlo nuevamente.\n");
            system("cls");
            encabezado();
        }
    }

    // Quitar la nueva linea
    input[strcspn(input, "\n")] = '\0';

    char* exitToken = strtok(input, " ");
    
    while (exitToken != NULL) {
        insertarSimboloSalida(&headAlfabetoSalida, exitToken[0]);
        exitToken = strtok(NULL, " ");
    }

    system("cls");
    encabezado();
    //Estados

    while (1) {
       
        printf("Alfabeto de entrada: ");
        imprimirLista(headAlfabetoEntrada);

        printf("Alfabeto de salida: ");
        imprimirListaSalida(headAlfabetoSalida);


        if (estadoshead != NULL) {
            printf("Conjunto de estados ingresados:\n");
            struct conjunto_estados* current = estadoshead;
            while (current != NULL) {
                printf("%s|", current->estado);
                current = current->next;
            }
            printf("\n");
        }

        printf("Inserte el conjunto de estados. Debe de ser maximo 15 caracteres y no puede tener espacios. Ingrese el simbolo y despues presione enter. Para salir, ingrese S o s: ");
        fgets(input, sizeof(input), stdin);

            input[strcspn(input, "\n")] = '\0';

            if (strlen(input) > 0) {
                if (input[0] == 's' || input[0] == 'S') { //
                    break; 
                } else {
                    int len = strlen(input);
                    bool hasNonWhitespace = false;
                    for (int i = 0; i < len; i++) {
                        if (!isspace(input[i])) {
                            hasNonWhitespace = true;
                            break;
                        }
                    }

                    if (hasNonWhitespace) {
                        system("cls");
                        encabezado();
                        insertarEstado(&estadoshead, input);
                    } else {
                        system("cls");
                        encabezado();
                        printf("ERROR: No se ha ingresado ningun estado o se ha ingresado solo espacios. Intentalo nuevamente.\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                        
                    }
                }
            }
    }

    system("cls");
    encabezado();

    printf("Alfabeto de entrada: ");
    imprimirLista(headAlfabetoEntrada);

    printf("Conjunto de estados ingresados:\n");
    imprmirEstados(estadoshead);

    //Estado q0
 
    struct conjunto_estados* q0 = seleccionarEstadoInicial(estadoshead);
    printf("Estado inicial seleccionado (q0): %s\n", q0->estado);

    system("cls");
    encabezado();
    // Estados finales
    while (1) {
        int show;
 
        struct conjunto_estados* current = estadoshead;
        printf("Alfabeto de entrada: ");
        imprimirLista(headAlfabetoEntrada);

        printf("Conjunto de estados ingresados:\n");
        imprmirEstados(estadoshead);

        printf("Estado inicial seleccionado (q0): %s\n", q0->estado);

        if (show==1)
        {
            printf("Conjunto de estados finales ingresados: ");
            current = estadoshead;
            while (current != NULL) {
                if (current->isFinal) {
                    printf("%s|", current->estado);
                }
                printf("\n");
                current = current->next;
            }
        }
        
        printf("Inserte los estados finales. Para finalizar, ingrese S o s:\n");
        char input[20]; 
        printf("Estado final: ");
        fgets(input, sizeof(input), stdin);


        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "S") == 0 || strcmp(input, "s") == 0) {
            break;
        }

        current = estadoshead;
        while (current != NULL) {
            if (strcmp(current->estado, input) == 0) {
                current->isFinal = true; 
                show = 1;
                system("cls");
                encabezado();
                break;
                
            }
            current = current->next;
        }

        if (current == NULL) {
            system("cls");
            encabezado();
            printf("ERROR: El estado final '%s' no existe en la lista de estados. Entrada negada.\n", input);
            while ((c = getchar()) != '\n' && c != EOF);
        }

    }

    //Funcion de transicion
    system("cls");
    encabezado();

    struct transicion* transiciones_head = NULL;
    struct simbolo_entrada* current_symbol = headAlfabetoEntrada;
    struct conjunto_estados* current_state = estadoshead;

    while (current_symbol != NULL) {
        char simbolo = current_symbol->simbolo;

        current_state = estadoshead; //Reiniciar el head

        while (current_state != NULL) {
            char estado_siguiente[20];

            printf("Ingrese el estado siguiente para el simbolo '%c' y el estado '%s':\n", simbolo, current_state->estado);

            printf("Estado siguiente: ");
            fgets(estado_siguiente, sizeof(estado_siguiente), stdin);
            estado_siguiente[strcspn(estado_siguiente, "\n")] = '\0';
            system("cls");

            if (!buscarEstado(estadoshead, estado_siguiente)) {
                system("cls");
                encabezado();
                printf("ERROR: El estado siguiente '%s' no existe en la lista de estados. Intente nuevamente.\n", estado_siguiente);
                continue;
            }

            insertarTransicion(&transiciones_head, current_state->estado, simbolo, estado_siguiente);
            system("cls");
            encabezado();

            current_state = current_state->next;
        }

        current_symbol = current_symbol->next;
    }

    system("cls");
    encabezado();
    // Traducciones
    struct simbolo_entrada* current_symbol_entrada = headAlfabetoEntrada;

    while (current_symbol_entrada != NULL) {
    struct conjunto_estados* current_estado = estadoshead;
    while (current_estado != NULL) {
        char entrada = current_symbol_entrada->simbolo;
        char estado_actual[20];
        strcpy(estado_actual, current_estado->estado);

        // Loop until a valid symbol is provided for the translation
        char salida;
        while (true) {
            printf("Ingrese la traduccion para el simbolo '%c' y el estado '%s': ", entrada, estado_actual);
            scanf(" %c", &salida);

            // Check if the symbol is part of the exit alphabet
            if (isValidExitSymbol(salida, headAlfabetoSalida)) {
                break; // Valid symbol, exit the loop
            } else {
                system("cls");
                encabezado();
                printf("ERROR: El simbolo '%c' no es valido en el alfabeto de salida. Intente nuevamente.\n", salida);
            }
        }

        // printf("DEBUG: entrada: %c, estado_actual: %s, salida: %c\n", entrada, estado_actual, salida); // Debug

        insertarTraduccion(&headTraducciones, entrada, estado_actual, salida);
        system("cls");
        encabezado();

        current_estado = current_estado->next;
    }
    current_symbol_entrada = current_symbol_entrada->next;
}

    while ((c = getchar()) != '\n' && c != EOF);

    system("cls");
    encabezado();

    //Traducir
    while (1) {
     
        char input[100]; 
        printf("Ingrese la palabra a traducir usando caracteres del alfabeto de entrada (o ingrese '*' para salir): ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "*") == 0) {
            break;
        }

        struct conjunto_estados* estado_actual = q0;

        char translated_word[100] = "";


       
        if (validarPalabraAlfabeto(headAlfabetoEntrada, input)) {
            estadisticas.palabras_registradas++;
            int isValid = validarPalabra(transiciones_head, q0, estadoshead, input);
            if (isValid) {
                system("cls");
                encabezado();
                printf("RESULTADO: Palabra '%s' es valida.\n", input);
                estadisticas.palabras_validas++;
            } else {
                system("cls");
                encabezado();
                printf("RESULTADO: Palabra '%s' es invalida.\n", input);
                estadisticas.palabras_invalidas++;
            }
                

        for (int i = 0; i < strlen(input); i++) {
            char simbolo_entrada = input[i];

            struct traduccion_simbolo* current_translation = headTraducciones;
            while (current_translation != NULL) {
                if (strcmp(current_translation->estado_actual, estado_actual->estado) == 0 &&
                    current_translation->simbolo_entrada == simbolo_entrada) {
                    char translated_symbol = current_translation->simbolo_salida;
                    strncat(translated_word, &translated_symbol, 1);

                    struct conjunto_estados* estado_siguiente = buscarEstado(estadoshead, current_translation->estado_siguiente);
                    if (estado_siguiente != NULL) {
                        estado_actual = estado_siguiente;
                    } 
                    break;
                }
                current_translation = current_translation->next;
            }

            // if (current_translation == NULL) {
            //     printf("Error: No se encontró la traducción para el símbolo de entrada '%c' y el estado '%s'.\n",
            //            simbolo_entrada, estado_actual->estado);
            //     break;
            // }
        }
        printf("Palabra traducida: %s\n", translated_word);
        estadisticas.palabras_traducidas++;
        }
        else{
            system("cls");
            encabezado();
            printf("ERROR: la palabra no pertenece al alfabeto de entrada \n");
        }
    }


    system("cls");
    encabezado();

    printf("\n\nEstadisticas:\n");
    printf("Palabras registradas: %d\n", estadisticas.palabras_registradas);
    printf("Palabras validas: %d\n", estadisticas.palabras_validas);
    printf("Palabras invalidas: %d\n", estadisticas.palabras_invalidas);
    printf("Palabras traducidas: %d\n", estadisticas.palabras_traducidas);

    printf("Presiona enter para continuar");
    while ((c = getchar()) != '\n' && c != EOF);

    estadisticas_globales.palabras_invalidas += estadisticas.palabras_validas;
    estadisticas_globales.palabras_registradas += estadisticas.palabras_registradas;
    estadisticas_globales.palabras_validas += estadisticas.palabras_validas;
    estadisticas_globales.palabras_traducidas += estadisticas.palabras_traducidas;
    estadisticas_globales.AFD_registrados++;

    system("cls");
    encabezado();

}



