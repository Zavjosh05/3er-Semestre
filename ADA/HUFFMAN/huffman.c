#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Nodo.h"
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

/*
* Funcion para verficar la existencia de un elemento en un arreglo (de unsigned char)
* @param arreglo arreglo de caracteress donde se buscara el elemento
* @param tArreglo tamaño del arreglo
* @param elemento elemento a buscar en el arreglo
*/
int busquedaLinealDeElemento(Caracter *arreglo, int tArreglo, unsigned char elemento)
{
    if(arreglo == NULL || tArreglo == 0) return 0;

    int i;
    for(i = 0; i < tArreglo; i++)
        if(arreglo[i]->elem == elemento)
            return i+1;

    return 0;
}

/*
* Funcion que devuelve un arreglo de la estructura Caracteres con cada caracter unico, asignando tambien su
* frecuencia de aparicion en el arreglo proporcionado
* @param elementosDelArchivo arreglo que queremos recorrer
* @param numeroDeElementos Numero de elementos del arreglo
* @param tArr apuntador a un entero que guardara la extencion del arreglo de caracteres a devolver
*/
Caracter *arregloDeCaractersUnicos(unsigned char *elementosDelArchivo, int numeroDeElementos, int *tArr)
{
    if(elementosDelArchivo == NULL || numeroDeElementos <= 0) return NULL;

    int i, ind;
    Caracter *arr, temp;
    *tArr = 0;

    for(i = 0; i < numeroDeElementos; i++)
    {
        ind = busquedaLinealDeElemento(arr,*tArr,elementosDelArchivo[i]);
        if(!ind)
        {
            crearCaracter(&temp);
            if(*tArr == 0)
                arr = (Caracter*)calloc(1, sizeof(Caracter));
            else
                arr = (Caracter*)realloc(arr,sizeof(Caracter)*(*tArr+1));
            temp->elem = elementosDelArchivo[i];
            temp->frecuencia += 1;
            arr[*tArr] = temp;
            *tArr += 1;
        }
        else
            arr[ind - 1]->frecuencia  += 1;
    }

    return arr;
}

/*
* Funcion que se dedica a "castear" de un arreglo de char a un arreglo de caracters
* @param arreglo arreglo de caracteres a castear
* @param numeroDeElementos numero de elementos en el arreglo de caracterse
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
* Funcion que "castea" un arreglo del struct Caracter a un arreglo del struct Nodo
* @param arreglo arreglo de Caracter a castear
* @param tArr tamaño del arreglo a castear
*/
Nodo* caracteresANodos(Caracter *arreglo, int tArr)
{
    Nodo *arregloNodo, temp;
    int i;

    arregloNodo = (Nodo*)calloc(tArr, sizeof(Nodo));

    for(i = 0; i < tArr; i++)
    {
        crearNodo(&temp);
        temp->elemento = arreglo[i];
        arregloNodo[i] = temp;
    }

    return arregloNodo;
}

/*
* funcion para generar un arbol binario de nodos
* @param arreglo arreglo de caracteres
* @param tArr numero de elementos del arreglo de caracteres
*/
Nodo generarArbolDeNodos(Caracter *arreglo, int tArr)
{
    Nodo *arregloNodo, padre;
    char *cadena;

    arregloNodo = caracteresANodos(arreglo, tArr);


    while(tArr > 1)
    {
        ordernarArregloDeNodosDsc(arregloNodo, tArr);
        crearNodoPadre(&padre);
        padre->elemento->frecuencia +=
            arregloNodo[tArr-1]->elemento->frecuencia + arregloNodo[tArr-2]->elemento->frecuencia;
        asignarConexionesNodo(padre, arregloNodo[tArr-1], arregloNodo[tArr-2]);
        tArr -= 1;
        arregloNodo[tArr-1] = padre;
    }

    padre = arregloNodo[0];
    free(arregloNodo);

    return padre;
}

/*
* Funcion que se encarga de copiar los primeros n elementos de una cadena (de unsigned char) a otra sin incluir '\0' al final
* de la cadena desstino
* @param destino cadena a la que queremos copiar la informacion
* @param fuente cadena que contiene la informacion que se quiere copiar
* @param n numero de elementos que se quieren copiar
*/
int strncpyJ(unsigned char *destino, unsigned char *fuente, int n)
{
  	if(destino == NULL || fuente == NULL || n <= 0)
          return 0;

	int i;

	for(i = 0; i < n; i++)
		destino[i] = fuente[i];

	return 1;
}

void asignarCadenasDeBits(Nodo nodoActual, Caracter *arregloCaracter, int tArr, unsigned char **arregloDeBits, int len)
{
  	int pos;
	unsigned char *arrBits;

	if(nodoActual->elemento->elem == '\0')
	{
        *arregloDeBits = (unsigned char*)realloc(*arregloDeBits, (len+1)*sizeof(unsigned char));
        (*arregloDeBits)[len+1] = '\0';
        (*arregloDeBits)[len] = '0';
        asignarCadenasDeBits(nodoActual->izq, arregloCaracter, tArr, arregloDeBits, len+1);
        (*arregloDeBits)[len] = '1';
        (*arregloDeBits)[len+1] = '\0';
        asignarCadenasDeBits(nodoActual->der, arregloCaracter, tArr, arregloDeBits, len+1);
	}
    else
    {
        pos = busquedaLinealDeElemento(arregloCaracter,tArr,nodoActual->elemento->elem);
        arrBits = (unsigned char*)calloc(len, sizeof(unsigned char));
        arrBits[len] = '\0';
        strncpyJ(arrBits, *arregloDeBits, len);
        arregloCaracter[pos-1]->cadenaDeBits = arrBits;
        arregloCaracter[pos-1]->tamCadena = len;
    }
}



/*
* Esta funcion generara la tabla de equivalencias (arreglo de structs en donde ya esta asignada la cadena de equivalencia en bits)
* @param elementosDelArchivo Arreglo que contiene los elementos del archivo leido
* @param numeroDeElementos numero de elementos que contiene el arreglo del archivo
* @param numeroDeCaracteres apuntador que nos ayuda a recuperar el numero de caracteres (struct) que vamos a obtener
 */
Caracter* generarTablaDeEquivalencias(unsigned char *elementosDelArchivo, int numeroDeElementos,  int *numeroDeCaracteres)
{
    Caracter *arregloCaracter, temp;
    Nodo arbol;
    int i, tArr;
    unsigned char **arregloDeBits;

	arregloDeBits = (unsigned char**)calloc(1, sizeof(unsigned char*));
	if(arregloDeBits == NULL) exit(-1);
    *arregloDeBits = (unsigned char*)calloc(1, sizeof(unsigned char));
    if(*arregloDeBits == NULL) exit(-1);

    arregloCaracter= arregloDeCaractersUnicos(elementosDelArchivo,numeroDeElementos,&tArr);
    ordernarArregloDeCaracteresAsc(arregloCaracter,tArr);
    imprimirArregloDeCaracter(arregloCaracter, tArr);
    arbol = generarArbolDeNodos(arregloCaracter,tArr);
	asignarCadenasDeBits(arbol, arregloCaracter,tArr,arregloDeBits,0);
	free(*arregloDeBits);
    free(arregloDeBits);
    ordernarArregloDeCaracteresDsc(arregloCaracter,tArr);
    printf("hodjlds;jfl;kasdj;lkajf\n\n");
	imprimirArregloDeCaracter(arregloCaracter, tArr);


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




