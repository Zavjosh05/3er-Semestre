#include<stdio.h>
#include<stdlib.h>
#include"Arista.h"
#include"Nodo.h"





int comprobarNodoExiste(Nodo * listaNodos, char nodoABuscar, int tamListaNodos, int op)
{
  for(int i = 0; i < tamListaNodos; i++)
  {
    if(listaNodos[i]->nombre == nodoABuscar)
      return 1;
  }
  if(op)
    printf("El nodo no existe\n");
  return 0;
}





int mostrarPosicionEnArray(Nodo * listaNodos, char nodoABuscar, int tamListaNodos)
{
  for(int i = 0; i < tamListaNodos; i++)
    if(listaNodos[i]->nombre == nodoABuscar)
      return i;
  return 0;
}

Nodo ** agregarNodoAListaNodosRecorrido(Nodo ** listaNodosRecorrido, Nodo nodoAAgregar, int * tamListaNodosRecorrido)
{
  (*tamListaNodosRecorrido)++;
  (*listaNodosRecorrido) = (Nodo *) realloc((*listaNodosRecorrido), sizeof(Nodo) * (*tamListaNodosRecorrido));
  if((*listaNodosRecorrido) == NULL)
    exit(-1);
  (*listaNodosRecorrido)[(*tamListaNodosRecorrido) - 1] = nodoAAgregar;
  return listaNodosRecorrido;
}

Nodo ** quitarUltimoNodoAListaNodosRecorrido(Nodo ** listaNodosRecorrido, int * tamListaNodosRecorrido)
{
  (*listaNodosRecorrido)[(*tamListaNodosRecorrido)-1] = NULL;
  (*tamListaNodosRecorrido)--;
  (*listaNodosRecorrido) = (Nodo *) realloc((*listaNodosRecorrido), sizeof(Nodo) * (*tamListaNodosRecorrido));
  if((*listaNodosRecorrido) == NULL)
    exit(-1);
  return listaNodosRecorrido;
}

int rutaPorPesoPequeno(Nodo node, char nodoFinal, Nodo ** listaNodosRecorridos, int * tamListaNodosRecorridos)
{
  listaNodosRecorridos = agregarNodoAListaNodosRecorrido(listaNodosRecorridos, node, tamListaNodosRecorridos);

  Nodo nodeSiguiente = NULL;

  if(node->nombre == nodoFinal)
    return 1;

  for(int i = 0; i < node->numAristas; i++)
  {

    if(node == node->aristas[i]->n1)
      nodeSiguiente = node->aristas[i]->n2;
    else
      nodeSiguiente = node->aristas[i]->n1;
    if(comprobarNodoExiste(*listaNodosRecorridos, nodeSiguiente->nombre, *tamListaNodosRecorridos, 0))
      continue;
    if(rutaPorPesoPequeno(nodeSiguiente, nodoFinal, listaNodosRecorridos, tamListaNodosRecorridos))
      return 1;
  }
  listaNodosRecorridos = quitarUltimoNodoAListaNodosRecorrido(listaNodosRecorridos, tamListaNodosRecorridos);
  return 0;
}

void crearCopiaDeLaListaNodosRecorridos(Nodo ** listaNodosRecorridos, Nodo ** resultadoFinalListaNodosRecorridos, int tamListaNodosRecorridos)
{
  (*resultadoFinalListaNodosRecorridos) = NULL;
  (*resultadoFinalListaNodosRecorridos) = (Nodo*) malloc(tamListaNodosRecorridos * sizeof(Nodo));
  if((*resultadoFinalListaNodosRecorridos) == NULL)
    exit(-1);
  for (int i = 0; i < tamListaNodosRecorridos; i++)
    (*resultadoFinalListaNodosRecorridos)[i] = (*listaNodosRecorridos)[i];
}

