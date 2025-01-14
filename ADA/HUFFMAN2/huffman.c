#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Nodo.h"
#include "archivo.h"
#include "huffman.h"

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
int busquedaLinealDeElemento(Caracter *arreglo, int tArreglo, int elemento)
{
    if(arreglo == NULL || tArreglo == 0)
    	return 0;

    int i;
    for(i = 0; i < tArreglo; i++)
        if(arreglo[i]->elem == elemento)
            return i+1;

    return 0;
}

/**
* Funcion que devuelve un arreglo de la estructura Caracteres con cada caracter unico, asignando tambien su
* frecuencia de aparicion en el arreglo proporcionado
* @param elementosDelArchivo arreglo que queremos recorrer
* @param numeroDeElementos Numero de elementos del arreglo
* @param tArr apuntador a un entero que guardara la extencion del arreglo de caracteres a devolver
*/
Caracter *arregloDeCaractersUnicos(int *elementosDelArchivo, int numeroDeElementos, int *tArr)
{
    if(elementosDelArchivo == NULL || numeroDeElementos <= 0) return NULL;

    int i, ind;
    Caracter *arr, temp = NULL;

    *tArr = 0;
    arr = (Caracter*)malloc(sizeof(Caracter));
    for(i = 0; i < numeroDeElementos; i++)
    {
        ind = busquedaLinealDeElemento(arr,*tArr,elementosDelArchivo[i]);
        if(!ind)
        {
            crearCaracter(&temp);
            if(*tArr > 0)
                arr = (Caracter*)realloc(arr,sizeof(Caracter)*(*tArr+1));
            temp->elem = elementosDelArchivo[i];
            temp->frecuencia += 1;
            arr[*tArr] = temp;
            temp = NULL;
            *tArr += 1;
        }
        else
            arr[ind - 1]->frecuencia  += 1;
    }
    printf("\n\nobtencion de tArr: %d\n\n",*tArr);

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
        temp = NULL;
    }

    printf("imprimiendo arreglo de nodos dentro de f, numElem: %d\n",tArr);
	//imprimirArregloDeNodo(arregloNodo,tArr);
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
    arregloNodo = caracteresANodos(arreglo, tArr);
    //imprimirArregloDeNodo(arregloNodo,tArr);

    while(tArr > 1)
    {
        ordenarArregloDeNodosDsc(arregloNodo, tArr);
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
	unsigned char *arrBits = NULL;
	if(nodoActual->esPadre)
	{
        *arregloDeBits = (unsigned char*)realloc(*arregloDeBits, (len+2)*sizeof(unsigned char));
        (*arregloDeBits)[len] = '0';
        (*arregloDeBits)[len+1] = '\0';
        asignarCadenasDeBits(nodoActual->izq, arregloCaracter, tArr, arregloDeBits, len+1);
        (*arregloDeBits)[len] = '1';
        (*arregloDeBits)[len+1] = '\0';
        asignarCadenasDeBits(nodoActual->der, arregloCaracter, tArr, arregloDeBits, len+1);
	}
    else
    {
        pos = busquedaLinealDeElemento(arregloCaracter,tArr,nodoActual->elemento->elem);
        if(pos)
        {
           arrBits = (unsigned char*)calloc(len+1, sizeof(unsigned char));
            strncpyJ(arrBits, *arregloDeBits, len);
            arrBits[len] = '\0';
            arregloCaracter[pos-1]->cadenaDeBits = arrBits;
            arregloCaracter[pos-1]->tamCadena = len;
        }
        else
            printf("por alguna razon, hay un nodo con un caracter que no se ha registrado\nEl elemento es: %c\n",
                 nodoActual->elemento->elem);

    }
}



/*
* Esta funcion generara la tabla de equivalencias (arreglo de structs en donde ya esta asignada la cadena de equivalencia en bits)
* @param elementosDelArchivo Arreglo que contiene los elementos del archivo leido
* @param numeroDeElementos numero de elementos que contiene el arreglo del archivo
* @param numeroDeCaracteres apuntador que nos ayuda a recuperar el numero de caracteres (struct) que vamos a obtener
 */
