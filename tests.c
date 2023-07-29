#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

struct simbolo_entrada {
    wchar_t simbolo;
    struct simbolo_entrada* next;
};

struct simbolo_entrada* crearSimbolo(wchar_t simbolo) {
    struct simbolo_entrada* nuevoSimbolo = (struct simbolo_entrada*)malloc(sizeof(struct simbolo_entrada));
    nuevoSimbolo->simbolo = simbolo;
    nuevoSimbolo->next = NULL;
    return nuevoSimbolo;
}

void insertarSimbolo(struct simbolo_entrada** head, wchar_t simbolo) {
    if (!iswspace(simbolo)) {
        if (!*head) {
            *head = crearSimbolo(simbolo);
        } else {
            struct simbolo_entrada* current = *head;
            while (current->next) {
                current = current->next;
            }
            current->next = crearSimbolo(simbolo);
        }
        // Debug print to check the symbol being stored
        printf("Stored symbol: %lc\n", simbolo);
    }
}

void imprimirLista(struct simbolo_entrada* head) {
    struct simbolo_entrada* current = head;
    while (current != NULL) {
        wprintf(L"%lc ", current->simbolo);
        current = current->next;
    }
    wprintf(L"\n");
}

int main() {
    // Set the locale to "es_ES.UTF-8" for proper handling of wide characters
    setlocale(LC_ALL, "es_ES.UTF-8");

    struct simbolo_entrada* head = NULL;
    wchar_t input[100];

    wprintf(L"Ingresa los simbolos del alfabeto de entrada separados por espacios: ");
    fgetws(input, sizeof(input), stdin);

    wchar_t* token = wcstok(input, L" ");
    while (token != NULL) {
        insertarSimbolo(&head, token[0]);
        token = wcstok(NULL, L" ");
    }

    wprintf(L"Alfabeto de entrada: ");
    imprimirLista(head);

    while (1)
    {
        /* code */
    }
    

    // Free the memory for the linked list
    struct simbolo_entrada* current = head;
    while (current != NULL) {
        struct simbolo_entrada* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
