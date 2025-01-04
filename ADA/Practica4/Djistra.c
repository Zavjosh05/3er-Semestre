#include<stdio.h>
#include<stdlib.h>
#include"Arista.h"
#include"Nodo.h"

void algoritmo(Nodo * listaNodos, Arista * listaAristas, int tamListaNodos, int tamListaAristas);
int comprobarNodoExiste(Nodo * listaNodos, char nodoABuscar, int tamListaNodos);
int mostrarPosicionEnArray(Nodo * listaNodos, char nodoABuscar, int tamListaNodos);
int rutaPorPesoPequeno(Nodo node, char nodoFinal, Nodo * listaNodosRecorridos, int * tamListaNodosRecorridos);
void acomodarAristasDeNodos(Nodo * listaNodos, int tamListaNodos);
void acomodarAristasDeNodo(Nodo node);
Nodo * agregarNodoAListaNodosRecorrido(Nodo * listaNodosRecorrido, Nodo nodoAAgregar, int * tamListaNodosRecorrido);
Nodo nodoTarea();

int main(void)
{
  Nodo n1, *arrNode = NULL, **arrNodePtr = &arrNode;
  Arista *arrArista = NULL, **arrAristaPtr = &arrArista;
  int nNode = 0, nArista = 0;

  n1  =  nodoTarea();

  puts("imprimir grafo\n\n\n");
  imprimirGrafo(n1,arrNodePtr, &nNode, arrAristaPtr, &nArista);
  printf("numero de nodos: %d, numero de aristas: %d\n",nNode,nArista);
  arrNode = *arrNodePtr;
  arrArista = *arrAristaPtr;
  printf("Lista de Nodos\n");
  imprimirArregloDeNodos2(arrNode,nNode);
  printf("Lista de Aristas:\n");
  imprimirArregloDeArista2(arrArista,nArista);

  algoritmo(arrNode,arrArista,nNode,nArista);

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
  imprimirNodo(n1);
  imprimirNodo(n2);
  imprimirNodo(n3);
  imprimirNodo(n4);
  imprimirNodo(n5);
  imprimirNodo(n6);
  imprimirNodo(n7);
  imprimirNodo(n8);
  imprimirNodo(n9);

  return n1;
}

void algoritmo(Nodo * listaNodos, Arista * listaAristas, int tamListaNodos, int tamListaAristas)
{
  char nodoInicial, nodoFinal;
  int tamListaNodosRecorridos = 1;
  do
  {
    printf("Ingresa el nodo incial\n");
    scanf("%c", &nodoInicial);
    getchar();
  }while(!comprobarNodoExiste(listaNodos, nodoInicial, tamListaNodos));
  do
  {
    printf("Ingresa el nodo final\n");
    scanf("%c", &nodoFinal);
    getchar();
  }while(!comprobarNodoExiste(listaNodos, nodoFinal, tamListaNodos));
  int posicionNodoInicial = mostrarPosicionEnArray(listaNodos, nodoInicial, tamListaNodos);
  acomodarAristasDeNodos(listaNodos, tamListaNodos);
  imprimirArregloDeNodos(listaNodos, tamListaNodos);
  Nodo * listaNodosRecorridos = (Nodo *) malloc(sizeof(Nodo));
  if(listaNodosRecorridos == NULL)
    exit(-1);
  listaNodosRecorridos[0] = listaNodos[posicionNodoInicial];
  rutaPorPesoPequeno(listaNodos[posicionNodoInicial], nodoFinal, listaNodosRecorridos, &tamListaNodosRecorridos);
}

int comprobarNodoExiste(Nodo * listaNodos, char nodoABuscar, int tamListaNodos)
{
  printf("\ntamListaNodos %d\n", tamListaNodos);
  for(int i = 0; i < tamListaNodos; i++)
  {
    printf("\nHola mundo\n");
    printf("\n%c y %c\n", listaNodos[i]->nombre, nodoABuscar);
    if(listaNodos[i]->nombre == nodoABuscar)
      return 1;
  }
  printf("El nodo no existe\n");
  return 0;
}

int rutaPorPesoPequeno(Nodo node, char nodoFinal, Nodo * listaNodosRecorridos, int * tamListaNodosRecorridos)
{

}


int mostrarPosicionEnArray(Nodo * listaNodos, char nodoABuscar, int tamListaNodos)
{
  for(int i = 0; i < tamListaNodos; i++)
    if(listaNodos[i]->nombre == nodoABuscar)
      return i;
  return 0;
}
void acomodarAristasDeNodos(Nodo * listaNodos, int tamListaNodos)
{
  for(int i = 0; i < tamListaNodos; i++)
    acomodarAristasDeNodo(listaNodos[i]);
}

void acomodarAristasDeNodo(Nodo node)
{
  for(int i = 1; i < node->numAristas; i++)
  {
    int posTemp = i;
    for(int j = posTemp - 1; j >= 0 ; j--)
    {
      if(node->aristas[posTemp]->valor < node->aristas[j]->valor)
      {
        Arista temp = node->aristas[j];
        node->aristas[j] = node->aristas[posTemp];
        node->aristas[posTemp] = temp;
        posTemp = j;
      }
      else
      	break;
    }
  }
}

Nodo * agregarNodoAListaNodosRecorrido(Nodo * listaNodosRecorrido, Nodo nodoAAgregar, int * tamListaNodosRecorrido)
{
  *tamListaNodosRecorrido++;
  listaNodosRecorrido = (Nodo *) realloc(listaNodosRecorrido, sizeof(Nodo) * (*tamListaNodosRecorrido));
  if(listaNodosRecorrido == NULL)
    exit(-1);
  listaNodosRecorrido[*tamListaNodosRecorrido - 1] = nodoAAgregar;
  return listaNodosRecorrido;
}