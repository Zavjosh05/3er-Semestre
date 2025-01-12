#include <stdio.h>
#include <stdlib.h>
#include "archivo.h"
#include <string.h>
#include "Descomprimir.h"

void descomprimir(char * rutaArchivo, char * nombreArchivo, char * extension)
{
  FILE * archivo = fopen(nombreArchivo, "r");
  char * arrayCaracteresArchivo, * nombreDelArchivo;
  int numCaracteresArchivo, posicionActual = 0;


  arrayCaracteresArchivo = obtenerElementosDeArchivo(archivo, &numCaracteresArchivo);

  if(!comprobarCadenaEsta(arrayCaracteresArchivo, numCaracteresArchivo, "INICIO", &posicionActual))
  {
    printf("\aEl .dat ingresado no es el generado por TRUCHA CORPORATION\n");
    exit(-1);
  }
  nombreDelArchivo = cadenaAntesDeUnSaltoDeLinea(arrayCaracteresArchivo, numCaracteresArchivo, &posicionActual);

}

int comprobarCadenaEsta(char * arrayCaracteresArchivo, int numCaracteresArchivo, char * palabraABuscar, int * numAEmpezar)
{
  int contador = 0;
  for(int i = (*numAEmpezar); i < numCaracteresArchivo && palabraABuscar[i] != '\0'; (*numAEmpezar)++)
  {
    if(arrayCaracteresArchivo[i] == palabraABuscar[i])
      contador++;
  }
  if(contador == strlen(palabraABuscar))
    return 1;
  return 0;
}

char * cadenaAntesDeUnSaltoDeLinea(char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar)
{
  char * cadenaCreada;
  int numAmpezarCopia = *numAEmpezar, tamCadenaCreada = 0, i = 0;
  for(i = numAmpezarCopia; i < numCaracteresArchivo && arrayCaracteresArchivo[i] != '\n'; (*numAEmpezar)++)
    addACadena(&cadenaCreada, arrayCaracteresArchivo[i], &tamCadenaCreada);
  cadenaCreada[i] = '\0';
  return cadenaCreada;
}

void addACadena(char ** arrayAAgregar, char charAAgregar, int * tamArreglo)
{
  if(*tamArreglo == 0)
    (*arrayAAgregar) = malloc(sizeof(char) * (++(*tamArreglo)));
  else
  {
    tamArreglo++;
    (*arrayAAgregar) = realloc(arrayAAgregar, *tamArreglo);
    (*arrayAAgregar)[(*tamArreglo) - 1] = charAAgregar;
  }
}