Caracter* generarTablaDeEquivalencias(int *elementosDelArchivo, int numeroDeElementos,  int *numeroDeCaracteres)
{
    Caracter *arregloCaracter, temp;
    Nodo arbol;
    int i, tArr;
    unsigned char **arregloDeBits = NULL;

	arregloDeBits = (unsigned char**)malloc(sizeof(unsigned char*));
	if(arregloDeBits == NULL) exit(-1);
    (*arregloDeBits) = (unsigned char*)malloc(sizeof(unsigned char));
    if(*arregloDeBits == NULL) exit(-1);

    puts("arregloDeCaracterUni");
    arregloCaracter= arregloDeCaractersUnicos(elementosDelArchivo,numeroDeElementos,&tArr);
    ordenarArregloDeCaracteresAsc(arregloCaracter,tArr);
    puts("arbol");
    printf("\ntArr2 = %d\n",tArr);
    arbol = generarArbolDeNodos(arregloCaracter,tArr);
    puts("AsignarCadenasDeBits");
    //imprimirArregloDeCaracter(arregloCaracter,tArr);
    printf("arr1: %p\n",arregloCaracter);
	asignarCadenasDeBits(arbol, arregloCaracter,tArr,arregloDeBits,0);
	free(*arregloDeBits);
    free(arregloDeBits);
    ordenarArregloDeCaracteresDsc(arregloCaracter,tArr);
    *numeroDeCaracteres = tArr;
    puts("si acabo GenerarTablaEquivalencias");

    return arregloCaracter;

}

unsigned char* generarCodificacoDelContenido(Caracter *tablaDeEquivalencias, int tamTabla, int *contenidoDelArchivo, int tamContenido,
                                             int *tamContenidoCodificado)
{
	int i, j, pos, ind = 0;
	unsigned char *contenidoCodificado = NULL;
    Caracter temp;

    *tamContenidoCodificado = 0;
	for(i = 0; i < tamTabla; i++)
        *tamContenidoCodificado += tablaDeEquivalencias[i]->frecuencia * tablaDeEquivalencias[i]->tamCadena;

	contenidoCodificado = (unsigned char*)calloc(*tamContenidoCodificado, sizeof(unsigned char));
	for(i = 0; i < tamContenido; i++)
	{
          pos = busquedaLinealDeElemento(tablaDeEquivalencias,tamTabla, contenidoDelArchivo[i]);
          temp = tablaDeEquivalencias[pos-1];
          for(j = 0; j < temp->tamCadena;j++)
			contenidoCodificado[ind++] = temp->cadenaDeBits[j];
	}
    contenidoCodificado[ind] = '\0';

    return contenidoCodificado;
}

unsigned char* contenidoCodificadoABits(unsigned char * contenidoCodificado, int tamContenido, int *tamContenidoBinario)
{
	unsigned char * contenidoBinario = NULL;
    int i, j, ind, cuenta, numeroDeBits, numeroDeResiduos;

    *tamContenidoBinario = 0;
    numeroDeBits = tamContenido/8;
    numeroDeResiduos = tamContenido%2;
    cuenta = 7;
    ind = 0;
	printf("numeroDeBits = %d, numeroDeResiduos = %d\n", numeroDeBits, numeroDeResiduos);
    if(numeroDeResiduos)
    	contenidoBinario = (unsigned char*)calloc(++numeroDeBits, sizeof(unsigned char));
    else
    	contenidoBinario = (unsigned char*)calloc(numeroDeBits, sizeof(unsigned char));

    printf("numeroDeBits = %d, numeroDeResiduos = %d\n", numeroDeBits, numeroDeResiduos);
    *tamContenidoBinario = numeroDeBits;

    for(i = 0; i < numeroDeBits;i++)
    {
    	if(i == numeroDeBits-1 && numeroDeResiduos)
		{
        	for(j = 0; j < 8; j++)
        	{
            	if(numeroDeResiduos)
                {
                	if(contenidoCodificado[ind++] == '0')
                		contenidoBinario[i] &= ~(1 << cuenta);
                	else
                		contenidoBinario[i] |= (1 << cuenta);
                    numeroDeResiduos--;
                }
                else
                	contenidoBinario[i] &= ~(1 << cuenta);
                cuenta--;
        	}
		}
        else
        {
			for(j = 0; j < 8;j++)
          	{
                if(contenidoCodificado[ind++] == '0')
                	contenidoBinario[i] &= ~(1 << cuenta);
                else
                	contenidoBinario[i] |= (1 << cuenta);
                cuenta--;
          	}
            cuenta = 7;
        }
    }

    return contenidoBinario;
}

