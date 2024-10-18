/* Practica 2
Vazquez Sanchez Omar Jesus
Vega Cortez Jose Angel
Zavaleta Guerrero Joshua Ivan */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"nodo.h"

#define BILLION  1000000000.0

int *construyeArreglo(int,char*);
void imprimeArreglo(int*,int);

void BubbleSort(int*,int);
void QuickSort(int*,int,int);
void Insertion(int*,int);
void Selection(int*,int);
void shellSort(int*,int);
Nodo insertTree(Nodo,int);
void impOrdTree(Nodo);
void createTree(Nodo,int*,int);
void sortedTreeArr(Nodo,int**);
void treeSort(int*,int);
void Intercambia(int*,int,int);
int pivote(int*,int,int);

int main() {
    int opcion, n, *A;

    printf("Introduce que metodo de ordenamiento quieres:\n1.BubbleSort\n2.QuickSort\n3,Insertion\n4.Selection\n5.ShellSort\n6.TreeSort\n");
    scanf("%d", &opcion);

    clock_t beginT;

    double time_spent = 0.0;
    do
    {
        printf("Cuantos va a ordenar maistro?\n");
        scanf("%d", &n);
    }
    while(n > 500000 || n <= 0);

    beginT = clock();
    clock_t begin = clock();
    A = construyeArreglo(n,"numeros10millones.txt");
    clock_t end = clock();

    time_spent = (double) (end - begin);
    printf("Numero de ciclos para lectura: %f\n", time_spent);
    printf("Tiempo de lectura: %f seconds\n\n", time_spent / CLOCKS_PER_SEC);
    time_spent = 0.0;


    switch(opcion)
    {
      case 1:
        begin = clock();
        BubbleSort(A, n);
        end = clock();
        break;
      case 2:
        begin = clock();
        QuickSort(A,0,n-1);
        end = clock();
        break;
      case 3:
        begin = clock();
        Insertion(A,n);
        end = clock();
        break;
      case 4:
        begin = clock();
        Selection(A,n);
        end = clock();
        break;
      case 5:
        begin = clock();
        shellSort(A,n);
        end = clock();
        break;
      case 6:
        begin = clock();
        treeSort(A,n);
        end = clock();
        break;
      default:
        printf("\nOpcion no valida\n");
        exit(0);
    }

    time_spent =  ((double)end - (double)begin);
    printf("Numero de ciclos realizados: %f\n", time_spent);
    printf("Tiempo tomado: %f segundos\n\n", time_spent / CLOCKS_PER_SEC);
    time_spent = 0.0;

    free(A);

    clock_t endT = clock();
    time_spent =  ((double)endT - (double)beginT);
    printf("Numero de ciclos totales del programa: %f\n", time_spent);
    printf("Tiempo total del programa: %f segundos\n", time_spent / CLOCKS_PER_SEC);

    return 0;

}

int *construyeArreglo(int n,char* ar) {

    FILE *archivo;
    int *aux = NULL;
    int c = 0, t;

    if(n > 500000)
        return NULL;

    archivo = fopen(ar, "r");

    if (archivo == NULL) {
        printf("No se puede abrir el archivo\n");
        return NULL;
    }

    aux = (int *)malloc(n * sizeof(int));

    while(fscanf(archivo, "%d", &t) != EOF && c < n) {
        *(aux + c) = t;
        c++;
    }

    return aux;

    fclose(archivo);
    free(aux);

}

void imprimeArreglo(int *A, int n) {

    for(int i = 0; i < n; i++)
        printf("%d ", *(A + i));
    putchar('\n');

}

void BubbleSort(int *A, int n) {

    int i, j;

    for(i = 0; i < n-1; i++)
        for(j = 0; j < n-1; j++) {
            if(*(A + j) > *(A + j + 1))
                Intercambia(A,j,j + 1);
        }

}

void Intercambia(int *A, int i, int j) {

    int t;

    t = *(A + i);
    *(A + i) = *(A + j);
    *(A + j) = t;

}

void QuickSort(int *A, int p, int r) {

    int j;

    if(p < r) {
        j = pivote(A, p, r);
        QuickSort(A, p, j - 1);
        QuickSort(A, j+1, r);
    }

}

int pivote(int *A, int p, int r) {

    int piv = *(A + p), i = p + 1, j = r;

    while (i <= j) {
        while (i <= r && *(A + i) < piv) {
            i++;
        }
        while (j >= p && *(A + j) > piv) {
            j--;
        }
        if (i <= j) {
            Intercambia(A, i, j);
            i++;
            j--;
        }
    }
    Intercambia(A, p, j);
    return j;
}

void Insertion(int* Arreglo, int n) {
    int a;
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (Arreglo[j] < Arreglo[j - 1]) {
                a = Arreglo[j - 1];
                Arreglo[j - 1] = Arreglo[j];
                Arreglo[j] = a;
            } else {
                break;
            }
        }
    }
}

void Selection(int* Arreglo, int n) {
    int a, min, cont = 0, i, j;
    for(i = 0; i < n; i++) {
        min = i;
        for(j = i + 1; j < n; j++) {
            if(Arreglo[min] > Arreglo[j])
                min = j;
        }
        a = Arreglo[i];
        Arreglo[i] = Arreglo[min];
        Arreglo[min] = a;
    }
}

void shellSort(int *arr, int n)
{
    int sep,i,j,temp,ind = 1,count1 = 1,count2 = 1;

    for(sep = n/2; sep >= 1;sep /= 2)
        while(ind){
            ind = 0;
            for(i = sep; i < n; i++)
                if(*(arr+i) < *(arr+i-sep))
                {
                    temp = *(arr+i);
                    *(arr+i) = *(arr+i-sep);
                    *(arr+i-sep) = temp;
                    ind += 1;
                }
        }
}

Nodo insertTree(Nodo nd, int x)
{
    if(nd == NULL)
    {
        crearNodo(&nd);
        nd->elem = x;
    }
    else
    {
        if(x < nd->elem)
            nd->enlaceA = insertTree(nd->enlaceA,x);
        else
            nd->enlaceB = insertTree(nd->enlaceB,x);
    }

    return nd;
}

void createTree(Nodo nd, int *arr,int n)
{
    int i;

    nd->elem = *arr;
    for(i = 1; i < n; i++)
        nd = insertTree(nd,*(arr+i));
}

void impOrdTree(Nodo nd)
{
    if(nd != NULL)
    {
        impOrdTree(nd->enlaceA);
        printf("%d\n",nd->elem);
        impOrdTree(nd->enlaceB);
    }
}

void sortedTreeArr(Nodo nd, int **arr)
{
    if(nd == NULL) return;

    sortedTreeArr(nd->enlaceA,arr);
    *(*arr)++ = nd->elem;
    sortedTreeArr(nd->enlaceB,arr);
}

void treeSort(int *arr, int n)
{
    Nodo root = NULL;

    crearNodo(&root);
    createTree(root, arr, n);
    sortedTreeArr(root,&arr);
}

