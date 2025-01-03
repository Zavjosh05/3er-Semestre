#include <stdio.h>
#include <stdlib.h>
#include "Nodo.h"
#include "Arista.h"

void nodoPrueba();

int main(void)
{

  nodoPrueba();

  return 0;
}

void nodoPrueba()
{
  Nodo n1, n2, n3, n4, n5, n6, n7, n8, *arrNode;
  Arista *arrArista;
  int nNode = 0, nArista = 0;

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
  imprimirNodo(n1);
  imprimirNodo(n2);
  putchar('\n');
  unirNodosConValorDeArista(n1,n6,14);
  imprimirNodo(n1);
  imprimirNodo(n6);
  putchar('\n');
  unirNodosConValorDeArista(n1,n7,15);
  imprimirNodo(n1);
  imprimirNodo(n7);
  putchar('\n');
  unirNodosConValorDeArista(n2,n3,23);
  imprimirNodo(n2);
  imprimirNodo(n3);
  unirNodosConValorDeArista(n6,n3,18);
  imprimirNodo(n6);
  unirNodosConValorDeArista(n6,n5,30);
  imprimirNodo(n6);
  unirNodosConValorDeArista(n6,n7,5);
  imprimirNodo(n6);
  unirNodosConValorDeArista(n7,n5,20);
  imprimirNodo(n7);
  unirNodosConValorDeArista(n7,n8,44);
  imprimirNodo(n7);
  unirNodosConValorDeArista(n3,n5,2);
  imprimirNodo(n3);
  unirNodosConValorDeArista(n3,n8,19);
  imprimirNodo(n3);
  unirNodosConValorDeArista(n5,n4,11);
  imprimirNodo(n5);
  unirNodosConValorDeArista(n5,n8,16);
  imprimirNodo(n5);
  unirNodosConValorDeArista(n4,n3,6);
  imprimirNodo(n4);
  unirNodosConValorDeArista(n4,n8,6);
  imprimirNodo(n4);
  imprimirGrafo(n1,arrNode, &nNode, arrArista, &nArista);
}