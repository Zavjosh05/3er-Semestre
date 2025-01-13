#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

    elem = (unsigned char*)calloc(*numeroDeElementos, sizeof(char));

    if(elem == NULL)
        return NULL;

    rewind(archivo);
    for(j = 0; j < *numeroDeElementos; j++)
        elem[j] = (unsigned char)fgetc(archivo);

    return elem;
}