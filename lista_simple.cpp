#include <stdio.h>
#include <stdlib.h>

/* Estructura base del nodo
   struct Nodo {
       int dato;
       struct Nodo *siguiente;
   };
*/

/* Parte A. Lista Simple */

/* Paso A1. Creación de la estructura y funciones básicas
   1. Crea una estructura Nodo y un puntero *cabeza inicializado en NULL.
   2. Implementa las funciones:
      - insertarInicio(struct Nodo **cabeza, int valor)
      - recorrer(struct Nodo *cabeza)
      - eliminar(struct Nodo **cabeza, int valor)
      - liberar(struct Nodo *cabeza)
*/

struct Nodo {
    int dato;
    struct Nodo *siguiente;
};

void insertarInicio(struct Nodo **cabeza, int valor) {
    struct Nodo *nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));
    if (nuevo == NULL) {
        printf("No se pudo reservar memoria.\n");
        return;
    }
    nuevo->dato = valor;
    nuevo->siguiente = *cabeza;
    *cabeza = nuevo;
}

void recorrer(struct Nodo *cabeza) {
    struct Nodo *actual = cabeza;
    printf("Lista: ");
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

void eliminar(struct Nodo **cabeza, int valor) {
    struct Nodo *actual = *cabeza;
    struct Nodo *anterior = NULL;

    /* Paso A3. Recorrido y eliminación
       3. Implementa la lógica:
          - Si el valor está en la cabeza, mover la cabeza al siguiente.
          - Si está en medio, cambiar los punteros del nodo anterior.
    */

    while (actual != NULL && actual->dato != valor) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("Valor no encontrado en la lista.\n");
        return;
    }

    if (anterior == NULL) { /* está en la cabeza */
        *cabeza = actual->siguiente;
    } else {                /* está en medio o al final */
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
}

void liberar(struct Nodo *cabeza) {
    struct Nodo *tmp;
    /* Paso A4. Liberación de memoria
       1. Usa free() para liberar cada nodo.
       2. Muestra un mensaje final: 'Memoria liberada correctamente'.
    */
    while (cabeza != NULL) {
        tmp = cabeza;
        cabeza = cabeza->siguiente;
        free(tmp);
    }
    printf("Memoria liberada correctamente.\n");
}

int main() {
    struct Nodo *cabeza = NULL;
    int n, i, valor, aEliminar;

    /* Paso A2. Inserción
       1. Pide al usuario cuántos valores desea insertar.
    */
    printf("Cuantos valores deseas insertar en la lista simple? ");
    scanf("%d", &n);

    /* 2. Inserta cada nuevo nodo al inicio de la lista.
       3. Muestra el contenido después de cada inserción.
    */
    for (i = 0; i < n; i++) {
        printf("Valor %d: ", i + 1);
        scanf("%d", &valor);
        insertarInicio(&cabeza, valor);
        recorrer(cabeza);
    }

    /* Paso A3. Recorrido y eliminación
       1. Recorre la lista e imprime todos los nodos con printf("%d -> ", dato).
       2. Pregunta al usuario qué valor desea eliminar.
    */
    printf("\nLista completa:\n");
    recorrer(cabeza);

    printf("Que valor deseas eliminar? ");
    scanf("%d", &aEliminar);

    eliminar(&cabeza, aEliminar);

    /* 4. Muestra la lista actualizada después de eliminar. */
    printf("Lista despues de eliminar:\n");
    recorrer(cabeza);

    /* Paso A4. Liberación de memoria */
    liberar(cabeza);

    return 0;
}
