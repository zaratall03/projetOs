#include "file_operation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int myFormat(const char* partitionName, off_t partitionSize) {
    int fd = open(partitionName, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("Erreur lors de la création de la partition");
        return -1;
    }
    
    if (ftruncate(fd, partitionSize) == -1) {
        perror("Erreur lors du tronquage de la partition");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}
// Implémentation de la fonction myOpen
file* myOpen(const char* fileName) {
    // Cette fonction doit allouer dynamiquement une nouvelle structure file et initialiser ses membres
    file* new_file = malloc(sizeof(file));
    if (new_file == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour la structure file\n");
        return NULL;
    }
    
    // Copie du nom de fichier dans la structure file
    strncpy(new_file->filename, fileName, sizeof(new_file->filename));
    new_file->filename[sizeof(new_file->filename) - 1] = '\0'; // Assurez-vous que la chaîne est terminée par un null-byte
    
    // Initialisation des autres membres
    new_file->file_size = 0;
    new_file->current_position = 0;
    new_file->file_descriptor = -1; // Initialisation à -1, car le fichier n'est pas ouvert
    
    return new_file;
}

// Implémentation de la fonction myWrite
int myWrite(file* f, const void* buffer, int nBytes) {
    // Vérification de la validité du pointeur de fichier
    if (f == NULL) {
        fprintf(stderr, "Le pointeur de fichier est NULL\n");
        return -1;
    }
    
    // Vérification de la validité de la position actuelle dans le fichier
    if (f->current_position + nBytes > f->file_size) {
        fprintf(stderr, "Impossible d'écrire au-delà de la fin du fichier\n");
        return -1;
    }
    
    // Vérification de la validité de l'opération d'écriture
    if (write(f->file_descriptor, buffer, nBytes) == -1) {
        perror("Erreur lors de l'écriture dans le fichier");
        return -1;
    }
    
    // Mise à jour de la position actuelle dans le fichier
    f->current_position += nBytes;
    
    return nBytes; // Retourne le nombre d'octets écrits
}
    

// Implémentation de la fonction myRead
int myRead(file* f, void* buffer, int nBytes) {
    // Vérification de la validité du pointeur de fichier
    if (f == NULL) {
        fprintf(stderr, "Le pointeur de fichier est NULL\n");
        return -1;
    }
    
    // Vérification de la validité de la position actuelle dans le fichier
    if (f->current_position + nBytes > f->file_size) {
        fprintf(stderr, "Impossible de lire au-delà de la fin du fichier\n");
        return -1;
    }
    
    // Simulation de la lecture dans le fichier (cette partie doit être adaptée à votre structure de fichier)
    // Nous allons simplement simuler la lecture en mettant à jour la position actuelle dans le fichier
    f->current_position += nBytes;
    
    return nBytes; // Retourne le nombre d'octets lus
}

// Implémentation de la fonction mySeek
void mySeek(file* f, off_t offset, int whence) {
    // Vérification de la validité du pointeur de fichier
    if (f == NULL) {
        fprintf(stderr, "Le pointeur de fichier est NULL\n");
        return;
    }
    
    // Calcul de la nouvelle position dans le fichier en fonction de whence
    off_t new_position;
    switch (whence) {
        case SEEK_SET:
            new_position = offset;
            break;
        case SEEK_CUR:
            new_position = f->current_position + offset;
            break;
        case SEEK_END:
            new_position = f->file_size + offset;
            break;
        default:
            fprintf(stderr, "La valeur de whence est invalide\n");
            return;
    }
    
    // Vérification que la nouvelle position est valide
    if (new_position < 0 || new_position > f->file_size) {
        fprintf(stderr, "La nouvelle position est invalide\n");
        return;
    }
    
    // Mise à jour de la position actuelle dans le fichier
    f->current_position = new_position;
}
