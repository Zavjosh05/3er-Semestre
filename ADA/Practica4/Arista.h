//
// Created by josh on 18/12/2024.
//

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

#endif //ARISTA_H
