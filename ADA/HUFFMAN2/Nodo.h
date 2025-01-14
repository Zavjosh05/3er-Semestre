#ifndef NODO_H
#define NODO_H

typedef struct caracter
{
    int elem;
    int frecuencia;
    unsigned char  *cadenaDeBits;
    int tamCadena;
}*Caracter, t_caracter;


typedef struct nodo
{
    Caracter elemento;
    struct nodo *izq, *der;
    int esPadre;
}*Nodo, t_nodo;

/**
* Funcion encargada de crear una instancia de la estructura nodo
* @param node nodo el cual se quiere crear
*/
int crearNodo(Nodo*);
/**
* Funcion encargada de crear una instancia de la estructura nodo
* @param node nodo el cual se quiere crear
*/
int crearNodoPadre(Nodo*);
/**
* Funcion encargada de crear una instancia de la estructura caracter
* @param character caracter el cual se quiere crear
*/
int crearCaracter(Caracter *character);
/**
* Funcion para eliminar un struct Nodo
* @param node apuntador a struct caracter que se desea eliminar
*/
int eliminarNodo(Nodo);
/**
* Funcion para eliminar un struct Caracter
* @param character apuntador a struct caracter que se desea eliminar
*/
int eliminarCaracter(Caracter character);
/**
* Funcion que permite asignar un elemento al Caracter de un Nodo
* @param node nodo al que queremos asignar un elemento
* @param elemento elemento a agregar al nodo
*/
int asignarElementoNodo(Nodo,unsigned char);
/**
* Funcion que permite conectar un nodo con otro en su slot izquierdo
* @param node nodo al que le conectaremos otro por su slot izquierdo
* @param izq nodo que sera conectado al otro
*/
int asignarConexionNodoIzquierda(Nodo,Nodo);
/**
* Funcion que permite conectar un nodo con otro en su slot derecho
* @param node nodo al que le conectaremos otro por su slot derecho
* @param der nodo que sera conectado al otro
*/
int asignarConexionNodoDerecha(Nodo,Nodo);
/**
* Funcion para conectar un nodo con otros dos mediante sus dos flancos
* @param node nodo que va a conectar con los otros dos
* @param izq nodo que se va a conectar en el flanco izquierdo
* @param der nodo que se va a conectar en el flanco derecho
*/
int asignarConexionesNodo(Nodo,Nodo,Nodo);

void imprimirCaracter(Caracter character);
/**
* Funcion que se encarga de imprimir un arreglo de caracteres, indicando su numero de elementos
* @param arr arreglo de Caracter que queremos imprimir
* @param tArr tamaño del arreglo
*/
void imprimirArregloDeCaracter(Caracter *arr, int tArr);

void imprimirNodo(Nodo node);

void imprimirArregloDeNodo(Nodo *arr, int tArr);

void ordenarArregloDeNodosAsc(Nodo*,int);

void ordenarArregloDeNodosDsc(Nodo*,int);

void ordenarArregloDeCaracteresAsc(Caracter*,int);

void ordenarArregloDeCaracteresDsc(Caracter*,int);


#endif //NODO_H
