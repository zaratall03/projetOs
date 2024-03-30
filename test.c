#include <stdio.h>
#include <stdlib.h>
#include "file_operation.h"
#include<string.h>
int main() {
     
    file* currentFile = NULL; // Pointeur vers le fichier courant

    printf("Bienvenue dans le programme de test de gestion de fichiers.\n");

    int choice;
    do {
        printf("\nMenu :\n");
        printf("1. Créer/ouvrir un fichier\n");
        printf("2. Écrire dans un fichier\n");
        printf("3. Lire depuis un fichier\n");
        printf("4. Déplacer le pointeur de lecture/écriture\n");
        printf("5. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (currentFile != NULL) {
                    printf("Fermez d'abord le fichier ouvert actuellement.\n");
                } else {
                    char filename[100];
                    printf("Entrez le nom du fichier à créer/ouvrir : ");
                    scanf("%s", filename);
                    currentFile = myOpen(filename);
                    if (currentFile != NULL) {
                        printf("Fichier ouvert avec succès.\n");
                    } else {
                        printf("Échec de l'ouverture du fichier.\n");
                    }
                }
                break;
            case 2:
                if (currentFile == NULL) {
                    printf("Aucun fichier ouvert. Veuillez d'abord ouvrir un fichier.\n");
                } else {
                    char buffer[100];
                    printf("Entrez les données à écrire dans le fichier : ");
                    scanf("%s", buffer);
                    int bytesWritten = myWrite(currentFile, buffer, strlen(buffer));
                    if (bytesWritten != -1) {
                        printf("%d octets écrits dans le fichier.\n", bytesWritten);
                    } else {
                        printf("Erreur lors de l'écriture dans le fichier.\n");
                    }
                }
                break;
            case 3:
                
                if (currentFile == NULL) {
                    printf("Aucun fichier ouvert. Veuillez d'abord ouvrir un fichier.\n");
                } else {
                    char buffer[100];
                    printf("Entrez le nombre d'octets à lire depuis le fichier : ");
                    int nBytes;
                    scanf("%d", &nBytes);
                    int bytesRead = myRead(currentFile, buffer, nBytes);
                    if (bytesRead != -1) {
                        buffer[bytesRead] = '\0'; // Ajouter un caractère de fin de chaîne
                        printf("%d octets lus depuis le fichier : %s\n", bytesRead, buffer);
                    } else {
                        printf("Erreur lors de la lecture depuis le fichier.\n");
                    }
                }
                break;

            case 4:
                if (currentFile == NULL) {
                    printf("Aucun fichier ouvert. Veuillez d'abord ouvrir un fichier.\n");
                } else {
                    int offset;
                    int whence;
                    printf("Entrez le décalage : ");
                    scanf("%d", &offset);
                    printf("Entrez le point de référence (0 pour le début, 1 pour la position actuelle, 2 pour la fin) : ");
                    scanf("%d", &whence);
                    mySeek(currentFile, offset, whence);
                    printf("Pointeur de lecture/écriture déplacé avec succès.\n");
                }
                break;

            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez sélectionner une option valide.\n");
        }
    } while (choice != 5);

    return 0;
}