int pesoDelResultado(Nodo * listaNodosRecorridos, int tamListaNodosRecorridos)
{
  int peso = 0;
  for(int i = 0; i < tamListaNodosRecorridos - 1; i++)
  {

    for(int j = 0; j < listaNodosRecorridos[i]->numAristas; j++)
    {
      if(listaNodosRecorridos[i+1] == listaNodosRecorridos[i]->aristas[j]->n1 || listaNodosRecorridos[i+1] == listaNodosRecorridos[i]->aristas[j]->n2)
      {

        peso += listaNodosRecorridos[i]->aristas[j]->valor;
        break;
      }
    }
  }
  return peso;
}

int rutaPorPesoPequenoExhaustivo(Nodo node, char nodoInial, char nodoFinal, Nodo ** listaNodosRecorridos, int * tamListaNodosRecorridos, Nodo ** resultadoFinalListaNodosRecorridos, int * pesoFinal, int * tamresultadoFinalListaNodosRecorridos) {
  listaNodosRecorridos = agregarNodoAListaNodosRecorrido(listaNodosRecorridos, node, tamListaNodosRecorridos);

  Nodo nodeSiguiente = NULL;

  if(node->nombre == nodoFinal) {
    int peso = pesoDelResultado(*listaNodosRecorridos, *tamListaNodosRecorridos);
    if(peso < *pesoFinal || *pesoFinal == 0)
    {
      crearCopiaDeLaListaNodosRecorridos(listaNodosRecorridos, resultadoFinalListaNodosRecorridos, *tamListaNodosRecorridos);
      (*pesoFinal) = peso;
      *tamresultadoFinalListaNodosRecorridos = *tamListaNodosRecorridos;
    }
    listaNodosRecorridos = quitarUltimoNodoAListaNodosRecorrido(listaNodosRecorridos, tamListaNodosRecorridos);
    return 1;
  }

  for(int i = 0; i < node->numAristas; i++)
  {
    if(node == node->aristas[i]->n1)
      nodeSiguiente = node->aristas[i]->n2;
    else
      nodeSiguiente = node->aristas[i]->n1;
    if(comprobarNodoExiste(*listaNodosRecorridos, nodeSiguiente->nombre, *tamListaNodosRecorridos, 0))
      continue;
    rutaPorPesoPequenoExhaustivo(nodeSiguiente, nodoInial, nodoFinal, listaNodosRecorridos, tamListaNodosRecorridos, resultadoFinalListaNodosRecorridos, pesoFinal, tamresultadoFinalListaNodosRecorridos);
  }
  if(node->nombre != nodoInial)
    listaNodosRecorridos = quitarUltimoNodoAListaNodosRecorrido(listaNodosRecorridos, tamListaNodosRecorridos);
  return 0;
}

void algoritmo(Nodo * listaNodos, Arista * listaAristas, int tamListaNodos, int tamListaAristas)
{
  char nodoInicial, nodoFinal;
  int tamListaNodosRecorridos = 0, tamListaNodosRecorridos2 = 0, pesoFinal = 0, tamsolucionListaNodosRecorridos = 0;
  do
  {
    fseek(stdin, 0, SEEK_END);
    printf("Ingresa el nodo incial\n");
    scanf("%c", &nodoInicial);
    getchar();
  }while(!comprobarNodoExiste(listaNodos, nodoInicial, tamListaNodos, 1));
  do
  {
    fseek(stdin, 0, SEEK_END);
    printf("Ingresa el nodo final\n");
    scanf("%c", &nodoFinal);
    getchar();
  }while(!comprobarNodoExiste(listaNodos, nodoFinal, tamListaNodos, 1));

  int posicionNodoInicial = mostrarPosicionEnArray(listaNodos, nodoInicial, tamListaNodos);

  acomodarAristasDeNodos(listaNodos, tamListaNodos);

  Nodo * listaNodosRecorridos = (Nodo *) malloc(sizeof(Nodo));
  Nodo * listaNodosRecorridos2 = (Nodo *) malloc(sizeof(Nodo));
  Nodo * solucionListaNodosRecorridos = (Nodo *) malloc(sizeof(Nodo));

  if(listaNodosRecorridos == NULL)
    exit(-1);

  rutaPorPesoPequeno(listaNodos[posicionNodoInicial], nodoFinal, &listaNodosRecorridos, &tamListaNodosRecorridos);

  printf("\nResultado voraz:\n");
  imprimirArregloDeNodos2(listaNodosRecorridos, tamListaNodosRecorridos);
  printf("\nCon un peso de: %d\n", pesoDelResultado(listaNodosRecorridos, tamListaNodosRecorridos));

  printf("Inicia proceso exhaustivo");
  rutaPorPesoPequenoExhaustivo(listaNodos[posicionNodoInicial], nodoInicial, nodoFinal, &listaNodosRecorridos2, &tamListaNodosRecorridos2, &solucionListaNodosRecorridos, &pesoFinal, &tamsolucionListaNodosRecorridos);
  printf("\nResultado exhaustivo:\n");
  imprimirArregloDeNodos2(solucionListaNodosRecorridos, tamsolucionListaNodosRecorridos);
  printf("\nCon un peso de: %d\n", pesoDelResultado(solucionListaNodosRecorridos, tamsolucionListaNodosRecorridos));
}

