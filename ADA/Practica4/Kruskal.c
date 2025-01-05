#include <stdio.h>
#include <stdlib.h>
#include "Nodo.h"
#include "Arista.h"


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

int verficiarConexionEntreNodos(Nodo n1, Nodo n2, Arista *memoria, int numMemoria)
{
  
}

void procesoKruskal(Nodo inicial,Nodo final ,Nodo *arrNode, int numNode, Arista *arrArista, int numArista)
{
    Arista *memoria;
    int numMemoria = 0, i, j;

    for (i = 0; i < numArista; i++)
    {
      numMemoria += 1;
      if (i != 0) memoria = (Arista*)realloc(memoria, sizeof(Arista) * numMemoria);
      else memoria = (Arista*)calloc(1,sizeof(Arista));
      memoria[numMemoria - 1] = arrArista[i];
      for(j = 0; j < numMemoria; j++)
        if (memoria[j]->n1  == inicial || memoria[j]->n2 == inicial )
    }
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
    imprimirArregloDeNodos2(arrNode,nNode);
    putchar('\n');
    //imprimirArregloDeArista2(arrArista,nArista);
    do
    {
        inicial = ingresarNodoParaKruskal(arrNode,nNode,1);
        final = ingresarNodoParaKruskal(arrNode,nNode,0);
        (inicial == final)?(puts("Los nodos no pueden ser iguales :v\ningrese nodos diferentes")):(puts("nodos registrados"));
    }while(inicial == final);

    procesoKruskal(inicial,final,arrNode,nNode,arrArista,nArista);

    eliminarGrafo(arrNode,nNode,arrArista,nArista);

}



int verificarExistenciaDeNodo(Nodo node, Nodo *arrNode, int numNode)
{
    int i;
    for (i = 0; i < numNode; i++)
        if (node == arrNode[i])
            return 1;
    return 0;
}

