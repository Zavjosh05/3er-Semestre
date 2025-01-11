#ifndef NODO_H
#define NODO_H

typedef struct nodo
{
    char elemento;
    struct nodo *izq, *der;
}*Nodo;

int crearNodo(Nodo);
int eliminarNodo(Nodo);
int asignarElementoNodo(Nodo,char);
int asignarConexionNodoIzquierda(Nodo,Nodo);
int asignarConexionNodoDerecha(Nodo,Nodo);
int asignarConexionesNodo(Nodo,Nodo,Nodo);

#endif //NODO_H
