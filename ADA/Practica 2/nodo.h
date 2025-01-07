#ifndef NODO_H
#define NODO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
	struct nodo *enlaceA;
	int elem;
	struct nodo *enlaceB;
	// struct nodo *enlaceC;
	// struct nodo **enlaces; 	// arreglo a apuntadores
}t_nodo, *Nodo;

// Nodo = (struct nodo *)
// Nodo *= (struct nodo **)

int crearNodo(Nodo *n);
int destruirNodo(Nodo *n);

// conexion:
int conectarEnlaceA(Nodo n, Nodo eA);
int conectarEnlaceB(Nodo n, Nodo eB);

// consulta:
int consultarEnlaceA(Nodo n, Nodo *eA);
int consultarEnlaceB(Nodo n, Nodo *eB);

//desconexion:
int desconectarEnlaceA(Nodo n);
int desconectarEnlaceB(Nodo n);

#endif

/*
// referencia a multiples nodos
typedef struct nodo
{
	struct nodo *enlaceA;
	struct nodo **coleccion;	// arreglo dinamico de nodos
	struct nodo *enlaceB;
	// struct nodo *enlaceC;
	// struct nodo **enlaces; 	// arreglo a apuntadores
}t_nodo, *Nodo;
*/



