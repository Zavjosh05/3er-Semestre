#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivo.h"

int numeroDeElementosEnArchivo(FILE *archivo)
{
    int i = 0, c;

    rewind(archivo);
    while((c = fgetc(archivo)) != EOF)
        i++;

    return i;
}

unsigned char * obtenerElementosDeArchivo(FILE *archivo, int *numeroDeElementos)
{
    unsigned char *elem;
    int c, j;

    *numeroDeElementos = numeroDeElementosEnArchivo(archivo);

    elem = (unsigned char*)calloc(*numeroDeElementos, sizeof(unsigned char));

    if(elem == NULL)
        return NULL;

    rewind(archivo);
    for(j = 0; j < *numeroDeElementos; j++)
        elem[j] = (unsigned char)fgetc(archivo);

    return elem;
}

int * obtenerElementosDeArchivoBin(FILE *archivo, int *numeroDeElementos)
{
    int *elem = NULL, i;

    *numeroDeElementos = numeroDeElementosEnArchivo(archivo);

    elem = (int*)malloc(sizeof(int)*(*numeroDeElementos+1));
    if(elem == NULL)
        return NULL;
    rewind(archivo);
    for(i = 0; i < *numeroDeElementos; i++)
        elem[i] = (int)fgetc(archivo);

//    printf("impresion de cadena: %d\n",*numeroDeElementos);
//    for(i = 0; i < *numeroDeElementos; i++)
//        printf("%d ", elem[i]);
//    printf("\n");

    return elem;
}

int escribirArchivoNormal(FILE *archivoDestino, unsigned char *cadena, int tamCadena)
{
  	if(cadena == NULL || tamCadena == 0 || cadena == NULL)
          return 0;

	int i;

    rewind(archivoDestino);
    for(i = 0; i < tamCadena; i++)
		fputc(cadena[i], archivoDestino);

    return 1;
}

int escribirArchivoBinario(FILE *archivoDestino, unsigned char *cadena, int tamCadena)
{
  	if(cadena == NULL || tamCadena == 0 || cadena == NULL)
          return 0;

	fwrite(cadena, sizeof(unsigned char), tamCadena, archivoDestino);

    return 1;
}