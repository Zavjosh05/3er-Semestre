//
// Created by josh on 18/12/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "Nodo.h"

//Funcion para crear nodo
//Esta funcion no inicializa el arreglo de aristas, pero si asigna el tamaño del arreglo a 0
int crearNodo(Nodo *node)
{
    *node = (Nodo)malloc(sizeof(t_nodo));
    if(*node == NULL)
        return 0;

    (*node)->numAristas = 0;
    return 1;
}

//Funcion para asignar el nombre a un nodo
int asignarNombreNodo(Nodo node, char nom)
{
  if(node == NULL)
    return 0;

  node->nombre = nom;
  if(node->nombre == '\0')
    return 0;
  return 1;
}

//Funcion que inicializa el arreglo de aristas en caso de que se quiera
//vincular una con el nodo
int nodoPrimerizo(Nodo node)
{
  if(node == NULL)
    return 0;

  node->numAristas += 1;
  node->aristas = (Arista*)calloc(1, sizeof(Arista));
  if(node->aristas == NULL)
    return 0;

  return 1;
}

//Funcion que imprime los datos del nodo, incluyendo las aristas y nodos a los que esta conectado
void imprimirNodo(Nodo node)
{
  if(node == NULL)
    printf("Nodo nulo\n");
  else
  {
    printf("Nodo: nombre = %c\nAristas en las que participa:\n", node->nombre);
    for(int i = 0; i < node->numAristas; i++)
      printf("\tArista: %p\n\t\tvalor: %d\n\t\tConectado con el nodo: %c\n",
             node->aristas[i], node->aristas[i]->valor,(node->aristas[i]->n1 == node)?(node->aristas[i]->n2->nombre):(node->aristas[i]->n1->nombre));
  }
}

//Checa si el nodo a analizar es primerizo o no
void checarNodoPrimerizo(Nodo node)
{
	if(node->numAristas == 0)
          nodoPrimerizo(node);
  else
  {
    node->numAristas += 1;
    node->aristas = (Arista*)realloc(node->aristas, sizeof(Arista) * node->numAristas);
  }
}

//Funcion para unir dos nodos
//int unirNodos(Nodo a, Nodo b)
//{
//    Arista aris;
//    crearArista(&aris);
//    checarNodoPrimerizo(a);
//    checarNodoPrimerizo(b);
//    aris->n1 = a;
//    aris->n2 = b;
//    a->aristas[a->numAristas-1] = aris;
//    b->aristas[b->numAristas-1] = aris;
//    asignarValorDeAristaPorUsuario(aris);
//    if(aris->n1 == NULL || aris->n2 == NULL)
//      return 0;
//    return 1;
//}

int unirNodosConValorDeArista(Nodo a, Nodo b, int val)
{
    Arista aris;
    crearArista(&aris);
    checarNodoPrimerizo(a);
    checarNodoPrimerizo(b);
    aris->n1 = a;
    aris->n2 = b;
    a->aristas[a->numAristas-1] = aris;
    b->aristas[b->numAristas-1] = aris;
    asignarValorDeArista(aris, val);
    if(aris->n1 == NULL || aris->n2 == NULL)
      return 0;
    return 1;
}

int busquedaLinealNodo(Nodo node, Nodo *arr, int numNodos)
{
  if(node == NULL || arr == NULL || numNodos == 0)
    return 0;

  int i;

  for(i = 0; i < numNodos; i++)
    if(node == arr[i])
    	return 1;

  return 0;
}

void imprimirGrafo(Nodo node, Nodo *arrNode, int *numNodos, Arista *arrArista, int *numAristas)
{
  if(node == NULL)
    printf("Nodo nulo\n");

  int i;
  Nodo temp;

  printf("\n numero de Nodos: %d\n", *numNodos);

  if(*numNodos  == 0)
  {
    *numNodos += 1;
    arrNode = (Nodo*)calloc(1, sizeof(Nodo));
    *arrNode = node;
  }
  else
  {
    *numNodos += 1;
    arrNode = (Nodo*)realloc(arrNode, sizeof(Nodo) * *numNodos);
    arrNode[*numNodos-1] = node;
  }

  imprimirNodo(node);
  if(*numAristas  ==  0)
  {
    *numAristas += 1;
    arrArista = (Arista*)calloc(1, sizeof(Arista));
    *arrArista = node->aristas[0];
    temp = (node->aristas[0]->n1 == node)?(node->aristas[0]->n2):(node->aristas[0]->n1);
      if(!busquedaLinealNodo(temp, arrNode, *numNodos))
        imprimirGrafo(temp, arrNode, numNodos, arrArista, numAristas);
    i = 1;
  }
  else i = 0;
  for(; i < node->numAristas; i++)
  {
    if(!busquedaLinealArista(node->aristas[i], arrArista, *numAristas))
    {
      *numAristas += 1;
      arrArista = (Arista*)realloc(arrArista, sizeof(Arista) * *numAristas);
      arrArista[*numAristas-1] = node->aristas[i];
      temp = (node->aristas[i]->n1 == node)?(node->aristas[i]->n2):(node->aristas[i]->n1);
      if(!busquedaLinealNodo(temp, arrNode, *numNodos))
        imprimirGrafo(temp, arrNode, numNodos, arrArista, numAristas);
    }
  }
}

int imprimirArregloDeNodos(Nodo *arrNode, int numNodos)
{
  if(numNodos == 0)
    return 0;

  int i;

}

void eliminarNodo(Nodo node)
{
  if(node == NULL)
    return;

  free(node->aristas);
  free(node);
}

void eliminarGrafo(Nodo *arrNode, int numNode, Arista *arrArista, int numArista)
{
  if(arrNode == NULL || arrArista == NULL)
    return;

  int i;

  for(i = 0; i < numNode; i++)
    	eliminarNodo(arrNode[i]);

  for(i = 0; i < numArista; i++)
    	eliminarArista(arrArista[i]);
}