void tablaDeEquivalencias(FILE * frecuencia,Caracter *tablaDeEquivalencias, int tamTabla,
                                            char * nombreDelArchivo, char * extension)
{
    int i, j;

    fprintf(frecuencia, "%s%s\n", nombreDelArchivo,extension);
    for(i = 0; i < tamTabla; i++)
    {
        fprintf(frecuencia, "%d\t", tablaDeEquivalencias[i]->elem);
        for(j = 0; j < tablaDeEquivalencias[i]->tamCadena; j++)
            fprintf(frecuencia, "%c", tablaDeEquivalencias[i]->cadenaDeBits[j]);
        if(i != tamTabla-1)
            fprintf(frecuencia, "\n");
    }
}

char * concaternarRutaNombreYExtension(char * rutaSinNombreArchivo, char * nombreArchivo, char * extension, int *tamRuta)
{
	int tRutaSin = strlen(rutaSinNombreArchivo), tNombreArch = strlen(nombreArchivo), tExtension = strlen(extension), i, ind;
	char * ruta;

    *tamRuta = 0;
    *tamRuta += tRutaSin + tNombreArch + tExtension;
    ruta = (char*)calloc(*tamRuta, sizeof(char));

    ind = 0;
    for(i = 0; i < tRutaSin; i++)
    	ruta[ind++] = rutaSinNombreArchivo[i];
    for(i = 0; i < tNombreArch; i++)
      	ruta[ind++] = nombreArchivo[i];
    for(i = 0; i < tExtension; i++)
      	ruta[ind++] = extension[i];
    ruta[ind] = '\0';

    return ruta;
}

void decodificacionHuffman(char * rutaSinNombreArchivo, char * nombreArchivo, char * extension)
{
    FILE *fuente = NULL, *destino = NULL, *frecuencia = NULL;
    Caracter *arregloDeCaracteres;
    int *elementosDelArchivo = NULL;
    unsigned char *contenidoCodificado = NULL;
    char *rutaFuente = NULL, *rutaDestino = NULL, *rutaFrecuencia = NULL, *nomDestino, *nomFrecuencias;
    int numDeElementos, numDeCaracteres, tamContenidoCodificado, numCadenaDeBits,
        tamFuente, tamDestino, tamFrecuencia, tamNomDestino;

    tamFrecuencia = (strlen(nombreArchivo)+1);
    nomFrecuencias = (char*)malloc((tamFrecuencia+1)*sizeof(char));
    strncpy(nomFrecuencias,nombreArchivo,tamFrecuencia);
    nomFrecuencias[tamFrecuencia-1] = 'f';
    nomFrecuencias[tamFrecuencia] = '\0';
    printf("%s, %d\n", nomFrecuencias, tamFrecuencia);

    rutaFuente = concaternarRutaNombreYExtension(rutaSinNombreArchivo, nombreArchivo, extension, &tamFuente);
    rutaFrecuencia = concaternarRutaNombreYExtension(rutaSinNombreArchivo, nomFrecuencias, ".txt", &tamFrecuencia);

    fuente = fopen(rutaFuente, "rb");
    if(fuente == NULL) exit(-1);
    printf("Ruta Fuente: %s\n", rutaFuente);
    printf("Ruta Frecuencia: %s\n", rutaFrecuencia);
    frecuencia = fopen(rutaFrecuencia, "r");
    if(frecuencia == NULL) exit(-1);

    fscanf(frecuencia, "%s", nomDestino);

    printf("%s\n", nomDestino);
}

