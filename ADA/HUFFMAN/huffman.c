#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo.h"
#include "archivo.h"

int verificacionDat(char *archivo)
{
    int i = 0, j = 0, k = 0, ind = 0;
    char *tipo, dat[3] = "dat";

    while(archivo[i] != '\0')
    {
        j += (ind)?(1):(0);
        if(archivo[i] == '.')
          (ind == 1) ? j = 0: ind == 0;
        i++;
    }
    if(j == 3)
    {
        tipo = (char*)calloc(j, sizeof(char));
        ind = 0;
        while(archivo[i-k-1] != '\0' && k < j)
        {
            tipo[2-k] = archivo[i-k-1];
            if(tipo[2-k] != dat[2-k])
                return 0;
            k++;
        }
        free(tipo);
        return 1;
    }
    else return 0;
}

void nombreDelArchivoComprimido(char *archivo)
{
    int i = 0,k;
    char dat[3] = "dat";

    while(archivo[i] != '\0')
        i++;

    for(k = 2; k >= 0; k--)
        archivo[i-1-k] = dat[2-k];
}

int numeroDeElementosDeUnArreglo(char *arr)
{
    int i = 0;

    while(arr[i] != '\0')
        i++;
    return i;
}

int busquedaLinealDeElemento(unsigned char *arreglo, int tArreglo, int elemento)
{
    if(arreglo == NULL || tArreglo == 0) return 0;

    int i;
    for(i = 0; i < tArreglo; i++)
        if(arreglo[i] == elemento)
            return 1;
    return 0;
}

unsigned char *arregloDeCaractersUnicos(unsigned char *elementosDelArchivo, int numeroDeElementos, int *tArr)
{
    int i;
    unsigned char *arr;
    *tArr = 0;

    arr = (unsigned char*)calloc(1, sizeof(unsigned char));

    for(i = 0; i < numeroDeElementos; i++)
    {
        if(!busquedaLinealDeElemento(arr,*tArr,elementosDelArchivo[i]))
        {
            if(tArr == 0)
                arr = (unsigned char*)calloc(1, sizeof(unsigned char));
            arr[*tArr]= elementosDelArchivo[i];
            *tArr += 1;
        }
    }

    return arr;
}

/*
* Funcion que se dedica a "castear" 
*/
Caracter* generarArregloDeCaracteres(unsigned char* arreglo, int numeroDeElementos)
{
    int i;
    Caracter *arregloCaracter, temp;

    arregloCaracter = (Caracter*)calloc(numeroDeElementos, sizeof(Caracter));
    for(i = 0; i < numeroDeElementos; i++)
    {
        crearCaracter(&temp);
        temp->elem = arreglo[i];
        arregloCaracter[i] = temp;
    }

    return arregloCaracter;
}

/*
* Esta funcion generara la tabla de equivalencias (arreglo de structs en donde ya esta asignada la cadena de equivalencia en bits)
*
* @param elementosDelArchivo Arreglo que contiene los elementos del archivo leido
* @param numeroDeElementos numero de elementos que contiene el arreglo del archivo
* @param numeroDeCaracteres apuntador que nos ayuda a recuperar el numero de caracteres (struct) que vamos a obtener
 */
Caracter* generarTablaDeEquivalencias(unsigned char *elementosDelArchivo, int numeroDeElementos,  int *numeroDeCaracteres)
{
    Caracter *arregloCaracter, temp;
    unsigned char *arr;
    int i, tArr;

    arr = arregloDeCaractersUnicos(elementosDelArchivo,numeroDeElementos,&tArr);
    arregloCaracter = (Caracter*)calloc(tArr, sizeof(Caracter));
    for(i = 0; i < tArr; i++)
    {
        crearCaracter(&temp);

        arregloCaracter[i] =
    }

    return NULL;

}

unsigned char* generarCodificacoDelContenido(Caracter *tablaDeEquivalencias, unsigned char *contenidoDelArchivo)
{

}

unsigned char* cadenaDeTablaDeEquivalencias(Caracter *tablaDeEquivalencias)
{

}

unsigned char* cadenaConTablaY(unsigned char *tablaDeEquivalencias, unsigned char *contenidoDelArchivoCodificado)
{

}

/*
* Funcion principal que engloba todos los procesos para comprimir mediante el metodo de Huffman
* @param fuente apuntador hacia el archivo que queremos comprimir
* @param destino apuntador hacia el archivo donde se almacenara la informacion comprimida
 */
void codificacionHuffman(FILE *fuente, FILE *destino)
{
    Caracter *arregloDeCaracteres;
    unsigned char *elementosDelArchivo;
    int numDeElementos, numDeCaracteres;

    elementosDelArchivo = obtenerElementosDeArchivo(fuente,&numDeElementos);

    arregloDeCaracteres = generarTablaDeEquivalencias(elementosDelArchivo, numDeElementos, &numDeCaracteres);

}




