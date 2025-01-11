#include <stdio.h>
#include <stdlib.h>

int verificacionDat(char*);

int main(int argc, char **argv)
{
    //FILE *entrada, *salida, *frecuencias;

    //entrada = fopen(*argv, "r");
    //salida = fopen("codificacion.dat","w");
    //frecuencias = fopen("frecuencias.txt","w");

    if(verificacionDat(*++argv))
        printf("Si es dat");
    else
        printf("No es dat");

    return 0;
}

int verificacionDat(char *archivo)
{
    int i = 0, j = 0, k = 0, ind = 0;
    char *tipo, dat[3] = "dat";

    while(archivo[i] != '\0')
    {
        j += (ind)?(1):(0);
        if(archivo[i] == '.') ind = 1;
        i++;
    }
//    printf("j: %d\n",j);
//    printf("nom: %s\n",archivo);
    if(j == 3)
    {
        tipo = (char*)calloc(j, sizeof(char));
        ind = 0;
        while(archivo[i-k-1] != '\0' && k < j)
        {
            tipo[2-k] = archivo[i-k-1];
//            printf("1: %c, 2: %c\n",tipo[2-k], dat[2-k]);
//            printf("ind: %d\n",tipo[2-k] != dat[2-k]);
            if(tipo[2-k] != dat[2-k])
                return 0;
            k++;
        }
        return 1;
    }
    else return 0;
}