#include "Descomprimir.h"
#include <stdio.h>
#include <stdlib.h>
#include "archivo.h"
#include <string.h>
#include "Nodo.h"
#include "huffman.h"

void descomprimir(char * rutaArchivo, char * nombreArchivo, char * extension)
{
  int tamRutaTablaDeFrecuencias;
  char * rutaTablaDeFrecuencias = concaternarRutaNombreYExtension(rutaArchivo, nombreArchivo, extension, &tamRutaTablaDeFrecuencias);
  printf("Hola mundo\n");

  printf("%s", rutaTablaDeFrecuencias);

  FILE * archivoTablaFrecuencias = fopen(rutaTablaDeFrecuencias, "r");
  if (archivoTablaFrecuencias == NULL)
  {
    printf("\nNo es encuentra la tabla de equivalencias, favor de agregar el archivo %sf.txt\n", nombreArchivo);
    exit(-1);
  }

/*
  unsigned char * arrayCaracteresArchivoFrecuencias;

  char * nombreDelArchivoDescomprimido, * extensionDescomprimido;

  int numCaracteresArchivoFrecuencias = 0, posicionActual = 0, tamArrayCaracteres = 0;

  Caracter * arrayCaracteres;

  arrayCaracteresArchivoFrecuencias = obtenerElementosDeArchivo(archivoTablaFrecuencias, &numCaracteresArchivoFrecuencias);

  if(!comprobarCadenaEsta(arrayCaracteresArchivoFrecuencias, numCaracteresArchivoFrecuencias, "INICIO", &posicionActual))
  {
    printf("\aEl .txt relacionado con este archivo comprimido no es el generado por TRUCHA CORPORATION\n");
    exit(-1);
  }

  nombreDelArchivoDescomprimido = cadenaAntesDeUnSaltoDeLinea(arrayCaracteresArchivoFrecuencias, numCaracteresArchivoFrecuencias, &posicionActual);

  llenarArrayCaracteres(arrayCaracteresArchivoFrecuencias, numCaracteresArchivoFrecuencias, &posicionActual, &arrayCaracteres, &tamArrayCaracteres);

  extensionDescomprimido = cadenaAntesDeUnSaltoDeLinea(arrayCaracteresArchivoFrecuencias, numCaracteresArchivoFrecuencias, &posicionActual);

  char * rutaCompletaDescomprimido = malloc(sizeof(char));

  strcat(rutaCompletaDescomprimido, rutaArchivo);
  strcat(rutaCompletaDescomprimido, nombreArchivo);
  strcat(rutaCompletaDescomprimido, "d");
  strcat(rutaCompletaDescomprimido, extensionDescomprimido);

  char * rutaCompletaArchivoComprimido = malloc(sizeof(char));
  strcat(rutaCompletaDescomprimido, rutaArchivo);
  strcat(rutaCompletaDescomprimido, nombreArchivo);
  strcat(rutaCompletaDescomprimido, extension);

  FILE * archivoDescomprimido = fopen(rutaCompletaDescomprimido, "w");
  if(archivoDescomprimido == NULL)
    exit(-1);
  FILE * archivoComprimido = fopen(rutaCompletaDescomprimido, "rb");
  if(archivoComprimido == NULL)
    exit(-1);
  unsigned char * arrayArchivoComprimido = NULL;
  arrayArchivoComprimido = obtenerElementosDeArchivo(archivoComprimido, &tamArrayCaracteres);
*/

}

int comprobarCadenaEsta(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, char * palabraABuscar, int * numAEmpezar)
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

char * cadenaAntesDeUnSaltoDeLinea(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar)
{
  char * cadenaCreada;
  int numAmpezarCopia = *numAEmpezar, tamCadenaCreada = 0, i = 0;
  for(i = numAmpezarCopia; i < numCaracteresArchivo && arrayCaracteresArchivo[i] != '\n'; (*numAEmpezar)++)
    addACadena(&cadenaCreada, arrayCaracteresArchivo[i], &tamCadenaCreada);
  cadenaCreada[i] = '\0';
  i++;
  return cadenaCreada;
}

