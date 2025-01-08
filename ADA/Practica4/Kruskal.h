#ifndef KRUSKAL_H
#define KRUSKAL_H

int verificarExistenciaDeNodo(Nodo,Nodo*,int);
int verificarExistenciaDeArista(Arista,Arista*,int);
Nodo obtenerNodoDeCaracter(char,Nodo*,int);
Nodo ingresarNodoParaKruskal(Nodo*,int,int);
int verficarConexionEntreNodos(Nodo,Nodo,Arista*,int);
Nodo* busquedaExaustivaEnSubgrafo(Nodo,Nodo,Arista*,int,int*);
void procesoKruskal(Nodo,Nodo,Nodo*,int,Arista*,int);
void algoritmoKruskal(Nodo grafo);
int verificarExistenciaDeNodo(Nodo node, Nodo *arrNode, int numNode);

#endif //KRUSKAL_H
