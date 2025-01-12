#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(int argc, char **argv)
{
    FILE *entrada, *salida, *frecuencias;
    int num, *elementosDeArchivo = &num;

    entrada = fopen(*++argv, "r");
    if (entrada == NULL)
    {
        puts("Error al abrir el archivo");
        exit(-1);
    }

    if(verificacionDat(*argv))
        printf("Si es dat");
    else
    {
        codificacionHuffman(entrada, salida);
        nombreDelArchivoComprimido(*argv);
        //salida = fopen(*argv,"w+");
        if (salida == NULL) puts("error");
        fclose(entrada);
        //fclose(salida);
    }

    return 0;
}