#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <sys/types.h>


typedef struct {
    char filename[256];       // Nom du fichier
    off_t file_size;          // Taille du fichier en octets
    off_t current_position;   // Position actuelle dans le fichier
    int file_descriptor;      // Descripteur de fichier (pour le fichier ouvert)
    // Vous pouvez ajouter d'autres membres au besoin
} file;



int myFormat(const char* partitionName, off_t partitionSize);
file* myOpen(const char* fileName);
int myWrite(file* f, const void* buffer, int nBytes);
int myRead(file* f, void* buffer, int nBytes);
void mySeek(file* f, off_t offset, int whence);

#endif /* FILE_OPERATION_H */