/**
* Funcion principal que engloba todos los procesos para comprimir mediante el metodo de Huffman
* @param fuente apuntador hacia el archivo que queremos comprimir
* @param destino apuntador hacia el archivo donde se almacenara la informacion comprimida
*/
void codificacionHuffman(char * rutaSinNombreArchivo, char * nombreArchivo, char * extension)
{
    Caracter *arregloDeCaracteres;
    int *elementosDelArchivo = NULL;
    unsigned char *contenidoCodificado = NULL, *cadenaDeBits = NULL;
    char *rutaFuente = NULL, *rutaDestino = NULL, *rutaFrecuencia = NULL;
    int numDeElementos, numDeCaracteres, tamContenidoCodificado, numCadenaDeBits,
        tamFuente, tamDestino, tamFrecuencia;
    FILE *fuente = NULL, *destino = NULL, *frecuencia = NULL;

	rutaFuente = concaternarRutaNombreYExtension(rutaSinNombreArchivo, nombreArchivo, extension, &tamFuente);
	rutaDestino = concaternarRutaNombreYExtension(rutaSinNombreArchivo,nombreArchivo, ".dat", &tamDestino);
	rutaFrecuencia = concaternarRutaNombreYExtension(rutaSinNombreArchivo,nombreArchivo, "f.txt", &tamFrecuencia);

    fuente = fopen(rutaFuente, "rb");
    if(fuente == NULL) exit(-1);
    destino = fopen(rutaDestino, "wb");
    if(destino == NULL) exit(-1);
    frecuencia = fopen(rutaFrecuencia, "w+");
    if(frecuencia == NULL) exit(-1);

    puts("obtenerelementosArchivo");
    elementosDelArchivo = obtenerElementosDeArchivoBin(fuente,&numDeElementos);
    fclose(fuente);
    puts("generarTablaDeEquivalencias");
    arregloDeCaracteres = generarTablaDeEquivalencias(elementosDelArchivo, numDeElementos, &numDeCaracteres);
//    puts("impresion");
    //imprimirArregloDeCaracter(arregloDeCaracteres, numDeCaracteres);
    puts("Proceso de codificacion");
	contenidoCodificado = generarCodificacoDelContenido(arregloDeCaracteres, numDeCaracteres, elementosDelArchivo,
                                                        numDeElementos,&tamContenidoCodificado);
    tablaDeEquivalencias(frecuencia,arregloDeCaracteres, numDeCaracteres,
                                                     nombreArchivo, extension);
    //printf("contenidoCodificado: %s, %d\n",contenidoCodificado, tamContenidoCodificado);
    fclose(fuente);
//    escribirArchivoNormal(frecuencia, cadenaDeTabla, numCadenaDeTabla);
	fclose(frecuencia);
    cadenaDeBits = contenidoCodificadoABits(contenidoCodificado, tamContenidoCodificado, &numCadenaDeBits);
//    printf("numCadenaDeBits: %d\n", numCadenaDeBits);
//    for(int i = 0; i < numCadenaDeBits; i++)
//      	printf("%d ",cadenaDeBits[i]);

    escribirArchivoBinario(destino, cadenaDeBits, numCadenaDeBits);
    free(rutaFuente);
    free(rutaDestino);
    free(rutaFrecuencia);
    free(elementosDelArchivo);
    free(contenidoCodificado);
    free(cadenaDeBits);
}




