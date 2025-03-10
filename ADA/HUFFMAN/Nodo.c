#include <stdio.h>
#include <stdlib.h>
#include "Nodo.h"

int crearNodo(Nodo *node)
{
    *node = (Nodo)calloc(1, sizeof(t_nodo));

    (*node)->izq = NULL;
    (*node)->der = NULL;

    if (node == NULL)
      return 0;
    return 1;
}

int crearNodoPadre(Nodo *node)
{
    *node = (Nodo)calloc(1, sizeof(t_nodo));
    crearCaracter(&((*node)->elemento));
    (*node)->elemento->elem = '\0';
    (*node)->elemento->frecuencia = 0;

    if (node == NULL || (*node)->elemento == NULL)
      return 0;
    return 1;
}

int crearCaracter(Caracter *character)
{
    *character = (Caracter)malloc(sizeof(t_caracter));
    (*character)->elem = '\0';
    (*character)->frecuencia = 0;
    (*character)->cadenaDeBits = NULL;
    (*character)->tamCadena = 0;

    if (character == NULL) return 0;
    return 1;
}

int eliminarCaracter(Caracter character)
{
    free(character);

    if(character != NULL)
      return 0;
    return 1;
}

int eliminarNodo(Nodo node)
{
    free(node->elemento->cadenaDeBits);
	free(node);

	if(node != NULL) return 0;
	else return 1;
}

int asignarElementoNodo(Nodo node,unsigned char elemento)
{
    if(node == NULL || elemento == '\0') return 0;

    node->elemento->elem = elemento;
    return 1;
}

int asignarConexionNodoIzquierda(Nodo node, Nodo izq)
{
    if(node == NULL || izq == NULL) return 0;

    node->izq = izq;
    return 1;
}

int asignarConexionNodoDerecha(Nodo node, Nodo der)
{
  if(node == NULL || der == NULL) return 0;

  node->der = der;
  return 1;
}

int asignarConexionesNodo(Nodo node, Nodo izq, Nodo der)
{
    if(asignarConexionNodoIzquierda(node, izq) && asignarConexionNodoDerecha(node, der))
        return 1;
    else
        return 0;
}

/*
*Funcion que se encarga de imprimir los datos de un caracter, si este es nulo, se informara de esto
* @param character caracter que deseamos imprimir
 */
void imprimirCaracter(Caracter character)
{
    if(character == NULL)
        puts("Caracter: Nulo");
    else
        printf("caracter: %c\nfrecuencia: %d\ncadena de bits: %s\nnumero de bits: %d\n",
         character->elem, character->frecuencia, character->cadenaDeBits, character->tamCadena);
}

void imprimirArregloDeCaracter(Caracter *arr, int tArr)
{
	int i;

	for(i = 0; i < tArr; i++)
          imprimirCaracter(arr[i]);
}

/*Funcion que se encarga de imprimir los datos de un nodo, si este es nulo, se informara de esto
* @param node nodo que deseamos imprimir
*/
void imprimirNodo(Nodo node)
{
    if(node == NULL)
        puts("Nodo: Nulo");
    else
    {
        puts("Nodo: ");
        imprimirCaracter(node->elemento);
        puts("Conectado a nodos: \nNodo izquierda: ");
        if(node->izq != NULL)
        	imprimirCaracter(node->izq->elemento);
        else
          puts("Nodo nulo");
        puts("Nodo derecha: ");
        if(node->der != NULL)
        	imprimirCaracter(node->der->elemento);
        else
          puts("Nodo nulo");
    }
}

void imprimirArregloDeNodo(Nodo *arr, int tArr)
{
	int i;

	for(i = 0; i < tArr; i++)
          imprimirNodo(arr[i]);
}

/**
* Funcion para ordenar un arreglo ascendentemente de nodos mediante shell sort con base a la frecuencia de sus caracteres
* @param arr arreglo a ordenar
* @param tam tamaño del arreglo a ordenar
*/
void ordenarArregloDeNodosAsc(Nodo *arr, int tam)
{
    int gap, i, j;
    Nodo temp;

    crearNodo(&temp);
    for (gap = tam / 2; gap > 0; gap /= 2)
        for (i = gap; i < tam; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap]->elemento->frecuencia > temp->elemento->frecuencia; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
}
/*
* Funcion para ordenar un arreglo descendentemente de nodos mediante shell sort con base a la frecuencia de sus caracteres
* @param arr arreglo a ordenar
* @param tam tamaño del arreglo a ordenar
*/
void ordenarArregloDeNodosDsc(Nodo *arr, int tam)
{
    int gap, i, j;
    Nodo temp;

    crearNodo(&temp);
    for (gap = tam / 2; gap > 0; gap /= 2)
        for (i = gap; i < tam; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap]->elemento->frecuencia < temp->elemento->frecuencia; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
}

/**
* Funcion para ordenar ascendentemente un arreglo de caracteres mediante shell sort con base a la frecuencia de sus caracteres
* @param arr arreglo a ordenar
* @param tam tamaño del arreglo a ordenar
*/
void ordenarArregloDeCaracteresAsc(Caracter *arr, int tam)
{
    int gap, i, j;
    Caracter temp;

    crearCaracter(&temp);
    for (gap = tam / 2; gap > 0; gap /= 2)
        for (i = gap; i < tam; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap]->frecuencia > temp->frecuencia; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
}

/*
* Funcion para ordenar descendentemente un arreglo de caracteres mediante shell sort con base a la frecuencia de sus caracteres
* @param arr arreglo a ordenar
* @param tam tamaño del arreglo a ordenar
*/
void ordenarArregloDeCaracteresDsc(Caracter *arr, int tam)
{
    int gap, i, j;
    Caracter temp;

    crearCaracter(&temp);
    for (gap = tam / 2; gap > 0; gap /= 2)
        for (i = gap; i < tam; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap]->frecuencia < temp->frecuencia; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
}