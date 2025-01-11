#include <stdio.h>
#include <stdlib.h>

int verificacionDat(char *archivo)
{
    int i = 0, j = 0, k = 0, ind = 0;
    char *tipo, dat[3] = "dat";

    while(archivo[i] != '\0')
    {
        j += (ind)?(1):(0);
        if(archivo[i] == '.')
          (ind == 1) ? j = 0: ind == 0;
        i++;
    }
    if(j == 3)
    {
        tipo = (char*)calloc(j, sizeof(char));
        ind = 0;
        while(archivo[i-k-1] != '\0' && k < j)
        {
            tipo[2-k] = archivo[i-k-1];
            if(tipo[2-k] != dat[2-k])
                return 0;
            k++;
        }
        free(tipo);
        return 1;
    }
    else return 0;
}

void nombreDelArchivoComprimido(char *archivo)
{
    int i = 0,k;
    char dat[3] = "dat";

    while(archivo[i] != '\0')
        i++;

    for(k = 2; k >= 0; k--)
        archivo[i-1-k] = dat[2-k];
}

int numeroDeElementosDeUnArreglo(char *arr)
{
    int i = 0;

    while(arr[i] != '\0')
        i++;
    return i;
}




