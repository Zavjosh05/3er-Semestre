#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <string.h>
int obtenerRuta(char ** rutaSinNombreArchivo, char ** nombreArchivo, char ** extension);

/*
 * Debemos tener los siguientes argumentos -lgdi32 -lcomdlg32
 *
 * */

int main()
{
  char * rutaSinNombreArchivo;
  char * nombreArchivo;
  char * extension;
  obtenerRuta(&rutaSinNombreArchivo, &nombreArchivo, &extension);
  printf("La ruta es: %s%s%s\n", rutaSinNombreArchivo, nombreArchivo, extension);
}

/**
 * Aqui obtenemos la ruta del archivo que queramos comprimir o descomprimir
 *
 * @param rutaSinNombreArchivo Devuelve la ruta sin el nombre del archivo
 * @param nombreArchivo Devuelve el nombre del archivo
 * @param
 */
int obtenerRuta(char ** rutaSinNombreArchivo, char ** nombreArchivo, char ** extension)
{
  // Estructura OPENFILENAME para configurar el diálogo
  OPENFILENAME ofn;
  char szFile[260] = {0};
  char szFileTitle[260] = {0};
  // Inicializar la estructura OPENFILENAME
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = NULL; // Ventana propietaria (NULL para consola)
  ofn.lpstrFile = szFile; // Buffer para el archivo seleccionado
  ofn.nMaxFile = sizeof(szFile); // Tamaño del buffer
  ofn.lpstrFileTitle = szFileTitle; //Guarda el nombre ya sea con la ruta completa o solo el nombre
  ofn.nMaxFileTitle = sizeof(szFileTitle); //Poniendo el tam max del titulo
  ofn.lpstrInitialDir = NULL; // Directorio inicial
  ofn.lpstrFilter = "Todos los Archivos\0"; // Filtros
  ofn.nFilterIndex = 1; // Filtro predeterminado
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; //Verifica si la ruta existe o el archivo existe
  // Mostrar el cuadro de diálogo
	if (GetOpenFileName(&ofn))
  {
		int i, j;

		int tamRutaSinNombreArchivo = strlen(ofn.lpstrFile) - strlen(ofn.lpstrFileTitle);
		int tamNombreArchivo = strlen(ofn.lpstrFileTitle);

		*rutaSinNombreArchivo = malloc(sizeof(char) * (tamRutaSinNombreArchivo));
		*nombreArchivo = malloc(sizeof(char) * (tamNombreArchivo));

		if(*rutaSinNombreArchivo == NULL || *nombreArchivo == NULL)
			exit(-1);

		for(i = 0; i < tamRutaSinNombreArchivo; i++)
			(*rutaSinNombreArchivo)[i] = ofn.lpstrFile[i];
		(*rutaSinNombreArchivo)[i] = '\0';

		for(i = 0; i < tamNombreArchivo; i++)
    {
      if(ofn.lpstrFileTitle[i] == '.')
        break;
      (*nombreArchivo)[i] = ofn.lpstrFileTitle[i];
    }
		(*nombreArchivo)[i] = '\0';
		int tamExtension = tamNombreArchivo - i;

		*extension = malloc(sizeof(char) * (tamExtension));
		if(*extension == NULL)
			exit(-1);

		printf("\n");

		int x = 0;

		for(j = i; j < tamNombreArchivo; j++)
		{
      (*extension)[x] = ofn.lpstrFileTitle[j];
			x++;
		}
    (*extension)[j] = '\0';
		return 1;
	} else
	{
		printf("No se seleccionó ningún archivo o se canceló.\n");

		return 0;
	}
}