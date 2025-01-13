#ifndef ARCHIVO_H
#define ARCHIVO_H
#include<stdio.h>

int numeroDeElementosEnArchivo(FILE*);
unsigned char* obtenerElementosDeArchivo(FILE*,int*);
int escribirArchivoNormal(FILE *archivoDestino, unsigned char *cadena, int tamCadena);

#endif //ARCHIVO_H
