#include <stdio.h>
#include <stdlib.h>

int verificacionDat(char*);

int main(int argc, char **argv)
{
    //FILE *entrada, *salida, *frecuencias;

    //entrada = fopen(*argv, "r");
    //salida = fopen("codificacion.dat","w");
    //frecuencias = fopen("frecuencias.txt","w");

    if(verificacionDat(*argv))
        printf("Si es dat");
    else
        printf("No es dat");

    return 0;
}

//me tengo que ir, ya no lo acabe esta funcion
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
    if(j == 3)
    {
        tipo = (char*)calloc(j, sizeof(char));
        ind = 0;
        while(archivo[i-k-1] != '.' && k <= j)
        {
            archivo[i-k-1] = tipo[k];
            if(tipo[k] != dat[k])
                return 0;
            k++;
        }
        return 1;
    }
    else return 0;


}