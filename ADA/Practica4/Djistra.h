#ifndef DIJSTRA_H
#define DIJSTRA_H

#include "Nodo.h"
#include "Arista.h"

void algoritmo(Nodo*, Arista*,int,int);
int comprobarNodoExiste(Nodo*,char,int,int);
int mostrarPosicionEnArray(Nodo*,char,int);
int rutaPorPesoPequeno(Nodo,char,Nodo**,int*);
void acomodarAristasDeNodos(Nodo*,int);
void acomodarAristasDeNodo(Nodo);
Nodo ** agregarNodoAListaNodosRecorrido(Nodo**,Nodo,int*);
Nodo nodoTarea();
Nodo ** quitarUltimoNodoAListaNodosRecorrido(Nodo**,int*);
int rutaPorPesoPequenoExhaustivo(Nodo,char,char,Nodo**,int*,Nodo**,int*,int*);
void crearCopiaDeLaListaNodosRecorridos(Nodo**,Nodo**,int);
int pesoDelResultado(Nodo*,int);
void algoritmoDijkstra(Nodo);
void algoritmoDijistra(Nodo*,Arista*,int,int,char,char);

#endif //DIJSTRA_H
