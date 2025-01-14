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

unsigned char * obtenerElementosDeArchivoBin(FILE *archivo, int *numeroDeElementos)
{
    unsigned char *elem = NULL;

    *numeroDeElementos = numeroDeElementosEnArchivo(archivo);

    elem = (unsigned char*)malloc(sizeof(unsigned char)*(*numeroDeElementos+1));
    if(elem == NULL)
        return NULL;
    rewind(archivo);
    fread(elem, sizeof(unsigned char), *numeroDeElementos, archivo);
    //fgets(elem, *numeroDeElementos, archivo);
    elem[*numeroDeElementos] = '\0';

    return elem;
}

int escribirArchivoNormal(FILE *archivoDestino, unsigned char *cadena, int tamCadena)
{
  	if(cadena == NULL || tamCadena == 0 || cadena == NULL)
          return 0;

	int i;

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