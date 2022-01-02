#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

typedef enum { F, T } boolean;

int main(int argc, char** argv){
    if(argc < 2){
        perror("No args passed! Try again. \n");
        exit(EXIT_FAILURE);
    }

    int opt, fd, fd2, i = 1;
    boolean param = F;

    while((opt = getopt(argc, argv, "i::o::c::d::s::t::")) != -1){
            switch(opt){
                case 'i':
                fd = open(optarg, O_RDONLY);
                dup2(fd, 0); //input stream from file
                param = T;
                break;

                case 'o':
                fd2 = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
                dup2(fd2, 1); //output stream to file
                param = T;
                break;

                default:
                perror("Illegal arg!\n");
                exit(EXIT_FAILURE);
             }
        }

    char** tab = (char**)malloc(argc*sizeof(char*));
    if(!tab){
        perror("Error while allocating memory. \n");
        exit(EXIT_FAILURE);
    }

    if(param == T)
        i = 3;

    int index = 1;
    for(i; i<argc; i++, index++)
        tab[index] = argv[i];

    execvp("tr", tab);
    free(tab);
    exit(0);
}
