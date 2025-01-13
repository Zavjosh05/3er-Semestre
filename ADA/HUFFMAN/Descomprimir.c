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
  char * rutaTablaDeFrecuencias = concaternarRutaNombreYExtension(rutaArchivo, nombreArchivo, "f.txt", &tamRutaTablaDeFrecuencias);

  printf("%s", rutaTablaDeFrecuencias);

  FILE * archivoTablaFrecuencias = fopen(rutaTablaDeFrecuencias, "r");
  if (archivoTablaFrecuencias == NULL)
  {
    printf("\nNo es encuentra la tabla de equivalencias, favor de agregar el archivo %sf.txt\n", nombreArchivo);
    exit(-1);
  }

  unsigned char * arrayCaracteresArchivoFrecuencias = NULL;

  char * nombreDelArchivoDescomprimido = NULL, * extensionDescomprimido = NULL;

  int numCaracteresArchivoFrecuencias = 0, posicionActual = 0, tamArrayCaracteres = 0;

  Caracter * arrayCaracteres = NULL;

  arrayCaracteresArchivoFrecuencias = obtenerElementosDeArchivo(archivoTablaFrecuencias, &numCaracteresArchivoFrecuencias);

  printf("\n%s\n", arrayCaracteresArchivoFrecuencias);

  if(!comprobarCadenaEsta(arrayCaracteresArchivoFrecuencias, numCaracteresArchivoFrecuencias, "INICIO", &posicionActual))
  {
    printf("\aEl .txt relacionado con este archivo comprimido no es el generado por TRUCHA CORPORATION\n");
    exit(-1);
  }
  printf("\nola kikin\n");

  nombreDelArchivoDescomprimido = cadenaAntesDeUnSaltoDeLinea(arrayCaracteresArchivoFrecuencias, numCaracteresArchivoFrecuencias, &posicionActual);

  printf("\n%s\n", nombreDelArchivoDescomprimido);

  fclose(archivoTablaFrecuencias);
  free(rutaTablaDeFrecuencias);
  free(arrayCaracteresArchivoFrecuencias);
  free(nombreDelArchivoDescomprimido);
  free(extensionDescomprimido);
  free(arrayCaracteres);
  /*

  llenarArrayCaracteres(arrayCaracteresArchivoFrecuencias, numCaracteresArchivoFrecuencias, &posicionActual, &arrayCaracteres, &tamArrayCaracteres);

  extensionDescomprimido = cadenaAntesDeUnSaltoDeLinea(arrayCaracteresArchivoFrecuencias, numCaracteresArchivoFrecuencias, &posicionActual);

  printf("\n%s\n", nombreDelArchivoDescomprimido);

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
  for(; ((*numAEmpezar) < numCaracteresArchivo) && (palabraABuscar[(*numAEmpezar)] != '\0'); (*numAEmpezar)++)
  {
    if(arrayCaracteresArchivo[(*numAEmpezar)] == palabraABuscar[(*numAEmpezar)])
      contador++;
  }
  if(contador == strlen(palabraABuscar))
    return 1;
  return 0;
}

char * cadenaAntesDeUnSaltoDeLinea(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar)
{
  printf("\nIniciando cadenaAntesDeUnSaltoDeLinea con numAEmpezar de: %d\tcon numero caracteres archivo: %d\n", *numAEmpezar, numCaracteresArchivo);
  char * cadenaCreada = NULL;
  int tamCadenaCreada = 0;
  for(; ((*numAEmpezar) < numCaracteresArchivo) && (arrayCaracteresArchivo[(*numAEmpezar)] != '\n'); (*numAEmpezar)++)
  {
    addACadena(&cadenaCreada, arrayCaracteresArchivo[(*numAEmpezar)], &tamCadenaCreada);
    printf("%s ", cadenaCreada);
  }
  cadenaCreada[(*numAEmpezar)] = '\0';
  (*numAEmpezar)++;
  printf("\nLa cadena es: %s\n", cadenaCreada);
  return cadenaCreada;
}

unsigned char * cadenaAntesDeUnSaltoDeLineaUnsigned(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar)
{
  printf("\nIniciando cadenaAntesDeUnSaltoDeLinea con numAEmpezar de: %d\tcon numero caracteres archivo: %d\n", *numAEmpezar, numCaracteresArchivo);
  unsigned char * cadenaCreada = NULL;
  int tamCadenaCreada = 0;
  for(; ((*numAEmpezar) < numCaracteresArchivo) && (arrayCaracteresArchivo[(*numAEmpezar)] != '\n'); (*numAEmpezar)++)
    addACadenaUnsigned(&cadenaCreada, arrayCaracteresArchivo[(*numAEmpezar)], &tamCadenaCreada);
  cadenaCreada[(*numAEmpezar)] = '\0';
  (*numAEmpezar)++;
  printf("\nLa cadena es: %s\n", cadenaCreada);
  return cadenaCreada;
}

void addACadena(char ** arrayAAgregar, char charAAgregar, int * tamArreglo)
{
  printf("\tIniciando addACadena\n");
  if((*tamArreglo) == 0)
  {
    (*tamArreglo)++;
    (*arrayAAgregar) = (char *) malloc(sizeof(char) * ((*tamArreglo)));
    if((*arrayAAgregar) == NULL)
      exit(-1);
	(*arrayAAgregar)[(*tamArreglo) - 1] = charAAgregar;
  }
  else
  {
    printf("\tAndo en el else\n");
    (*tamArreglo)++;
    (*arrayAAgregar) = realloc(*arrayAAgregar, *tamArreglo);
    if((*arrayAAgregar) == NULL)
      exit(-1);
    (*arrayAAgregar)[(*tamArreglo) - 1] = charAAgregar;
  }
}

void addACadenaUnsigned(unsigned char ** arrayAAgregar, char charAAgregar, int * tamArreglo)
{
  if(*tamArreglo == 0)
  {
    (*arrayAAgregar) = malloc(sizeof(unsigned char) * (++(*tamArreglo)));
  	if((*arrayAAgregar) == NULL)
      exit(-1);
	(*arrayAAgregar)[(*tamArreglo) - 1] = charAAgregar;
  }
  else
  {
    (*tamArreglo)++;
    (*arrayAAgregar) = realloc(arrayAAgregar, *tamArreglo);
    if((*arrayAAgregar) == NULL)
      exit(-1);
    (*arrayAAgregar)[(*tamArreglo) - 1] = charAAgregar;
  }
}

void llenarArrayCaracteres(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar, Caracter ** arrayCaracteres, int * tamArrayCaracteres)
{
  printf("\nIniciando llenarArrayCaracteres con numero a empezar de: %d\n", *numAEmpezar);

  for(; *(numAEmpezar) < numCaracteresArchivo && !buscarFinTablaEquivalencias(arrayCaracteresArchivo, numCaracteresArchivo, numAEmpezar); (*numAEmpezar)++)
  {
    printf("Caracter cargado %c\n", arrayCaracteresArchivo[(*numAEmpezar)]);
    unsigned char caracterAGuardar = arrayCaracteresArchivo[(*numAEmpezar)];
    printf("Caracter a guardar%c\n", caracterAGuardar);
    (*numAEmpezar)++;
    printf("Enviamos");
    unsigned char * cadenaDeBits = cadenaAntesDeUnSaltoDeLineaUnsigned(arrayCaracteresArchivo, numCaracteresArchivo, numAEmpezar);
    printf("%s", cadenaDeBits);
    addAArrayCaracteres((*arrayCaracteres), caracterAGuardar, cadenaDeBits, tamArrayCaracteres);
    printf("%s", (*arrayCaracteres)[(*numAEmpezar)]->cadenaDeBits);
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
  if((*tamArrayAAgregar) == 0)
  {
    (*tamArrayAAgregar)++;
    arrayAAgregar = (Caracter *)malloc(sizeof(Caracter) * ((*tamArrayAAgregar)));
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