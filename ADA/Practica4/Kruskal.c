#include <stdio.h>
#include <stdlib.h>
#include "Nodo.h"
#include "Arista.h"

int calculoDeCosto(Nodo *arrNode, int numNode)
{
    int i,j, sum = 0;
    for(i  = 0; i < numNode-1; i++)
        for(j = 0; j < arrNode[i]->numAristas; j++)
            sum += (arrNode[i]->aristas[j]->n1 == arrNode[i+1]  || arrNode[i]->aristas[j]->n2 == arrNode[i+1])?
              (arrNode[i]->aristas[j]->valor):0;

    return sum;
}

int verificarExistenciaDeNodo(Nodo node, Nodo *arrNode, int numNode)
{
    if(node == NULL || arrNode == NULL || numNode <= 0)
        return 0;

    int i;
    for (i = 0; i < numNode; i++)
        if (node == arrNode[i])
            return 1;
    return 0;
}

int verificarExistenciaDeArista(Arista node, Arista *arrArista, int numArista)
{
    int i;
    for (i = 0; i < numArista; i++)
        if (node == arrArista[i])
            return 1;
    return 0;
}


Nodo obtenerNodoDeCaracter(char x, Nodo *arrNode, int numNode)
{
    int i;

    for (i = 0; i < numNode; i++)
        if (arrNode[i]->nombre == x)
            return arrNode[i];
    puts("No se encontro el nodo");
    return NULL;
}

Nodo ingresarNodoParaKruskal(Nodo *arrNode, int numNode, int modo)
{
    char c;
    Nodo node;

    if (modo == 1)
        puts("Ingresa el nombre del nodo inicio");
    else
        puts("Ingresa el nombre del nodo destino");
    do
    {
        fseek(stdin, 0, SEEK_END);
        c = getchar();
        node = obtenerNodoDeCaracter(c,arrNode,numNode);
        if (node == NULL) puts("ingresar un nodo existente");
    }while (node == NULL);

    return node;
}

int verficarConexionEntreNodos(Nodo n1, Nodo n2, Arista *memoria, int numMemoria)
{
  int ind1 = 0, ind2 = 0, i;

  for(i = 0; i<numMemoria; i++)
  {
    if(memoria[i]->n1 == n1 || memoria[i]->n2 == n1) ind1 = 1;
    if(memoria[i]->n1 == n2 || memoria[i]->n2 == n2) ind2 = 1;
    if (ind1 && ind2) return 1;
  }

  return 0;
}

Nodo* busquedaExaustivaEnSubgrafo(Nodo inicial, Nodo final, Arista *memoria, int numMemoria, int *numTrazoPtr)
{
    Nodo *trazo, *callejon = NULL, temp;
    int numCallejon = 0, ind = 1, ind2,  i, j;
    *numTrazoPtr = 0;

    *numTrazoPtr += 1;
    trazo = (Nodo*)calloc(1, sizeof(Nodo));
    *trazo = inicial;

    while (ind)
    {
        if(*numTrazoPtr > 0)
        {
            ind2 = 1;
            i = 0;
            while (i < trazo[*numTrazoPtr-1]->numAristas && ind2)
            {
                if(verificarExistenciaDeArista(trazo[*numTrazoPtr-1]->aristas[i], memoria, numMemoria))
                {
                    temp = (trazo[*numTrazoPtr-1]->aristas[i]->n1 == trazo[*numTrazoPtr-1])?
                        (trazo[*numTrazoPtr-1]->aristas[i]->n2):(trazo[*numTrazoPtr-1]->aristas[i]->n1);
                    if(!verificarExistenciaDeNodo(temp, trazo, *numTrazoPtr) && !verificarExistenciaDeNodo(temp, callejon, numCallejon))
                    {
                        *numTrazoPtr += 1;
                        trazo = (Nodo*)realloc(trazo,sizeof(Nodo)**numTrazoPtr);
                        trazo[*numTrazoPtr-1] = temp;
                        ind2 = 0;
                        if(temp == final) ind = 0;
                    }
                }
                if (ind2 != 0) i++;
            }
            if(i == trazo[*numTrazoPtr-1]->numAristas  && ind)
            {
                numCallejon += 1;
                if(numCallejon-1 == 0)
                    callejon = (Nodo*)calloc(numCallejon, sizeof(Nodo));
                else
                    callejon = (Nodo*)realloc(callejon, sizeof(Nodo)*numCallejon);
                callejon[numCallejon-1] = trazo[*numTrazoPtr-1];
                *numTrazoPtr -= 1;
                trazo = (Nodo*)realloc(trazo, sizeof(Nodo)* *numTrazoPtr);
            }
        }else return NULL;

    }

    return trazo;
}

void procesoKruskal(Nodo inicial,Nodo final ,Nodo *arrNode, int numNode, Arista *arrArista, int numArista)
{
    Arista *memoria;
    Nodo *trazo;
    int numMemoria = 0,numTrazo = 0, *numTrazoPtr = &numTrazo , i, j, ind = 1;

    acomodarAristasDeNodos(arrNode, numNode);
    i = 0;
    while(i < numArista && ind)
    {
      numMemoria += 1;
      if (i != 0)
        memoria = (Arista*)realloc(memoria, sizeof(Arista) * numMemoria);
      else
        memoria = (Arista*)calloc(1,sizeof(Arista));
      memoria[numMemoria - 1] = arrArista[i];
      if (verficarConexionEntreNodos(inicial, final,memoria,numMemoria))
      {
          trazo = busquedaExaustivaEnSubgrafo(inicial,final,memoria,numMemoria, numTrazoPtr);
          if (trazo != NULL)  ind = 0;
      }
      i++;
    }
    printf("Numero de nodos por los que se pasa: %d\n", numTrazo);
    puts("Camino tomado:");
    imprimirArregloDeNodos2(trazo,numTrazo);
    printf("Costo total: %d\n", calculoDeCosto(trazo, numTrazo));

}

void algoritmoKruskal(Nodo grafo)
{
    Nodo *arrNode = NULL, **arrNodePtr = &arrNode, inicial, final;
    Arista *arrArista = NULL, **arrAristaPtr = &arrArista;
    int nNode = 0, nArista = 0;

    imprimirGrafo(grafo,arrNodePtr, &nNode, arrAristaPtr, &nArista);
    arrNode = *arrNodePtr;
    arrArista = *arrAristaPtr;
    printf("El grafo insertado cuenta con: %d nodos y %d aristas\n\n",nNode,nArista);
    ordenarArregloDeAristas(arrArista,nArista);
    ordenarArregloDeNodos(arrNode,nNode);
    puts("Nodos:");
    imprimirArregloDeNodos2(arrNode,nNode);
    puts("\nAristas:");
    imprimirArregloDeArista2(arrArista,nArista);
    putchar('\n');
    do
    {
        inicial = ingresarNodoParaKruskal(arrNode,nNode,1);
        final = ingresarNodoParaKruskal(arrNode,nNode,0);
        (inicial == final)?(puts("Los nodos no pueden ser iguales :v\ningrese nodos diferentes")):(puts("nodos registrados\n"));
    }while(inicial == final);

    procesoKruskal(inicial,final,arrNode,nNode,arrArista,nArista);

    eliminarGrafo(arrNode,nNode,arrArista,nArista);


}
