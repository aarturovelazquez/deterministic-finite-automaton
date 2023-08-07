#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <locale.h>
#include <windows.h>
#include <conio.h> 
#include <stdbool.h>


void disableCtrlC() {
    signal(SIGINT, SIG_IGN);
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

// Function para insertar un simbolo en la lista ligada
void insertarSimbolo(struct simbolo_entrada** head, wchar_t simbolo) {

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
            printf("Stored symbol: %c\n", simbolo);
        }
}

//Simbolo Salida

struct simbolo_salida {
    wchar_t simbolo;
    struct simbolo_salida* next;
};

// Funcion para crear un nuevo simbolo de salida
struct simbolo_salida* crearSimboloSalida(wchar_t simbolo) {
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
int simboloSalidaExiste(struct simbolo_salida* head, wchar_t simbolo) {
    struct simbolo_salida* current = head;
    while (current != NULL) {
        if (current->simbolo == simbolo) {
            return 1; 
        }
        current = current->next;
    }
    return 0;
}

// Function para insertar un simbolo de salida en la lista ligada
void insertarSimboloSalida(struct simbolo_salida** head, wchar_t simbolo) {

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


// Estructura del los conjuntos de estado
struct conjunto_estados {
    wchar_t estado[20];
    struct conjunto_estados* next;
    bool isFinal;
};

// Funcion para crear un nuevo conjunto de estado
struct conjunto_estados* crearEstado(wchar_t estado[20]) {
    struct conjunto_estados* nuevoEstado = (struct conjunto_estados*)malloc(sizeof(struct conjunto_estados));
    wcscpy(nuevoEstado->estado, estado); 
    nuevoEstado->next = NULL;
    nuevoEstado->isFinal = false;
    return nuevoEstado;
}

int estadoExiste(struct conjunto_estados* head, const wchar_t* estado) {
    struct conjunto_estados* current = head;
    while (current != NULL) {
        if (wcscmp(current->estado, estado) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}


//Funcion para insertar el estado
void insertarEstado(struct conjunto_estados** head, const wchar_t* estado) {
    if (wcslen(estado) > 15 || wcschr(estado, ' ') != NULL) {
        system("cls");
        encabezado();
        printf("Error: El estado no puede ser mayor a 15 caracteres o contener espacios. Intente nuevamente.\n");
        return;
    }

    // Create a new state node
    struct conjunto_estados* nuevoEstado = (struct conjunto_estados*)malloc(sizeof(struct conjunto_estados));
    wcscpy(nuevoEstado->estado, estado);
    nuevoEstado->isFinal = 0;
    nuevoEstado->next = NULL;

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
        wprintf(L"%ls|", current->estado); 
    current = current->next;
    }
    printf("\n");
}



struct conjunto_estados* buscarEstado(struct conjunto_estados* head, wchar_t estado[20]) {
    struct conjunto_estados* current = head;
    while (current != NULL) {
        if (wcscmp(current->estado, estado) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct conjunto_estados* seleccionarEstadoInicial(struct conjunto_estados* head) {
    wchar_t input[20];

    printf("Seleccione el estado inicial (q0) de la lista de estados:\n");

    while (1) {
        
        printf("Estado seleccionado: ");
        fgetws(input, sizeof(input), stdin);

        input[wcscspn(input, L"\n")] = '\0';

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
    wchar_t estado_actual[15];
    wchar_t simbolo;
    wchar_t estado_siguiente[15];
    struct transicion* next;
};

void insertarTransicion(struct transicion** head, wchar_t estado_actual[15], wchar_t simbolo, wchar_t estado_siguiente[15]) {
    struct transicion* nuevaTransicion = (struct transicion*)malloc(sizeof(struct transicion));
    wcscpy(nuevaTransicion->estado_actual, estado_actual);
    nuevaTransicion->simbolo = simbolo;
    wcscpy(nuevaTransicion->estado_siguiente, estado_siguiente);
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

int validarPalabra(struct transicion* transiciones_head, struct conjunto_estados* q0, struct conjunto_estados* estadoshead, wchar_t* palabra) {
    
    struct conjunto_estados* estado_actual = q0;


    for (int i = 0; i < wcslen(palabra); i++) {
        wchar_t simbolo = palabra[i];

        
        struct transicion* current_transicion = transiciones_head;
        while (current_transicion != NULL) {
            if (wcscmp(current_transicion->estado_actual, estado_actual->estado) == 0 && current_transicion->simbolo == simbolo) {

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


int validarPalabraAlfabeto(struct simbolo_entrada* headAlfabeto, wchar_t* palabra) {
    for (int i = 0; i < wcslen(palabra); i++) {
        wchar_t simbolo = palabra[i];
        if (!simboloExiste(headAlfabeto, simbolo)) {
            return 0;
        }
    }
    return 1; 
}

//Traduccion

// Estructura de las traducciones de simbolos
struct traduccion_simbolo {
    wchar_t simbolo_entrada;
    wchar_t estado_actual[15];
    wchar_t estado_siguiente[15];
    wchar_t simbolo_salida;
    struct traduccion_simbolo* next;
};


// Funcion para crear una nueva traduccion
struct traduccion_simbolo* crearTraduccion(wchar_t simbolo_entrada, wchar_t estado_actual[15], wchar_t simbolo_salida) {
    struct traduccion_simbolo* nuevaTraduccion = (struct traduccion_simbolo*)malloc(sizeof(struct traduccion_simbolo));
    nuevaTraduccion->simbolo_entrada = simbolo_entrada;
    wcscpy(nuevaTraduccion->estado_actual, estado_actual);
    nuevaTraduccion->simbolo_salida = simbolo_salida;
    nuevaTraduccion->next = NULL;
    return nuevaTraduccion;
}

// Funcion para insertar una traduccion en la lista ligada
void insertarTraduccion(struct traduccion_simbolo** head, wchar_t simbolo_entrada, wchar_t estado_actual[15], wchar_t simbolo_salida) {
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

wchar_t traducirSimbolo(struct traduccion_simbolo* head, wchar_t simbolo_entrada) {
    struct traduccion_simbolo* current = head;
    while (current != NULL) {
        if (current->simbolo_entrada == simbolo_entrada) {
            return current->simbolo_salida;
        }
        current = current->next;
    }
    return simbolo_entrada;
}

bool isValidExitSymbol(wchar_t symbol, struct simbolo_salida* headExitAlphabet) {
    struct simbolo_salida* current = headExitAlphabet;
    while (current != NULL) {
        if (current->simbolo == symbol) {
            return true; 
        }
        current = current->next;
    }
    return false; 
}

wchar_t getValidCharacterInput() {
    wchar_t ch;
    while (1) {
        ch = _getch();
        if (ch == 0 || ch == -32) {
            _getch();
        } else if (ch == 3 || ch == 18) {
        } else {
            return ch;
        }
    }
}

int isValidSpanishAlphabet(const wchar_t* input) {
    wchar_t spanish_characters[] = L"abcdefghijklmnopqrstuvwxyz"
                                    L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                    L"áéíóúÁÉÍÓÚ"
                                    L"ñÑ"
                                    L"üÜ"
                                    L"0123456789";

    for (size_t i = 0; input[i] != L'\0'; i++) {
        if (wcschr(spanish_characters, input[i]) == NULL) {
            return 0;
        }
    }
    return 1;
}




// Declaraciones
void validacion();
void traduccion();

struct estadisticas_globales estadisticas_globales = {0,0,0,0,0};


int main() {
    disableCtrlC();
    
    system("cls");
    encabezado();
    while (1) {
    int selection;
    while (1) {

        wchar_t c;
        printf("1. AFD Traduccion\n");
        printf("2. AFD Validacion\n");
        printf("3. Salir\n");
        printf("Selecciona una opcion: ");
        selection = getValidCharacterInput() - '0';
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
    wchar_t input[100];
    struct simbolo_entrada* headAlfabetoEntrada = NULL;
    struct conjunto_estados* estadoshead = NULL;
    int inputEntered = 0;

    system("cls");
    encabezado();

    //Alfabeto
    while (!inputEntered) { 

        printf("Ingresa los simbolos del alfabeto de entrada separados por espacios. Cuando termine, presione enter: ");
        fgetws(input, sizeof(input), stdin);

         input[wcscspn(input,L"\n")] = '\0';

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
    input[wcscspn(input,L"\n")] = '\0';

    wchar_t* token = wcstok(input,L" ");
    
    while (token != NULL) {
        insertarSimbolo(&headAlfabetoEntrada, token[0]);
        token = wcstok(NULL,L" ");
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
                wprintf(L"%ls|", current->estado);
                current = current->next;
            }
            printf("\n");
        }

        printf("Inserte el conjunto de estados. Debe de ser maximo 15 caracteres y no puede tener espacios. Ingrese el simbolo y despues presione enter. Para salir, ingrese S o s: ");
        fgetws(input, sizeof(input), stdin);

            input[wcscspn(input, L"\n")] = '\0';

            if (wcslen(input) > 0) {
                if (input[0] == 's' || input[0] == 'S') { //
                    break; 
                } else {
                    int len = wcslen(input);
                    bool hasNonWhitespace = false;
                    for (int i = 0; i < len; i++) {
                        if (!isspace(input[i])) {
                            hasNonWhitespace = true;
                            break;
                        }
                    }

                    if (estadoExiste(estadoshead, input)) {
                        system("cls");
                        encabezado();
                        printf("ERROR: El estado aceptacion '%s' ya existe en la lista de estados. Entrada negada.\n", input);
                        continue;
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
                    wprintf(L"%ls|", current->estado);
                }
                current = current->next;
            }
            printf("\n");
        }
        
        printf("Inserte los estados de aceptacion. Para finalizar, ingrese S o s:\n");
        wchar_t input[20];

        printf("Estado aceptacion: ");
        fgetws(input, sizeof(input), stdin);

        input[wcscspn(input, L"\n")] = '\0';

        if (wcscmp(input, L"S") == 0 || wcscmp(input, L"s") == 0) {
            break;
        }

        current = estadoshead;
        while (current != NULL) {
            if (wcscmp(current->estado, input) == 0) {
                current->isFinal = true;
                show = 1;
                break;
                
            }
            current = current->next;
            system("cls");
            encabezado();
        }

        if (current == NULL) {
            system("cls");
            encabezado();
            wprintf(L"ERROR: El estado aceptacion '%ls' no existe en la lista de estados. Entrada negada.\n", input);
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
        wchar_t simbolo = current_symbol->simbolo;

        current_state = estadoshead;

        while (current_state != NULL) {
            wchar_t estado_siguiente[20];

            wprintf(L"Ingrese el estado siguiente para el simbolo '%lc' y el estado '%ls':\n", simbolo, current_state->estado);

            printf("Estado siguiente: ");
            fgetws(estado_siguiente, sizeof(estado_siguiente), stdin);
            estado_siguiente[wcscspn(estado_siguiente, L"\n")] = '\0';

            if (!buscarEstado(estadoshead, estado_siguiente)) {
                wprintf(L"ERROR: El estado siguiente '%ls' no existe en la lista de estados. Intente nuevamente.\n", estado_siguiente);
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
        wprintf(L"Estado inicial seleccionado (q0): %ls\n", q0->estado);
        printf("Conjunto de estados aceptacion ingresados: ");
        struct conjunto_estados* current = estadoshead;
        current = estadoshead;
        while (current != NULL) {
                if (current->isFinal) {
                    wprintf(L"%ls|", current->estado);
                }
                printf("\n");
                current = current->next;
        }
        printf("Inserte la palabra a validar. Para salir, ingrese S o s:\n");
        fgetws(input, sizeof(input), stdin);

        input[wcscspn(input, L"\n")] = '\0';

        if (wcscmp(input, L"S") == 0 || wcscmp(input, L"s") == 0) {
            break;
        }

        if (validarPalabraAlfabeto(headAlfabetoEntrada, input)) {
            int isValid = validarPalabra(transiciones_head, q0, estadoshead, input);
            if (isValid) {
                system("cls");
                encabezado();
                wprintf(L"RESULTADO: Palabra '%ls' es valida.\n", input);
                estadisticas.palabras_validas++;
            } else {
                system("cls");
                encabezado();
                wprintf(L"RESULTADO: Palabra '%ls' es invalida.\n", input);
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

    system("cls");
    encabezado();

}

void traduccion(){
    struct estadisticas estadisticas = {0, 0, 0, 0};
    int c;
    wchar_t input[100];
    struct simbolo_entrada* headAlfabetoEntrada = NULL;
    struct simbolo_salida* headSalidaEntrada = NULL;
    struct conjunto_estados* estadoshead = NULL;
    int inputEntered = 0;
    struct traduccion_simbolo* headTraducciones = NULL;

    system("cls");
    encabezado();
    //Alfabeto Entrada
    while (!inputEntered) { 
        
        printf("Ingresa los simbolos del alfabeto de entrada separados por espacios. Cuando termine, presione enter: ");
        fgetws(input, sizeof(input), stdin);

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
    input[wcscspn(input, L"\n")] = '\0';

    wchar_t* token = wcstok(input, L" ");
    
    while (token != NULL) {
        insertarSimbolo(&headAlfabetoEntrada, token[0]);
        token = wcstok(NULL, L" ");
    }

    int exitAlphabetEntered = 0;
    struct simbolo_salida* headAlfabetoSalida = NULL;

    //Alfabeto Salida
    system("cls");
    encabezado();

    while (!exitAlphabetEntered) {
        //while ((c = getchar()) != '\n' && c != EOF); para esperar enter
        printf("Ingresa los simbolos del alfabeto de salida separados por espacios. Cuando termine, presione enter: ");
        fgetws(input, sizeof(input), stdin);

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
    input[wcscspn(input, L"\n")] = '\0';

    wchar_t* exitToken = wcstok(input, L" ");
    
    while (exitToken != NULL) {
        insertarSimboloSalida(&headAlfabetoSalida, exitToken[0]);
        exitToken = wcstok(NULL, L" ");
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
                wprintf(L"%ls|", current->estado);
                current = current->next;
            }
            printf("\n");
        }

        printf("Inserte el conjunto de estados. Debe de ser maximo 15 caracteres y no puede tener espacios. Ingrese el simbolo y despues presione enter. Para salir, ingrese S o s: ");
        fgetws(input, sizeof(input), stdin);

            input[wcscspn(input, L"\n")] = '\0';

            if (wcslen(input) > 0) {
                if (input[0] == 's' || input[0] == 'S') { //
                    break; 
                } else {
                    int len = wcslen(input);
                    bool hasNonWhitespace = false;
                    for (int i = 0; i < len; i++) {
                        if (!isspace(input[i])) {
                            hasNonWhitespace = true;
                            break;
                        }
                    }

                    if (estadoExiste(estadoshead, input)) {
                        system("cls");
                        encabezado();
                        wprintf(L"ERROR: El estado aceptacion '%ls' ya existe en la lista de estados. Entrada negada.\n", input);
                        continue;
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
    // Estados aceptacion
    while (1) {
        int show;
 
        struct conjunto_estados* current = estadoshead;
        printf("Alfabeto de entrada: ");
        imprimirLista(headAlfabetoEntrada);

        printf("Conjunto de estados ingresados:\n");
        imprmirEstados(estadoshead);

        wprintf(L"Estado inicial seleccionado (q0): %ls\n", q0->estado);

        if (show==1)
        {
            printf("Conjunto de estados  ingfresados: ");
            current = estadoshead;
            while (current != NULL) {
                if (current->isFinal) {
                    wprintf(L"%ls|", current->estado);
                }
                current = current->next;
            }
            printf("\n");
        }
        
        printf("Inserte los estados aceptacion. Para finalizar, ingrese S o s:\n");
        wchar_t input[20]; 
        printf("Estado aceptacion: ");
        fgetws(input, sizeof(input), stdin);


        input[wcscspn(input, L"\n")] = '\0';

        if (wcscmp(input, L"S") == 0 || wcscmp(input, L"s") == 0) {
            break;
        }

        current = estadoshead;
        while (current != NULL) {
            if (wcscmp(current->estado, input) == 0) {
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
            printf("ERROR: El estado aceptacion '%s' no existe en la lista de estados. Entrada negada.\n", input);
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
        wchar_t simbolo = current_symbol->simbolo;

        current_state = estadoshead; //Reiniciar el head

        while (current_state != NULL) {
            wchar_t estado_siguiente[20];

            wprintf(L"Ingrese el estado siguiente para el simbolo '%lc' y el estado '%ls':\n", simbolo, current_state->estado);

            printf("Estado siguiente: ");
            fgetws(estado_siguiente, sizeof(estado_siguiente), stdin);
            estado_siguiente[wcscspn(estado_siguiente, L"\n")] = '\0';
            system("cls");

            if (!buscarEstado(estadoshead, estado_siguiente)) {
                system("cls");
                encabezado();
                printf("ERROR: El estado siguiente '%ls' no existe en la lista de estados. Intente nuevamente.\n", estado_siguiente);
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
        wchar_t entrada = current_symbol_entrada->simbolo;
        wchar_t estado_actual[20];
        wcscpy(estado_actual, current_estado->estado);

        wchar_t salida;
        while (true) {
            wprintf(L"Ingrese la traduccion para el simbolo '%lc' y el estado '%ls': ", entrada, estado_actual);
            scanf(" %c", &salida);

            if (isValidExitSymbol(salida, headAlfabetoSalida)) {
                break;
            } else {
                system("cls");
                encabezado();
                wprintf(L"ERROR: El simbolo '%lc' no es valido en el alfabeto de salida. Intente nuevamente.\n", salida);
            }
        }


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
     
        wchar_t input[100]; 
        printf("Alfabeto de entrada: ");
        imprimirLista(headAlfabetoEntrada);
        printf("Alfabeto de salida: \n");
        imprimirListaSalida(headAlfabetoSalida);
        printf("Conjunto de estados ingresados:\n");
        imprmirEstados(estadoshead);
        wprintf(L"Estado inicial seleccionado (q0): %ls\n", q0->estado);
        printf("Conjunto de estados aceptacion ingresados: ");
        struct conjunto_estados* current = estadoshead;
        current = estadoshead;
        while (current != NULL) {
                if (current->isFinal) {
                    wprintf(L"%ls|", current->estado);
                }
                printf("\n");
                current = current->next;
        }
        printf("Ingrese la palabra a traducir usando caracteres del alfabeto de entrada (o ingrese '*' para salir): ");
        fgetws(input, sizeof(input), stdin);

        input[wcscspn(input, L"\n")] = '\0';

        if (wcscmp(input, L"*") == 0) {
            break;
        }

        struct conjunto_estados* estado_actual = q0;

        wchar_t translated_word[100] = L"";


       
        if (validarPalabraAlfabeto(headAlfabetoEntrada, input)) {
            estadisticas.palabras_registradas++;
            int isValid = validarPalabra(transiciones_head, q0, estadoshead, input);
            if (isValid) {
                system("cls");
                encabezado();
                wprintf(L"RESULTADO: Palabra '%ls' es valida.\n", input);
                estadisticas.palabras_validas++;
            } else {
                system("cls");
                encabezado();
                wprintf(L"RESULTADO: Palabra '%ls' es invalida.\n", input);
                estadisticas.palabras_invalidas++;
            }
                

        for (int i = 0; i < wcslen(input); i++) {
            wchar_t simbolo_entrada = input[i];

            struct traduccion_simbolo* current_translation = headTraducciones;
            while (current_translation != NULL) {
                if (wcscmp(current_translation->estado_actual, estado_actual->estado) == 0 &&
                    current_translation->simbolo_entrada == simbolo_entrada) {
                    wchar_t translated_symbol = current_translation->simbolo_salida;
                    wcsncat(translated_word, &translated_symbol, 1);

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
        wprintf(L"Palabra traducida: %ls\n", translated_word);
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

    estadisticas_globales.palabras_invalidas += estadisticas.palabras_invalidas;
    estadisticas_globales.palabras_registradas += estadisticas.palabras_registradas;
    estadisticas_globales.palabras_validas += estadisticas.palabras_validas;
    estadisticas_globales.palabras_traducidas += estadisticas.palabras_traducidas;
    estadisticas_globales.AFD_registrados++;

    system("cls");
    encabezado();

}


