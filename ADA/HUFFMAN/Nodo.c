#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    char elemento;
    struct nodo *izq, *der;
}*Nodo;

int crearNodo(Nodo node)
{
    node = (Nodo)calloc(1, sizeof(Nodo));

    if (node == NULL)
      return 0;
    return 1;
}

int asignarElementoNodo(Nodo node, char elemento)
{
    if(node == NULL || elemento == '\0') return 0;

    node->elemento = elemento;
    return 1;
}

int asignarConexionNodoIzquierda(Nodo node, Nodo izq)
{
    if(node == NULL || izq == NULL) return 0;

    node->izq = izq;
    return 1;
}

int asignarConexionNodoDerecha(Nodo node, Nodo der)
{
  if(node == NULL || der == NULL) return 0;

  node->der = der;
}

int asignarConexionesNodo(Nodo node, Nodo izq, Nodo der)
{
    if(asignarConexionNodoIzquierda(node, izq) && asignarConexionNodoDerecha(node, der))
        return 1;
    else
        return 0;
}