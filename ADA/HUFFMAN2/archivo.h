#ifndef ARCHIVO_H
#define ARCHIVO_H
#include<stdio.h>

int numeroDeElementosEnArchivo(FILE*);
unsigned char* obtenerElementosDeArchivo(FILE*,int*);
unsigned char * obtenerElementosDeArchivoBin(FILE *archivo, int *numeroDeElementos);
int escribirArchivoNormal(FILE *archivoDestino, unsigned char *cadena, int tamCadena);
int escribirArchivoBinario(FILE *archivoDestino, unsigned char *cadena, int tamCadena);

#endif //ARCHIVO_H
