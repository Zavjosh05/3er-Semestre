#ifndef HUFFMAN_H
#define HUFFMAN_H

int verificacionDat(char*);
void nombreDelArchivoComprimido(char*);
void codificacionHuffman(char * rutaSinNombreArchivo, char * nombreArchivo, char * extension);
char * concaternarRutaNombreYExtension(char * rutaSinNombreArchivo, char * nombreArchivo, char * extension, int *tamRuta);

#endif //HUFFMAN_H
