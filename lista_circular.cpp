#include <stdio.h>
#include <stdlib.h>

/* Estructura base del nodo
   struct Nodo {
       int dato;
       struct Nodo *siguiente;
   };
*/

struct Nodo {
    int dato;
    struct Nodo *siguiente;
};

/* Parte B. Lista Circular */

/* Paso B1. Creación y características
   1. Modifica la estructura de la lista simple para convertirla en circular:
      - El último nodo ya no apunta a NULL, sino al primero.
   2. Declara un puntero *cabeza y uno adicional *ultimo.
*/

void insertarCircular(struct Nodo **cabeza, struct Nodo **ultimo, int valor) {
    struct Nodo *nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));
    if (nuevo == NULL) {
        printf("No se pudo reservar memoria.\n");
        return;
    }
    nuevo->dato = valor;

    if (*cabeza == NULL) {
        /* primer nodo: se apunta a sí mismo */
        *cabeza = nuevo;
        *ultimo = nuevo;
        nuevo->siguiente = nuevo;
    } else {
        /* inserta al inicio: nuevo apunta a cabeza y ultimo apunta a nuevo */
        nuevo->siguiente = *cabeza;
        (*ultimo)->siguiente = nuevo;
        *cabeza = nuevo;
    }
}

/* Paso B3. Recorrido circular
   Implementa un recorrido que se detenga cuando el puntero vuelva a la cabeza.
*/
void recorrerCircular(struct Nodo *cabeza) {
    struct Nodo *actual;

    if (cabeza == NULL) {
        printf("Lista circular vacia\n");
        return;
    }

    printf("Lista circular: ");
    actual = cabeza;
    do {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    } while (actual != cabeza);
    printf("(cabeza)\n");
}

/* Paso B4. Eliminación
   Implementa eliminarCircular(struct Nodo **cabeza, int valor) que:
   - Busca el nodo a eliminar.
   - Si es el primero, actualiza el puntero del último.
   - Si es intermedio, enlaza su anterior con su siguiente.
   - Libera la memoria del nodo eliminado.
*/
void eliminarCircular(struct Nodo **cabeza, struct Nodo **ultimo, int valor) {
    struct Nodo *actual, *anterior;

    if (*cabeza == NULL) {
        printf("Lista circular vacia, no se puede eliminar.\n");
        return;
    }

    actual = *cabeza;
    anterior = *ultimo;

    /* buscar el nodo con ese valor */
    do {
        if (actual->dato == valor) {
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    } while (actual != *cabeza);

    if (actual->dato != valor) {
        printf("Valor no encontrado en la lista circular.\n");
        return;
    }

    if (actual == *cabeza && actual == *ultimo) {
        /* solo hay un nodo */
        *cabeza = NULL;
        *ultimo = NULL;
    } else if (actual == *cabeza) {
        /* es el primero: mover cabeza y actualizar ultimo->siguiente */
        *cabeza = actual->siguiente;
        (*ultimo)->siguiente = *cabeza;
    } else {
        /* nodo intermedio o ultimo */
        anterior->siguiente = actual->siguiente;
        if (actual == *ultimo) {
            *ultimo = anterior;
        }
    }

    free(actual);
}

int main() {
    struct Nodo *cabeza = NULL;
    struct Nodo *ultimo = NULL;
    int n, i, valor, aEliminar;

    /* Paso B2. Inserción circular
       Implementa la función:
       1. Pide al usuario cuántos valores desea insertar.
       2. Inserta cada nuevo nodo al inicio de la lista.
       3. Muestra el contenido después de cada inserción.
    */
    printf("Cuantos valores deseas insertar en la lista circular? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Valor %d: ", i + 1);
        scanf("%d", &valor);
        insertarCircular(&cabeza, &ultimo, valor);
        recorrerCircular(cabeza);
    }

    /* Paso B3. Recorrido circular */
    printf("\nRecorrido final de la lista circular:\n");
    recorrerCircular(cabeza);

    /* Paso B4. Eliminación: pedir valor y aplicar eliminarCircular */
    printf("Que valor deseas eliminar de la lista circular? ");
    scanf("%d", &aEliminar);

    eliminarCircular(&cabeza, &ultimo, aEliminar);

    printf("Lista circular despues de eliminar:\n");
    recorrerCircular(cabeza);

    /* (Opcional) liberar memoria de la lista circular */
    if (cabeza != NULL) {
        struct Nodo *actual = cabeza;
        struct Nodo *tmp;
        do {
            tmp = actual;
            actual = actual->siguiente;
            free(tmp);
        } while (actual != cabeza);
    }

    return 0;
}