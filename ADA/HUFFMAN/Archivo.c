#include <stdio.h>
#include <stdlib.h>

int numeroDeElementosEnArchivo(FILE *archivo)
{
    int i = 0, c;

    rewind(archivo);
    while((c = fgetc(archivo)) != EOF)
        i++;

    return i;
}

char* obtenerElementosDeArchivo(FILE *archivo, int numeroDeElementos)
{
    unsinged char *elem;
    int c, i = 0;

    elem = (char*)calloc(numeroDeElementos, sizeof(char));

    if(elem == NULL)
        return NULL;

    rewind(archivo);
    while((c = fgetc(archivo)) != EOF)
        elem[i++] = (unsinged char)c;

    return elem;
}
