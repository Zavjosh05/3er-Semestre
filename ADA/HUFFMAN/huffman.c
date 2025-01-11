#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *entrada, *salida, *frecuencias;

    entrada = fopen(*argv, "r");
    salida = fopen("codificacion.dat","w");
    frecuencias = fopen("frecuencias.txt","w");


    return 0;
}

//me tengo que ir, ya no lo acabe esta funcion
int verificacionDat(char *archivo)
{
    int i = 0, j, k = 0;
    char tipo;

    while(archivo[i] != '\0')
    {
        if(archivo[i] == '.')
            j++;
        i++;
    }


    j = i;
    while(archivo[j] != '.' && j > 0)
        k++;
}