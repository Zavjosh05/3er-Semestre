//
// Created by josh on 04/01/2025.
//
#include <stdio.h>
#include"Nodo.h"
#include"Arista.h"
#include"Kruskal.h"

Nodo nodoTarea();

int main(void)
{
    algoritmoKruskal(nodoTarea());

    return 0;
}


Nodo nodoTarea()
{
    Nodo n1, n2, n3, n4, n5, n6, n7, n8, n9;

    crearNodo(&n1);
    crearNodo(&n2);
    crearNodo(&n3);
    crearNodo(&n4);
    crearNodo(&n5);
    crearNodo(&n6);
    crearNodo(&n7);
    crearNodo(&n8);
    crearNodo(&n9);
    asignarNombreNodo(n1, '1');
    asignarNombreNodo(n2, '2');
    asignarNombreNodo(n3, '3');
    asignarNombreNodo(n4, '4');
    asignarNombreNodo(n5, '5');
    asignarNombreNodo(n6, '6');
    asignarNombreNodo(n7, '7');
    asignarNombreNodo(n8, '8');
    asignarNombreNodo(n9, '9');
    unirNodosConValorDeArista(n1,n2,4);
    unirNodosConValorDeArista(n1,n8,9);
    unirNodosConValorDeArista(n2,n8,11);
    unirNodosConValorDeArista(n2,n3,9);
    unirNodosConValorDeArista(n3,n9,2);
    unirNodosConValorDeArista(n3,n6,4);
    unirNodosConValorDeArista(n3,n4,7);
    unirNodosConValorDeArista(n4,n6,15);
    unirNodosConValorDeArista(n4,n5,10);
    unirNodosConValorDeArista(n5,n6,11);
    unirNodosConValorDeArista(n6,n7,2);
    unirNodosConValorDeArista(n7,n9,6);
    unirNodosConValorDeArista(n7,n8,1);
    unirNodosConValorDeArista(n8,n9,7);
    /*imprimirNodo(n1);
    imprimirNodo(n2);
    imprimirNodo(n3);
    imprimirNodo(n4);
    imprimirNodo(n5);
    imprimirNodo(n6);
    imprimirNodo(n7);
    imprimirNodo(n8);
    imprimirNodo(n9);*/

    return n1;
}

Nodo nodoPrueba()
{
    Nodo n1, n2, n3, n4, n5, n6, n7, n8;

    crearNodo(&n1);
    crearNodo(&n2);
    crearNodo(&n3);
    crearNodo(&n4);
    crearNodo(&n5);
    crearNodo(&n6);
    crearNodo(&n7);
    crearNodo(&n8);
    asignarNombreNodo(n1, 's');
    asignarNombreNodo(n2, '2');
    asignarNombreNodo(n3, '3');
    asignarNombreNodo(n4, '4');
    asignarNombreNodo(n5, '5');
    asignarNombreNodo(n6, '6');
    asignarNombreNodo(n7, '7');
    asignarNombreNodo(n8, 't');
    unirNodosConValorDeArista(n1,n2,9);
    unirNodosConValorDeArista(n1,n6,14);
    unirNodosConValorDeArista(n1,n7,15);
    unirNodosConValorDeArista(n2,n3,23);
    unirNodosConValorDeArista(n6,n3,18);
    unirNodosConValorDeArista(n6,n5,30);
    unirNodosConValorDeArista(n6,n7,5);
    unirNodosConValorDeArista(n7,n5,20);
    unirNodosConValorDeArista(n7,n8,44);
    unirNodosConValorDeArista(n3,n5,2);
    unirNodosConValorDeArista(n3,n8,19);
    unirNodosConValorDeArista(n5,n4,11);
    unirNodosConValorDeArista(n5,n8,16);
    unirNodosConValorDeArista(n4,n3,6);
    unirNodosConValorDeArista(n4,n8,6);
    /*imprimirNodo(n1);
    imprimirNodo(n2);
    imprimirNodo(n3);
    imprimirNodo(n4);
    imprimirNodo(n5);
    imprimirNodo(n6);
    imprimirNodo(n7);
    imprimirNodo(n8);*/

    return n1;
}