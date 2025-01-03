//
// Created by josh on 18/12/2024.
//

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

void eliminarArista(Arista aris)
{
  if(aris == NULL)
    return;

  free(aris);
}