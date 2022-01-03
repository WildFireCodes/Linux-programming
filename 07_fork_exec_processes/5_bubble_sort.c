#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef enum { F, T } boolean;

int main(int argc, char** argv){
    if(argc < 2){
        perror("Too small number of args passed. Try again.");
        exit(EXIT_FAILURE);
    }

    //rosnaca kolejnosc
    // 3 1 5 4
    // 1 3 5 4
    // 1 3 4 5 za pomoca exec

    //argumenty przychodza jako chary* -> konwersja na float -> wyjscie jest charem*

    //wypisanie argumentow wejsciowych
    printf("INPUT: \n");
    for(int i=1; i<argc; i++)
        printf("%s ", argv[i]);
    printf("\n");

    //tablica na konwersje na float
    float* tab = (float*)malloc((argc-1) * sizeof(float));
    if(!tab){
        perror("Error while allocating memory for float tab.\n");
        exit(EXIT_FAILURE);
    } 

    //tablica wyjsciowa
    char** output = (char**)malloc((argc-1) * sizeof(char*));
    if(!output){
        perror("Error while allocating memory for output tab.\n");
        exit(EXIT_FAILURE);
    }

    //konwersja
    for(int i=1; i<argc; i++)
        tab[i-1] = atof(argv[i]);

    boolean again = F;

    for(int i=1; i<argc-1; i++){
        if(tab[i-1] > tab[i]){
            float help = tab[i];
            tab[i] = tab[i-1];
            tab[i-1] = help;
            again = T;
            break;
        }
    }

    printf("OUTPUT: \n");
    char buffer[10];
    for(int i=0; i<argc-1; i++){
        sprintf(buffer, "%f", tab[i]);
        //gcvt(tab[i], 10, buffer);
        //output[i] = buffer;
        strcpy(output[i], buffer); //tutaj chyba trzeba przesunac wskaznik ile sie zapisalo
        printf("%s ", output[i]);
    }

    printf("\n");
    if(again == F)
        exit(0);
    printf("\n\n");
    for(int i=0; i<argc-1; i++){
        printf("%s ", output[i]); //jedynie ostatnia liczba jest przekazywana do ponownego wykonania
    }
    printf("Wykonuje program ponownie. \n");
    execv("5_bubble_sort", output);
}
