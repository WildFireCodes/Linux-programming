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

    printf("INPUT: \n");

    for(int i=1; i<argc; i++)
        printf("%s ", argv[i]);
        
    printf("\n");

    boolean sort_again = F;

    for(int i=1; i<argc-1; i++){
        if(*argv[i] > *argv[i+1]){
            char* help = argv[i];
            argv[i] = argv[i+1];
            argv[i+1] = help;

            sort_again = T;
            break;
        }
    }

    printf("OUTPUT: \n"); 

    for(int i=1; i<argc; i++)
        printf("%s ", argv[i]);
    printf("\n");

    if(sort_again == T){
        printf("Wykonuje program ponownie. \n\n");
        execv("5_bubble_sort", argv);
    } 
    
    printf("Tablica posortowana!\n\n");
    exit(0);
}
