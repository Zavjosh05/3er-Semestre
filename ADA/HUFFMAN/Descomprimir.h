#pragma once
#include "Nodo.h"
#include <stdio.h>

#ifndef Descomprimir
#define Descomprimir

void descomprimir(char * rutaArchivo, char * nombreArchivo, char * extension);


/**
* Comprueba si la cadena palabraBuscar está en la cadena arrayCaracteresArchivo
*
* @param arrayCaracteresArchivo Cadena donde se busca
* @param numCaracteresArchivo Tamaño de la de cadena donde se busca
* @param palabraABuscar Palabra donde que se busca
* @param numAEmpezar Posición de la lista donde se quiere empezar a buscar
* @return se enviara 1 o 0 dependiendo si la cadena está en la cadena a buscar
*/
int comprobarCadenaEsta(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, char * palabraABuscar, int * numAEmpezar);

/**
* Comprueba si la cadena palabraBuscar está en la cadena arrayCaracteresArchivo
*
* @param arrayCaracteresArchivo Cadena donde se busca
* @param numCaracteresArchivo Tamaño de la de cadena donde se busca
* @param palabraABuscar Palabra donde que se busca
* @param numAEmpezar Posición de la lista donde se quiere empezar a buscar
* @return se enviara 1 o 0 dependiendo si la cadena está en la cadena a buscar
*/
int comprobarCadenaEstaSigned(char * arrayCaracteresArchivo, int numCaracteresArchivo, char * palabraABuscar, int * numAEmpezar);

/**
 * Nos proporcionara una cadena que esté antes de un salto de linea, esta función para cuando detecta un saldo de linea
 * @param arrayCaracteresArchivo Cadena donde se busca la cadena antes del salto de linea
 * @param numCaracteresArchivo Tamaño de la cadena donde se busca
 * @param numAEmpezar numero donde se empieza a buscar
 * @return Se regresara la cadena que hay antes de cada salto de linea
 */
char * cadenaAntesDeUnSaltoDeLinea(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar);

char * fcadenaAntesDeUnSaltoDeLinea(FILE * archivo, int numCaracteresArchivo);

unsigned char * fcadenaAntesDeUnSaltoDeLineaUnsigned(FILE * archivo, int numCaracteresArchivo);

/**
 * Nos proporcionara una cadena que esté antes de un salto de linea, esta función para cuando detecta un saldo de linea
 * @param arrayCaracteresArchivo Cadena donde se busca la cadena antes del salto de linea
 * @param numCaracteresArchivo Tamaño de la cadena donde se busca
 * @param numAEmpezar numero donde se empieza a buscar
 * @return Se regresara la cadena que hay antes de cada salto de linea
 */
unsigned char * cadenaAntesDeUnSaltoDeLineaUnsigned(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar);


/**
 * Aquí se añade un caracter al arreglo que se enviara
 *
 * @param arrayAAgregar Es la cadena donde se agregara el caracter
 * @param charAAgregar	Es el caracter a agregar
 * @param tamArreglo		Es el tamaño actual del arreglo
 */
void addACadena(char ** arrayAAgregar, char charAAgregar, int * tamArreglo);

/**
 * Aquí se añade un caracter al arreglo que se enviara
 *
 * @param arrayAAgregar Es la cadena donde se agregara el caracter
 * @param charAAgregar	Es el caracter a agregar
 * @param tamArreglo		Es el tamaño actual del arreglo
 */
void addACadenaUnsigned(unsigned char ** arrayAAgregar, unsigned char charAAgregar, int * tamArreglo);

/**
 * Aquí se llena el array de caracteres, con su respectiva información
 *
 * @param arrayCaracteresArchivo Es la cadena donde se buscara nuestra tabla de equivalencias
 * @param numCaracteresArchivo Es el tamaño del arreglo donde se buscara
 * @param numAEmpezar Es el punto donde se empezara dentro del array
 * @param arrayCaracteres Es el array de caracteres donde guardaremos la información
 * @param tamArrayCaracteres Es el tamaño actual del tamaño del arreglo de caracteres
 */
void llenarArrayCaracteres(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar, Caracter ** arrayCaracteres, int * tamArrayCaracteres);

/**
 * Aqui se buscara el caracter FIN para terminar la tabla de equivalencias
 *
 * @param arrayCaracteresArchivo Es el arreglo donde se buscara nuestra tabla de equivalencias
 * @param numCaracteresArchivo Es el tamaño de nuestra tabla de equivalencias
 * @param numAEmpezar el numero donde se empezara a buscar
 * @return Retornara un 0 o 1, dependiendo si se encontro el fin
 */
int buscarFinTablaEquivalencias(unsigned char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar);

/**
 * Aquí se añade un caracter al arreglo de caracteres
 *
 * @param arrayAAgregar Es la cadena donde se agregara el caracter
 * @param caracter Es el caracter que se va a agregar
 * @param cadenaEquivalenteBits Es la cadena equivalente en bits relacionada con el caracter recibido
 * @param tamArrayAAgregar Es el tamaño del arreglo que se está generando
 */
void addAArrayCaracteres(Caracter * arrayAAgregar, unsigned char caracter, unsigned char * cadenaEquivalenteBits, int * tamArrayAAgregar);
#endif //Descomprimir