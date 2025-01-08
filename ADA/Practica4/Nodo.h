#ifndef NODO_H
#define NODO_H

#include "Arista.h"

typedef struct nodo
{
    char nombre;
    Arista *aristas;
    int numAristas;
} *Nodo, t_nodo;

int crearNodo(Nodo*);
int asignarNombreNodo(Nodo,char);
int nodoPrimerizo(Nodo);
void checarNodoPrimerizo(Nodo);
int unirNodos(Nodo,Nodo);
int unirNodosConValorDeArista(Nodo,Nodo,int);
int busquedaLinealNodo(Nodo,Nodo*,int);
void checarNodoPrimerizo(Nodo);
void imprimirNodo(Nodo);
int imprimirArregloDeNodos(Nodo*,int);
int imprimirArregloDeNodos2(Nodo*,int);
void imprimirGrafo(Nodo,Nodo**,int*,Arista**,int*);
int imprimirArregloDeArista2(Arista*,int);
void acomodarAristasDeNodo(Nodo);
void acomodarAristasDeNodos(Nodo*,int);
void ordenarArregloDeNodos(Nodo*,int);
void eliminarGrafo(Nodo*,int,Arista*,int);

#endif //NODO_H
