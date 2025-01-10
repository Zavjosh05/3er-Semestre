#ifndef NODO_H
#define NODO_H

typedef struct nodo
{
    char elemento;
    struct nodo *izq, *der;
}*Nodo;

int crearNodo(Nodo);
int asignarElementoNodo(Nodo,char);
int asignarConexionNodoIzquierda(Nodo node, Nodo);

#endif //NODO_H
