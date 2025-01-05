//
// Created by josh on 04/01/2025.
//
#ifndef KRUSKAL_H
#define KRUSKAL_H

Nodo obtenerNodoDeCaracter(char,Nodo*,int);
Nodo ingresarNodoParaKruskal(Nodo*,int,int);
void procesoKruskal(Nodo,Nodo,Nodo*,int,Arista*,int);
void algoritmoKruskal(Nodo grafo);
int verificarExistenciaDeNodo(Nodo node, Nodo *arrNode, int numNode);

#endif //KRUSKAL_H
