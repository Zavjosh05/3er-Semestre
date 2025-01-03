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

  printf("Ingrese el numero del arista: ");
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
  imprimirGrafo(n1,arrNode, &nNode, arrArista, &nArista);
}