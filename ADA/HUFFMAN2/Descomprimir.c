#include "Descomprimir.h"
#include <stdio.h>
#include <stdlib.h>
#include "archivo.h"
#include <string.h>
#include "Nodo.h"
#include "huffman.h"
#include "unistd.h"
#include "direct.h"

void descomprimir(char * rutaArchivo, char * nombreArchivo, char * extension)
{
  int tamRutaTablaDeFrecuencias;
  char * rutaTablaDeFrecuencias = NULL;

  rutaTablaDeFrecuencias = concaternarRutaNombreYExtension(rutaArchivo, nombreArchivo, "f.txt", &tamRutaTablaDeFrecuencias);

  FILE * archivoTablaFrecuencias = NULL;
  archivoTablaFrecuencias = fopen(rutaTablaDeFrecuencias, "r");
  if (archivoTablaFrecuencias == NULL)
  {
    printf("\nNo es encuentra la tabla de equivalencias, favor de agregar el archivo %sf.txt\n", nombreArchivo);
    exit(-1);
  }

  unsigned char * arrayCaracteresArchivoFrecuencias = NULL;

  char * nombreDelArchivoDescomprimido = NULL;

  int numCaracteresArchivoFrecuencias = 0, posicionActual = 0, tamArrayCaracteres = 0;

  int tamArchivoTablaFrecuencias = numeroDeElementosEnArchivo(archivoTablaFrecuencias);
  rewind(archivoTablaFrecuencias);

  nombreDelArchivoDescomprimido = fcadenaAntesDeUnSaltoDeLinea(archivoTablaFrecuencias, tamArchivoTablaFrecuencias);
  if (nombreDelArchivoDescomprimido == NULL)
    exit(-1);

  if(!comprobarCadenaEstaSigned(nombreDelArchivoDescomprimido, strlen(nombreDelArchivoDescomprimido), ".", &posicionActual))
  {
    printf("\aEl %sf.txt relacionado con este archivo comprimido no es el generado por TRUCHA CORPORATION\n", nombreArchivo);
    exit(-1);
  }

  Caracter * arrayCaracteres = NULL;

  nuevoLlenarArrayCaracteres(&arrayCaracteres, archivoTablaFrecuencias, &tamArrayCaracteres);

  fclose(archivoTablaFrecuencias);

  char * rutaArchivoComprimido = NULL;
  int tamRutaArchivoComprimido = 0;
  rutaArchivoComprimido = concaternarRutaNombreYExtension(rutaArchivo, nombreArchivo, extension, &tamRutaArchivoComprimido);

  FILE * archivoComprimido = NULL;
  archivoComprimido = fopen(rutaArchivoComprimido, "rb");
  if (archivoComprimido == NULL)
    exit(-1);

  unsigned char * arrayBitsEnArchivoComprimido = NULL;
  int tamArrayBitsEnArchivoComprimido = 0;

  arrayBitsEnArchivoComprimido = obtenerElementosDeArchivo(archivoComprimido, &tamArrayBitsEnArchivoComprimido);

  fclose(archivoComprimido);
  char * rutaArchivoDescomprimido = NULL;
  int tamRutaArchivoDescomprimido = 0;

  char * rutaCarpeta = NULL;
  int tamRutaCarpeta = 0;
  rutaCarpeta = concaternarRutaNombreYExtension(rutaArchivo, nombreArchivo, "-Descomprimido", &tamRutaCarpeta);

  if (!(_mkdir(rutaCarpeta)))
    printf("\nCarpeta Creada\n");
  else
    printf("\nCaperta ya existente\n");

  rutaArchivoDescomprimido = concaternarRutaNombreYExtension(rutaCarpeta,"\\", nombreDelArchivoDescomprimido, &tamRutaArchivoDescomprimido);

  printf("\n%s\n", rutaArchivoDescomprimido);

  FILE * archivoDescomprimido = NULL;
  archivoDescomprimido = fopen(rutaArchivoDescomprimido, "wb");
  if (archivoDescomprimido == NULL)
    exit(-1);


  crearArchivo(arrayCaracteres, tamArrayCaracteres, arrayBitsEnArchivoComprimido, tamArrayBitsEnArchivoComprimido, archivoDescomprimido);

  fclose(archivoDescomprimido);
  free(arrayBitsEnArchivoComprimido);
  free(rutaArchivoComprimido);
  free(rutaArchivo);
  free(rutaTablaDeFrecuencias);
  free(nombreDelArchivoDescomprimido);

  //free(arrayCaracteresArchivoFrecuencias);
  //free(arrayCaracteres);
  //arrayCaracteresArchivoFrecuencias = obtenerElementosDeArchivo(archivoTablaFrecuencias, &numCaracteresArchivoFrecuencias);
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
void nuevoLlenarArrayCaracteres(Caracter ** arrayCaracteres, FILE * archivoTablaFrecuencias, int * tamArrayCaracteres)
{
  char c;
  //unsigned char * cadenaBits = NULL;
  unsigned char cadenaBits [20];
  int caracter;
  if (archivoTablaFrecuencias == NULL)
    exit(-1);
  (*arrayCaracteres) = (Caracter *)malloc(sizeof(Caracter));

  while((c = fgetc(archivoTablaFrecuencias)) != EOF)
  {
    //free(cadenaBits);
    //cadenaBits = NULL;
    fseek(archivoTablaFrecuencias, -1, SEEK_CUR);
    //fscanf(archivoTablaFrecuencias, "%d\t", &caracter);
    fscanf(archivoTablaFrecuencias, "%d\t%s\n", &caracter, cadenaBits);
    if((*tamArrayCaracteres) == 0)
    {
      (*arrayCaracteres) = (Caracter *) malloc(sizeof(Caracter));
      if((*arrayCaracteres) == NULL)
        exit(-1);
      *(*arrayCaracteres) = (Caracter) malloc(sizeof(t_caracter));
      if((*(*arrayCaracteres)) == NULL)
        exit(-1);
      (*arrayCaracteres)[0]->elem = caracter;
      (*arrayCaracteres)[0]->frecuencia = 0;
      hacerCopiaArray(&((*arrayCaracteres)[0]->cadenaDeBits), cadenaBits);
      (*arrayCaracteres)[0]->tamCadena = sizeof(cadenaBits);
      (*tamArrayCaracteres)++;
    }
    else
    {
      (*tamArrayCaracteres)++;
      (*arrayCaracteres) = (Caracter *) realloc((*arrayCaracteres), (*tamArrayCaracteres) * sizeof(Caracter));
      if((*arrayCaracteres) == NULL)
        exit(-1);
      Caracter caracAux = (Caracter) malloc(sizeof(t_caracter));
      if((caracAux) == NULL)
        exit(-1);
      int indiceActual = (*tamArrayCaracteres) - 1;
      caracAux->elem = caracter;
      caracAux->frecuencia = 0;
      hacerCopiaArray(&(caracAux->cadenaDeBits), cadenaBits);
      caracAux->tamCadena = sizeof(cadenaBits);
      (*arrayCaracteres)[indiceActual] = caracAux;
    }
  }
}

void crearArchivo(Caracter * arrayCaracteres, int tamArrayCaracteres, unsigned char * arrayBitsEnArchivoComprimido, int tamArrayBitsEnArchivoComprimido, FILE * archivoDescomprimido)
{
  unsigned char * c = NULL;
  int tamc = 0;
  int elemSeleccionado;

  for(int i = 0 ; i < tamArrayBitsEnArchivoComprimido ; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      unsigned char a = arrayBitsEnArchivoComprimido[i] << j;
      unsigned char b = arrayBitsEnArchivoComprimido[i] << (j + 1);

      int a1 = a;
      int b1 = b;

      if( a1 > b1 )
		addACadenaUnsigned(&c, '1', &tamc);
      else
        addACadenaUnsigned(&c, '0', &tamc);
      printf("\nHola demonio\n");
      if(cadenaDeBitsIguales(c, arrayCaracteres, tamArrayCaracteres,&elemSeleccionado))
      {
        printf("\nSegún mi mamá, aquí tambien trueno, mira mi elemento seleccionado %c\n", (unsigned char) elemSeleccionado);
        fputc((unsigned char)elemSeleccionado, archivoDescomprimido);
        tamc = 0;
        free(c);
        c = NULL;
      }
    }
  }
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

int comprobarCadenaEstaSigned(char * arrayCaracteresArchivo, int numCaracteresArchivo, char * palabraABuscar, int * numAEmpezar)
{
  char xd, cd;
  int contador = 0, j = 0;
  for(; ((*numAEmpezar) < numCaracteresArchivo) && (palabraABuscar[j] != '\0'); (*numAEmpezar)++)
  {
    xd = arrayCaracteresArchivo[(*numAEmpezar)];
    cd = palabraABuscar[j];
    if(arrayCaracteresArchivo[(*numAEmpezar)] == palabraABuscar[j])
    {
      contador++;
      j++;
    }
    else
      j = 0;
  }
  if(contador == strlen(palabraABuscar))
    return 1;
  return 0;
}

char * cadenaAntesDeUnSaltoDeLinea(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar)
{
  char * cadenaCreada = NULL;
  int tamCadenaCreada = 0;
  for(; ((*numAEmpezar) < numCaracteresArchivo) && (arrayCaracteresArchivo[(*numAEmpezar)] != '\n'); (*numAEmpezar)++)
  {
    addACadena(&cadenaCreada, arrayCaracteresArchivo[(*numAEmpezar)], &tamCadenaCreada);
    printf("%s ", cadenaCreada);
  }
  cadenaCreada[(*numAEmpezar)] = '\0';
  (*numAEmpezar)++;
  return cadenaCreada;
}

char * fcadenaAntesDeUnSaltoDeLinea(FILE * archivo, int numCaracteresArchivo)
{
  char * cadenaCreada = NULL;
  int tamCadenaCreada = 0, i = 0;
  char temp = fgetc(archivo);
  for(i = 0; i < numCaracteresArchivo && (temp != '\n'); i++)
  {
    addACadena(&cadenaCreada, temp, &tamCadenaCreada);
    temp = fgetc(archivo);
  }
  cadenaCreada[tamCadenaCreada] = '\0';
  return cadenaCreada;
}

unsigned char * fcadenaAntesDeUnSaltoDeLineaUnsigned(FILE * archivo)
{
  printf("\nToy entrando a fcadenaAntesDeUnSaltoDeLineaUnsigned\n");
  unsigned char * cadenaCreada = NULL;
  int tamCadenaCreada = 0, i = 0;
  char temp = fgetc(archivo);
  while(temp != '\n' && temp != EOF)
  {
  	printf("\nHola, el char que esta entrando es: %c, con un tam de: %d\n", temp, tamCadenaCreada);
    addACadenaUnsigned(&cadenaCreada, (unsigned char) temp, &tamCadenaCreada);
    temp = fgetc(archivo);
  	printf("\nHola, el char que esta saliendo es: %c, con un tam de: %d\n", temp, tamCadenaCreada);
  }
  if(cadenaCreada == NULL)
    exit(-1);
  cadenaCreada[tamCadenaCreada] = '\0';
  return cadenaCreada;
}

unsigned char * cadenaAntesDeUnSaltoDeLineaUnsigned(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar)
{
  unsigned char * cadenaCreada = NULL;
  int tamCadenaCreada = 0;
  for(; ((*numAEmpezar) < numCaracteresArchivo) && (arrayCaracteresArchivo[(*numAEmpezar)] != '\n'); (*numAEmpezar)++)
    addACadenaUnsigned(&cadenaCreada, arrayCaracteresArchivo[(*numAEmpezar)], &tamCadenaCreada);
  cadenaCreada[(*numAEmpezar)] = '\0';
  (*numAEmpezar)++;
  return cadenaCreada;
}

void addACadena(char ** arrayAAgregar, char charAAgregar, int * tamArreglo)
{
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
    (*tamArreglo)++;
    (*arrayAAgregar) = realloc(*arrayAAgregar, *tamArreglo);
    if((*arrayAAgregar) == NULL)
      exit(-1);
    (*arrayAAgregar)[(*tamArreglo) - 1] = charAAgregar;
  }
}

