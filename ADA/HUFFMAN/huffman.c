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
Caracter *arregloDeCaractersUnicos(unsigned char *elementosDelArchivo, int numeroDeElementos, int *tArr)
{
    if(elementosDelArchivo == NULL || numeroDeElementos <= 0 || *tArr == 0) return NULL;

    int i, ind;
    Caracter *arr, temp = NULL;

    *tArr = 0;
    arr = (Caracter*)calloc(1, sizeof(Caracter));
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
	puts("Holan");
    arregloNodo = (Nodo*)calloc(tArr, sizeof(Nodo));
    	puts("Holan");


    for(i = 0; i < tArr; i++)
    {
        crearNodo(&temp);
        temp->elemento = arreglo[i];
        arregloNodo[i] = temp;
        temp = NULL;
    }

    printf("imprimiendo arreglo de nodos dentro de f, numElem: %d\n",tArr);
	imprimirArregloDeNodo(arregloNodo,tArr);
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
	printf("imprimir arreglo de Nodos\n:");
    imprimirArregloDeNodo(arregloNodo,tArr);

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
    printf("arr1: %p\n", arregloCaracter);
	printf("arr2: %p\n",*arregloDeBits);
    printf("NodoAct: %c\n",nodoActual->elemento->elem);
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
    unsigned char **arregloDeBits = NULL;

	arregloDeBits = (unsigned char**)malloc(sizeof(unsigned char*));
	if(arregloDeBits == NULL) exit(-1);
    *arregloDeBits = (unsigned char*)calloc(1, sizeof(unsigned char));
    if(*arregloDeBits == NULL) exit(-1);

    puts("arregloDeCaracterUni");
    arregloCaracter= arregloDeCaractersUnicos(elementosDelArchivo,numeroDeElementos,&tArr);
    int tArr2 = tArr;
    puts("ordenamiento");
    printf("1tArr = %d\n",tArr);
    ordenarArregloDeCaracteresAsc(arregloCaracter,tArr);
    imprimirArregloDeCaracter(arregloCaracter,tArr);
    printf("\nImprimo para estar seguro %s.\n", elementosDelArchivo);
    puts("arbol");
    printf("\ntArr2 = %d\n",tArr);
    arbol = generarArbolDeNodos(arregloCaracter,tArr);
//    puts("AsignarCadenasDeBits");
//    //imprimirArregloDeCaracter(arregloCaracter,tArr);
//    printf("arr1: %p\n",arregloCaracter);
//	asignarCadenasDeBits(arbol, arregloCaracter,tArr,arregloDeBits,0);
//    puts("despues");
//	free(*arregloDeBits);
//    free(arregloDeBits);
//    puts("liberando bits");
//    ordenarArregloDeCaracteresDsc(arregloCaracter,tArr);
//    *numeroDeCaracteres = tArr;

    return arregloCaracter;

}

