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
    ordenarArregloDeCaracteresAsc(arregloCaracter,tArr);
    arbol = generarArbolDeNodos(arregloCaracter,tArr);
	asignarCadenasDeBits(arbol, arregloCaracter,tArr,arregloDeBits,0);
	free(*arregloDeBits);
    free(arregloDeBits);
    ordenarArregloDeCaracteresDsc(arregloCaracter,tArr);
    *numeroDeCaracteres = tArr;

    return arregloCaracter;

}

unsigned char* generarCodificacoDelContenido(Caracter *tablaDeEquivalencias, int tamTabla, unsigned char *contenidoDelArchivo, int tamContenido,
                                             int *tamContenidoCodificado)
{
	int i, j, pos, ind = 0;
	unsigned char *contenidoCodificado;
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

unsigned char* cadenaDeTablaDeEquivalencias(Caracter *tablaDeEquivalencias, int tamTabla, int *tamTablaCadena)
{
	int i, j, ind, iInicio, iFin, iExtencio, iNom;
    unsigned char *cadenaDeTablaDeEquivalencias, inicio[] = "INICIO", fin[] = "FIN";

    for(i = 0; i < tamTabla; i++)
    	*tamTablaCadena += tablaDeEquivalencias[i]->tamCadena+1;//Esta suma concidera el espacio para la cadena de bits y el caracter
    *tamTablaCadena += tamTabla-1;//tamTabla-1 representa el numero de saltos de linea que se van a agregar en la cadena

    cadenaDeTablaDeEquivalencias = (unsigned char*)calloc(*tamTablaCadena, sizeof(unsigned char));
    cadenaDeTablaDeEquivalencias[*tamTablaCadena] = '\0';
    ind = 0;

    for(i = 0; i < tamTabla; i++)
    {
    	cadenaDeTablaDeEquivalencias[ind++] = tablaDeEquivalencias[i]->elem;
        for(j = 0; j < tablaDeEquivalencias[i]->tamCadena; j++)
			cadenaDeTablaDeEquivalencias[ind++] = tablaDeEquivalencias[i]->cadenaDeBits[j];
        if(i < tamTabla-1)
        	cadenaDeTablaDeEquivalencias[ind++] = '\n';
    }
    printf("ind: %d, tamTablaCadena: %d\n",ind, *tamTablaCadena);

	return cadenaDeTablaDeEquivalencias;
}

unsigned char* cadenaConTablaY(unsigned char *tablaDeEquivalencias, unsigned char *contenidoDelArchivoCodificado)
{

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

/**
* Funcion principal que engloba todos los procesos para comprimir mediante el metodo de Huffman
* @param fuente apuntador hacia el archivo que queremos comprimir
* @param destino apuntador hacia el archivo donde se almacenara la informacion comprimida
*/
void codificacionHuffman(char * rutaSinNombreArchivo, char * nombreArchivo, char * extension)
{
    Caracter *arregloDeCaracteres;
    unsigned char *elementosDelArchivo, *contenidoCodificado, *cadenaDeTabla;
    char *rutaFuente, *rutaDestino, *rutaFrecuencia;
    int numDeElementos, numDeCaracteres, tamContenidoCodificado, numCadenaDeTabla,
        tamFuente, tamDestino, tamFrecuencia;
    FILE *fuente, *destino, *frecuencia;

	rutaFuente = concaternarRutaNombreYExtension(rutaSinNombreArchivo, nombreArchivo, extension, &tamFuente);
	rutaDestino = concaternarRutaNombreYExtension(rutaSinNombreArchivo,nombreArchivo, ".dat", &tamDestino);
	rutaFrecuencia = concaternarRutaNombreYExtension(rutaSinNombreArchivo,nombreArchivo, "f.txt", &tamFrecuencia);

    fuente = fopen(rutaFuente, "r");
    if(fuente == NULL) exit(-1);
    destino = fopen(rutaDestino, "wb");
    if(destino == NULL) exit(-1);
    frecuencia = fopen(rutaFrecuencia, "w+");
    if(frecuencia == NULL) exit(-1);

    elementosDelArchivo = obtenerElementosDeArchivo(fuente,&numDeElementos);
    printf("%s\n", elementosDelArchivo);
    arregloDeCaracteres = generarTablaDeEquivalencias(elementosDelArchivo, numDeElementos, &numDeCaracteres);
    imprimirArregloDeCaracter(arregloDeCaracteres, numDeCaracteres);
	contenidoCodificado = generarCodificacoDelContenido(arregloDeCaracteres, numDeCaracteres, elementosDelArchivo,
                                                        numDeElementos,&tamContenidoCodificado);
    cadenaDeTabla = cadenaDeTablaDeEquivalencias(arregloDeCaracteres, numDeCaracteres, &numCadenaDeTabla);
    printf("contenidoCodificado: %s\n",contenidoCodificado);
    printf("cadenaDeTabla: \n%s\n",cadenaDeTabla);
    fclose(fuente);

    escribirArchivoNormal(frecuencia, cadenaDeTabla, numCadenaDeTabla);

}




