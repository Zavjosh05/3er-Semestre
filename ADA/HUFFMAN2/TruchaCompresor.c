#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include "huffman.h"
#include "Descomprimir.h"
#include <time.h>

int obtenerRuta(char ** rutaSinNombreArchivo, char ** nombreArchivo, char ** extension);
int comprobarCadena(char * arrayCaracteresArchivo, int numCaracteresArchivo, char * palabraABuscar);

int main()
{
	clock_t inicio, fin;
	char * rutaSinNombreArchivo = NULL;
	char * nombreArchivo = NULL;
	char * extension = NULL;

	if(!obtenerRuta(&rutaSinNombreArchivo, &nombreArchivo, &extension))
	{
		printf("Fin del programa papus\n");
		exit(0);
	}
	if (comprobarCadena(extension,(int)strlen(extension),".dat"))
	{
		inicio = clock();
		descomprimir(rutaSinNombreArchivo, nombreArchivo, extension);
		fin = clock();
	}
	else
	{
		inicio = clock();
		codificacionHuffman(rutaSinNombreArchivo, nombreArchivo, extension);
		fin = clock();
	}

	printf("Tiempo de ejecucion: %.3f\n",(double)(fin-inicio)/CLOCKS_PER_SEC);

  free(rutaSinNombreArchivo);
  free(nombreArchivo);
  free(extension);
	return 0;
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

		(*rutaSinNombreArchivo) = malloc(sizeof(char) * (tamRutaSinNombreArchivo));
		(*nombreArchivo) = malloc(sizeof(char) * (tamNombreArchivo));

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

		(*extension) = malloc(sizeof(char) * (tamExtension));
		if(*extension == NULL)
			exit(-1);

		printf("\n");

		int x = 0;

		for(; i < tamNombreArchivo; i++)
		{
      (*extension)[x] = ofn.lpstrFileTitle[i];
			x++;
		}
    (*extension)[x] = '\0';
		return 1;
	} else
	{
		printf("No se selecciono ningun archivo o se cancelo.\n");
		return 0;
	}
}

/**
* Comprueba si la cadena palabraBuscar está en la cadena arrayCaracteresArchivo
*
* @param arrayCaracteresArchivo Cadena donde se busca
* @param numCaracteresArchivo Tamaño de la de cadena donde se busca
* @param palabraABuscar Palabra donde que se busca
* @return se enviara 1 o 0 dependiendo si la cadena está en la cadena a buscar
*/
int comprobarCadena(char * arrayCaracteresArchivo, int numCaracteresArchivo, char * palabraABuscar)
{
	int contador = 0;
	for(int i = 0; i < numCaracteresArchivo && palabraABuscar[i] != '\0'; i++)
		if(arrayCaracteresArchivo[i] == palabraABuscar[i])
			contador++;
	if(contador == strlen(palabraABuscar))
		return 1;
	return 0;
}