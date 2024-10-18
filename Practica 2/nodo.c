#ifndef NODO_C
#define NODO_C

#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"

int crearNodo(Nodo *n)
{
	Nodo m= NULL;
	
	m= (Nodo) malloc(sizeof(t_nodo));
	
	if (m==NULL)
	  return(0);
	
	m->enlaceA= NULL;
	m->elem = 0;
	m->enlaceB= NULL;
	
	*n= m;
	
	return(1);
}

int destruirNodo(Nodo *n)
{
	Nodo aux= NULL;
	
	if (*n==NULL)
	  return(0);
	  
	aux= *n;

	aux->enlaceA= NULL;	
	aux->enlaceB= NULL;
		
	free(aux);
	
	*n= NULL;
	
	return(1);
}

int escribirElemento(Nodo n, int e)
{
	if (n==NULL)
	  return(0);
	  
	n->elem= e;					// copia de direcciones
		
	return(1);
}

int conectarEnlaceA(Nodo n, Nodo eA)
{
	if (n==NULL)
	  return(0);
	  
	n->enlaceA= eA;				// copia de la referencia
	
	return(1);
}

int conectarEnlaceB(Nodo n, Nodo eB)
{
	if (n==NULL)
	  return(0);
	  
	n->enlaceB= eB;
	
	return(1) ;
}

/* funcion ejemplo para multiples enlaces
int conectarEnlaceX(Nodo n, Nodo eX, int k)
{
	if (n==NULL)
	  return(FALSO);
	  
	n->enlaces[k]= eX;
	
	return(VERDADERO) ;
}
*/

int consultarEnlaceA(Nodo n, Nodo *eA)
{
	if (n==NULL)
	  return(0);
	  
	*eA= n->enlaceA;
	
	return(1) ;
}

int consultarEnlaceB(Nodo n, Nodo *eB)
{
	if (n==NULL)
	  return(0);
	  
	*eB= n->enlaceB;
	
	return(1) ;
}

int desconectarEnlaceA(Nodo n)
{
	if (n==NULL)
	  return(0);
	  
	n->enlaceA= NULL;
	
	return(1) ;
}

int desconectarEnlaceB(Nodo n)
{
	if (n==NULL)
	  return(0);
	  
	n->enlaceB= NULL;
	
	return(1) ;
}

#endif
