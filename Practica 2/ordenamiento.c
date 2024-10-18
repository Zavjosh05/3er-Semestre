#include<stdio.h>
#include"nodo.h"

void shellSort(int*,int);
void impArrInt(int*,int);
Nodo insertTree(Nodo,int);
void impOrdTree(Nodo);
void createTree(Nodo,int*,int);
void sortedTreeArr(Nodo,int**);
void treeSort(int*,int);

int main(void)
{

    int arr[5] = {5,4,8,2,1};

    impArrInt(arr,5);
    //treeSort(arr,5);
    shellSort(arr,5);
    impArrInt(arr,5);

    return 0;
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

void impArrInt(int *arr, int n)
{
    int i;

    for(i = 0; i < n; i++)
        if(i == (n-1))
            printf("%d\n",*(arr+i));
        else
            printf("%d, ",*(arr+i));
    putchar('\n');
}