unsigned char * cadenaAntesDeUnSaltoDeLineaUnsigned(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar)
{
  unsigned char * cadenaCreada;
  int numAmpezarCopia = *numAEmpezar, tamCadenaCreada = 0, i = 0;
  for(i = numAmpezarCopia; i < numCaracteresArchivo && arrayCaracteresArchivo[i] != '\n'; (*numAEmpezar)++)
    addACadenaUnsigned(&cadenaCreada, arrayCaracteresArchivo[i], &tamCadenaCreada);
  cadenaCreada[i] = '\0';
  i++;
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

void addACadenaUnsigned(unsigned char ** arrayAAgregar, char charAAgregar, int * tamArreglo)
{
  if(*tamArreglo == 0)
    (*arrayAAgregar) = malloc(sizeof(unsigned char) * (++(*tamArreglo)));
  else
  {
    tamArreglo++;
    (*arrayAAgregar) = realloc(arrayAAgregar, *tamArreglo);
    (*arrayAAgregar)[(*tamArreglo) - 1] = charAAgregar;
  }
}

void llenarArrayCaracteres(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar, Caracter ** arrayCaracteres, int * tamArrayCaracteres)
{
  for(; *(numAEmpezar) < numCaracteresArchivo && !buscarFinTablaEquivalencias(arrayCaracteresArchivo, numCaracteresArchivo, numAEmpezar); (*numAEmpezar)++)
  {
    unsigned char caracterAGuardar = arrayCaracteresArchivo[(*numAEmpezar)++];
    unsigned char * cadenaDeBits = cadenaAntesDeUnSaltoDeLineaUnsigned(arrayCaracteresArchivo, numCaracteresArchivo, numAEmpezar);
    addAArrayCaracteres((*arrayCaracteres), caracterAGuardar, cadenaDeBits, tamArrayCaracteres);
  }
}

int buscarFinTablaEquivalencias(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar)
{
  int numAEmpezarCopia = *numAEmpezar;

  if(comprobarCadenaEsta(arrayCaracteresArchivo, numCaracteresArchivo, "FIN", &numAEmpezarCopia))
  {
    *numAEmpezar = numAEmpezarCopia;
    return 1;
  }
  return 0;
}

void addAArrayCaracteres(Caracter * arrayAAgregar, unsigned caracter, unsigned char * cadenaEquivalenteBits, int * tamArrayAAgregar)
{
  if(*tamArrayAAgregar == 0)
  {
    arrayAAgregar = (Caracter *)malloc(sizeof(Caracter) * (++(*tamArrayAAgregar)));
    if(arrayAAgregar == NULL)
      exit(-1);
    arrayAAgregar[(*tamArrayAAgregar) - 1] = (Caracter)malloc(sizeof(t_caracter));
    if(arrayAAgregar[(*tamArrayAAgregar) - 1] == NULL)
      exit(-1);
    arrayAAgregar[(*tamArrayAAgregar) - 1]->elem = caracter;
    arrayAAgregar[(*tamArrayAAgregar) - 1]->frecuencia = 0;
    arrayAAgregar[(*tamArrayAAgregar) - 1]->cadenaDeBits = cadenaEquivalenteBits;
    arrayAAgregar[(*tamArrayAAgregar) - 1]->tamCadena = strlen((char *)cadenaEquivalenteBits);
  }
  else
  {
    (*tamArrayAAgregar)++;
    arrayAAgregar = realloc(arrayAAgregar, *tamArrayAAgregar);
    if(arrayAAgregar == NULL)
      exit(-1);
    arrayAAgregar[(*tamArrayAAgregar) - 1] = (Caracter)malloc(sizeof(t_caracter));
    if(arrayAAgregar[(*tamArrayAAgregar) - 1] == NULL)
      exit(-1);
    arrayAAgregar[(*tamArrayAAgregar) - 1]->elem = caracter;
    arrayAAgregar[(*tamArrayAAgregar) - 1]->frecuencia = 0;
    arrayAAgregar[(*tamArrayAAgregar) - 1]->cadenaDeBits = cadenaEquivalenteBits;
    arrayAAgregar[(*tamArrayAAgregar) - 1]->tamCadena = strlen((char *)cadenaEquivalenteBits);
  }
}