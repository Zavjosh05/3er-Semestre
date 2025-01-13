#ifndef NODO_H
#define NODO_H

typedef struct caracter
{
    unsigned char elem;
    int frecuencia;
    unsigned char * cadenaDeBits;
    int tamCadena;
}*Caracter, t_caracter;

typedef struct nodo
{
    Caracter elemento;
    struct nodo *izq, *der;
}*Nodo, t_nodo;

int crearNodo(Nodo*);
int crearCaracter(Caracter *character);
int eliminarNodo(Nodo);
int eliminarCaracter(Caracter character);
int asignarElementoNodo(Nodo,char);
int asignarConexionNodoIzquierda(Nodo,Nodo);
int asignarConexionNodoDerecha(Nodo,Nodo);
int asignarConexionesNodo(Nodo,Nodo,Nodo);

#endif //NODO_H
