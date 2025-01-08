#ifndef ARISTA_H
#define ARISTA_H

struct nodo;

typedef struct arista
{
    int valor;
    struct nodo *n1, *n2;
}*Arista, t_Arista;

int crearArista(Arista*);
void imprimirArista(Arista);
void asignarValorDeAristaPorUsuario(Arista);
void asignarValorDeArista(Arista,int);
int busquedaLinealArista(Arista,Arista*,int);
void eliminarArista(Arista);
int imprimirArregloDeArista(Arista*,int);
void ordenarArregloDeAristas(Arista*,int);

#endif //ARISTA_H
