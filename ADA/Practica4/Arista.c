#include <stdio.h>
#include <stdlib.h>
#include "Arista.h"

int crearArista(Arista *arista)
{
    *arista = (Arista)malloc(sizeof(t_Arista));
    if(*arista == NULL)
        return 0;
    return 1;
}

void imprimirArista(Arista arista)
{
  if(arista == NULL)
    printf("Arista vacia\n");

  printf("Arista:\n\tapuntador: %p\n\tvalor: %d\n\tnodo 1 conectado: %p\n\tnodo 2 conectado: %p\n",
         arista,arista->valor,arista->n1,arista->n2);
}

void asignarValorDeAristaPorUsuario(Arista aris)
{
  if(aris == NULL)
    return;

  fseek(stdin, 0, SEEK_END);
  scanf("%d",&(aris->valor));
  if(aris->valor <= 0)
  {
    printf("Valor de arista invalido\n");
    asignarValorDeAristaPorUsuario(aris);
  }
}

void asignarValorDeArista(Arista aris,int val)
{
  if(aris == NULL)
    return;

  if(val <= 0)
  {
    printf("Valor de arista invalido, ingrese un valor valido manualmente\n");
    asignarValorDeAristaPorUsuario(aris);
  }

  aris->valor = val;
}

int busquedaLinealArista(Arista aris, Arista *arrArista, int arrNum)
{
  if(aris == NULL || arrArista == NULL || arrNum <= 0)
    return 0;

  int i;

  for(i = 0; i < arrNum; i++)
    if(aris == arrArista[i])
      return 1;

  return 0;
}

int imprimirArregloDeArista(Arista *arr, int arrNum)
{
  if(arr == NULL || arrNum <= 0)
    return 0;

  int i;

  for(i = 0; i < arrNum; i++)
    imprimirArista(arr[i]);

  return 1;
}

void ordenarArregloDeAristas(Arista *arr, int arrNum)
{
  if(arr == NULL || arrNum <= 0)
    return;

  int i,  j, gap;
  Arista temp;

  for (gap = arrNum / 2; gap > 0; gap /= 2)
        for (i = gap; i < arrNum; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap]->valor > temp->valor; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
}

void shellSort(int arr[], int n) {
    // Comenzamos con un gran intervalo, luego lo reducimos
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Realizamos un ordenamiento por inserción para este intervalo
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void eliminarArista(Arista aris)
{
  if(aris == NULL)
    return;

  free(aris);
}