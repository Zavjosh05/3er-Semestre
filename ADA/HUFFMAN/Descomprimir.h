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
int comprobarCadenaEsta(char * arrayCaracteresArchivo, int numCaracteresArchivo, char * palabraABuscar, int * numAEmpezar);

/**
 * Nos proporcionara una cadena que esté antes de un salto de linea, esta función para cuando detecta un saldo de linea
 * @param arrayCaracteresArchivo Cadena donde se busca la cadena antes del salto de linea
 * @param numCaracteresArchivo Tamaño de la cadena donde se busca
 * @param numAEmpezar numero donde se empieza a buscar
 * @return Se regresara la cadena que hay antes de cada salto de linea
 */
char * cadenaAntesDeUnSaltoDeLinea(char * arrayCaracteresArchivo, int numCaracteresArchivo, int * numAEmpezar);

/**
 * Aquí se añade un caracter al arreglo que se enviara
 *
 * @param arrayAAgregar Es la cadena donde se agregara el caracter
 * @param charAAgregar	Es el caracter a agregar
 * @param tamArreglo		Es el tamaño actual del arreglo
 */
void addACadena(char ** arrayAAgregar, char charAAgregar, int * tamArreglo);

#endif //Descomprimir
