#include <stdio.h>
#include <stdlib.h>

/*
* Funcion encargada de crear una instancia de la estructura nodo
*
* @param node nodo el cual se quiere crear
*/
int crearNodo(Nodo *node)
{
    *node = (Nodo)calloc(1, sizeof(t_nodo));

    if (node == NULL)
      return 0;
    return 1;
}

/*
* Funcion encargada de crear una instancia de la estructura caracter
*
* @param character caracter el cual se quiere crear
*/
int crearCaracter(Caracter *character)
{
    *character = (Caracter)calloc(1, sizeof(t_caracter));

    if (character == NULL) return 0;
    return 1;
}

int eliminarCaracter(Caracter character)
{
    free(character);

    if(character != NULL)
      return 0;
    return 1;
}

int eliminarNodo(Nodo node)
{
    free(node->elemento->cadenaDeBits);
	free(node);

	if(node != NULL) return 0;
	else return 1;
}

int asignarElementoNodo(Nodo node, char elemento)
{
    if(node == NULL || elemento == '\0') return 0;

    node->elemento->elem = elemento;
    return 1;
}

int asignarConexionNodoIzquierda(Nodo node, Nodo izq)
{
    if(node == NULL || izq == NULL) return 0;

    node->izq = izq;
    return 1;
}

int asignarConexionNodoDerecha(Nodo node, Nodo der)
{
  if(node == NULL || der == NULL) return 0;

  node->der = der;
}

int asignarConexionesNodo(Nodo node, Nodo izq, Nodo der)
{
    if(asignarConexionNodoIzquierda(node, izq) && asignarConexionNodoDerecha(node, der))
        return 1;
    else
        return 0;
}

void imprimirCaracter(Caracter character)
{
    printf("%c", character->elemento->elem);
}

void imprimirNodo("")