unsigned char* generarCodificacoDelContenido(Caracter *tablaDeEquivalencias, int tamTabla, unsigned char *contenidoDelArchivo, int tamContenido,
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

unsigned char* cadenaDeTablaDeEquivalencias(Caracter *tablaDeEquivalencias, int tamTabla, int *tamTablaCadena,
                                            char * nombreDelArchivo, char * extension)
{
	int i, j, ind, iInicio, iFin, iExtencio, iNom;
    unsigned char *cadenaDeTablaDeEquivalencias = NULL;
    char inicio[] = "INICIO", fin[] = "FIN";

    for(i = 0; i < tamTabla; i++)
    	*tamTablaCadena += tablaDeEquivalencias[i]->tamCadena+1;//Esta suma concidera el espacio para la cadena de bits y el caracter
    *tamTablaCadena += tamTabla + strlen(inicio) + strlen(fin)
                       + strlen(nombreDelArchivo) + strlen(extension);//tamTabla representa el numero de saltos de
                                                                      // linea que se van a agregar en la cadena

    cadenaDeTablaDeEquivalencias = (unsigned char*)calloc(*tamTablaCadena, sizeof(unsigned char));
    cadenaDeTablaDeEquivalencias[*tamTablaCadena] = '\0';
    ind = 0;

    for(i = 0; i < strlen(inicio); i++)
      	cadenaDeTablaDeEquivalencias[ind++] = inicio[i];
    for(i = 0; i < strlen(nombreDelArchivo); i++)
    	cadenaDeTablaDeEquivalencias[ind++] = nombreDelArchivo[i];
    cadenaDeTablaDeEquivalencias[ind++] = '\n';
    for(i = 0; i < tamTabla; i++)
    {
    	cadenaDeTablaDeEquivalencias[ind++] = tablaDeEquivalencias[i]->elem;
        for(j = 0; j < tablaDeEquivalencias[i]->tamCadena; j++)
			cadenaDeTablaDeEquivalencias[ind++] = tablaDeEquivalencias[i]->cadenaDeBits[j];
        cadenaDeTablaDeEquivalencias[ind++] = '\n';
    }
    for(i = 0; i < strlen(fin); i++)
    	cadenaDeTablaDeEquivalencias[ind++] = fin[i];
    for(i = 1; i < strlen(extension); i++)
      	cadenaDeTablaDeEquivalencias[ind++] = extension[i];
    printf("ind: %d, tamTablaCadena: %d\n",ind, *tamTablaCadena);

	return cadenaDeTablaDeEquivalencias;
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
    unsigned char *elementosDelArchivo, *contenidoCodificado, *cadenaDeTabla, *cadenaDeBits;
    char *rutaFuente, *rutaDestino, *rutaFrecuencia;
    int numDeElementos, numDeCaracteres, tamContenidoCodificado, numCadenaDeTabla, numCadenaDeBits,
        tamFuente, tamDestino, tamFrecuencia;
    FILE *fuente, *destino, *frecuencia;

	rutaFuente = concaternarRutaNombreYExtension(rutaSinNombreArchivo, nombreArchivo, extension, &tamFuente);
	rutaDestino = concaternarRutaNombreYExtension(rutaSinNombreArchivo,nombreArchivo, ".dat", &tamDestino);
	rutaFrecuencia = concaternarRutaNombreYExtension(rutaSinNombreArchivo,nombreArchivo, "f.txt", &tamFrecuencia);

    fuente = fopen(rutaFuente, "rb");
    if(fuente == NULL) exit(-1);
//    destino = fopen(rutaDestino, "wb");
//    if(destino == NULL) exit(-1);
//    frecuencia = fopen(rutaFrecuencia, "w+");
//    if(frecuencia == NULL) exit(-1);

    puts("obtenerelementosArchivo");
    elementosDelArchivo = obtenerElementosDeArchivoBin(fuente,&numDeElementos);
    printf("cadena: %s, numElem: %d\n",elementosDelArchivo, numDeElementos);
    fclose(fuente);
    puts("generarTablaDeEquivalencias");
    arregloDeCaracteres = generarTablaDeEquivalencias(elementosDelArchivo, numDeElementos, &numDeCaracteres);
//    puts("impresion");
//    imprimirArregloDeCaracter(arregloDeCaracteres, numDeCaracteres);
//    puts("generarCodficcion");
//	contenidoCodificado = generarCodificacoDelContenido(arregloDeCaracteres, numDeCaracteres, elementosDelArchivo,
//                                                        numDeElementos,&tamContenidoCodificado);
//    puts("hola");
//    cadenaDeTabla = cadenaDeTablaDeEquivalencias(arregloDeCaracteres, numDeCaracteres, &numCadenaDeTabla,
//                                                     nombreArchivo, extension);
//    printf("contenidoCodificado: %s, %d\n",contenidoCodificado, tamContenidoCodificado);
//    printf("cadenaDeTabla: \n%s\n",cadenaDeTabla);
//    fclose(fuente);
//    escribirArchivoNormal(frecuencia, cadenaDeTabla, numCadenaDeTabla);
//	fclose(frecuencia);
//    cadenaDeBits = contenidoCodificadoABits(contenidoCodificado, tamContenidoCodificado, &numCadenaDeBits);
//    printf("numCadenaDeBits: %d\n", numCadenaDeBits);
//    printf("cadena de Bits: %s\ncadena de Bits:\t", cadenaDeBits);
//    for(int i = 0; i < numCadenaDeBits; i++)
//      	printf("%d ",cadenaDeBits[i]);
//
//    escribirArchivoBinario(destino, cadenaDeBits, numCadenaDeBits);
}