void algoritmoDijistra(Nodo * listaNodos, Arista * listaAristas, int tamListaNodos, int tamListaAristas, char nodoInicial, char nodoFinal)
{
  int tamListaNodosRecorridos = 0, tamListaNodosRecorridos2 = 0, pesoFinal = 0, tamsolucionListaNodosRecorridos = 0;

  int posicionNodoInicial = mostrarPosicionEnArray(listaNodos, nodoInicial, tamListaNodos);

  acomodarAristasDeNodos(listaNodos, tamListaNodos);

  Nodo * listaNodosRecorridos = (Nodo *) malloc(sizeof(Nodo));
  Nodo * listaNodosRecorridos2 = (Nodo *) malloc(sizeof(Nodo));
  Nodo * solucionListaNodosRecorridos = (Nodo *) malloc(sizeof(Nodo));

  if(listaNodosRecorridos == NULL)
    exit(-1);

  rutaPorPesoPequeno(listaNodos[posicionNodoInicial], nodoFinal, &listaNodosRecorridos, &tamListaNodosRecorridos);

  printf("\nResultado voraz:\n");
  imprimirArregloDeNodos2(listaNodosRecorridos, tamListaNodosRecorridos);
  printf("\nCon un peso de: %d\n", pesoDelResultado(listaNodosRecorridos, tamListaNodosRecorridos));

  printf("Inicia proceso exhaustivo");
  rutaPorPesoPequenoExhaustivo(listaNodos[posicionNodoInicial], nodoInicial, nodoFinal, &listaNodosRecorridos2, &tamListaNodosRecorridos2, &solucionListaNodosRecorridos, &pesoFinal, &tamsolucionListaNodosRecorridos);
  printf("\nResultado exhaustivo:\n");
  imprimirArregloDeNodos2(solucionListaNodosRecorridos, tamsolucionListaNodosRecorridos);
  printf("\nCon un peso de: %d\n", pesoDelResultado(solucionListaNodosRecorridos, tamsolucionListaNodosRecorridos));
}

void algoritmoDijkstra(Nodo n1)
{
  Nodo *arrNode = NULL, **arrNodePtr = &arrNode;
  Arista *arrArista = NULL, **arrAristaPtr = &arrArista;
  int nNode = 0, nArista = 0;

  imprimirGrafo(n1,arrNodePtr, &nNode, arrAristaPtr, &nArista);
  printf("numero de nodos: %d, numero de aristas: %d\n",nNode,nArista);
  arrNode = *arrNodePtr;
  arrArista = *arrAristaPtr;
  printf("\nLista de Nodos\n");
  imprimirArregloDeNodos2(arrNode,nNode);
  printf("\nLista de Aristas:\n");
  imprimirArregloDeArista2(arrArista,nArista);

  algoritmo(arrNode,arrArista,nNode,nArista);

  eliminarGrafo(arrNode,nNode,arrArista,nArista);
}