void addACadenaUnsigned(unsigned char ** arrayAAgregar, unsigned char charAAgregar, int * tamArreglo)
{
  unsigned char * temp = NULL;
  if((*tamArreglo) == 0)
  {
    ++(*tamArreglo);
    (*arrayAAgregar) = (unsigned char *) malloc(sizeof(unsigned char) * ((*tamArreglo)+1));
  	if((*arrayAAgregar) == NULL)
      exit(-1);
	(*arrayAAgregar)[(*tamArreglo) - 1] = charAAgregar;
  }
  else
  {
    (*tamArreglo)++;
    (*arrayAAgregar) = (unsigned char *) realloc(temp = (*arrayAAgregar), ((*tamArreglo)+1) * sizeof(unsigned char));
    if((*arrayAAgregar) == NULL)
      exit(-1);
    (*arrayAAgregar)[(*tamArreglo) - 1] = charAAgregar;
  }
  (*arrayAAgregar)[(*tamArreglo)] = '\0';

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

void addAArrayCaracteres(Caracter * arrayAAgregar, int caracter, unsigned char * cadenaEquivalenteBits, int * tamArrayAAgregar)
{
  if((*tamArrayAAgregar) == 0)
  {
    (*tamArrayAAgregar)++;
    (*arrayAAgregar) = (Caracter)malloc(sizeof(t_caracter));
    if(arrayAAgregar == NULL)
      exit(-1);

    (*arrayAAgregar)[(*tamArrayAAgregar) - 1].elem = caracter;
    (*arrayAAgregar)[(*tamArrayAAgregar) - 1].frecuencia = 0;
    hacerCopiaArray(&((*arrayAAgregar)[(*tamArrayAAgregar) - 1].cadenaDeBits), cadenaEquivalenteBits);
    (*arrayAAgregar)[(*tamArrayAAgregar) - 1].tamCadena = strlen((char *)cadenaEquivalenteBits);
  }
  else
  {
    (*tamArrayAAgregar)++;
    (*arrayAAgregar) = realloc((*arrayAAgregar), (*tamArrayAAgregar));
    if(arrayAAgregar == NULL)
      exit(-1);
    (*arrayAAgregar)[(*tamArrayAAgregar) - 1].elem = caracter;
    (*arrayAAgregar)[(*tamArrayAAgregar) - 1].frecuencia = 0;
    hacerCopiaArray(&((*arrayAAgregar)[(*tamArrayAAgregar) - 1].cadenaDeBits), cadenaEquivalenteBits);
    (*arrayAAgregar)[(*tamArrayAAgregar) - 1].tamCadena = strlen((char *)cadenaEquivalenteBits);
  }
}

void hacerCopiaArray (unsigned char ** destino, unsigned char * origen)
{
  int i;
  int tamOrigen = tamArrayCharUnsigned(origen);
  if((*destino) != NULL)
    (*destino) = NULL;
  (*destino) = (unsigned char *)malloc(sizeof(unsigned char) * (tamOrigen));
  for(i = 0; i < tamOrigen; i++)
  {
    (*destino)[i] = origen[i];
  }
  (*destino)[i] = '\0';
}

int tamArrayCharUnsigned(unsigned char * char1)
{
  int i = 0;
  while(char1[i] != '\0')
    i++;
  return i;
}

int cadenaDeBitsIguales(unsigned char * cadenaDeBitsRecibida, Caracter * arrayCaracteres, int tamArrayCaracteres, int * bitCoincidencia)
{
  printf("\nHola perro ando buscando a %s\n", cadenaDeBitsRecibida);
  for(int i = 0; i < tamArrayCaracteres; i++)
  {
    printf("%d ", i);
    int y = 0;
    for(int j = 0; (cadenaDeBitsRecibida[j] != '\0') && (arrayCaracteres[i]->cadenaDeBits[j] != '\0'); j++)
    {
      if(cadenaDeBitsRecibida[j] == arrayCaracteres[i]->cadenaDeBits[j])
        y++;
      else
        y = 0;
    }
    if(y == tamArrayCharUnsigned(arrayCaracteres[i]->cadenaDeBits))
    {
      *bitCoincidencia = arrayCaracteres[i]->elem;
      return 1;
    }
  }
  printf("\nadios perro\n");
  return 0;
}