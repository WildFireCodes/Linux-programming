#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv){
    if(argc < 2){
        perror("No args passed! Try again. \n");
        exit(EXIT_FAILURE);
    }

    int opt;
    while((opt = getopt(argc, argv, "i:o:")) != -1){
            switch(opt){
                case 'i':
                //printf("%s to optarg\n", optarg);
                int fd = open(optarg, O_RDONLY);
                if(fd < 0){
                    perror("Error while opening input file. \n");
                    exit(EXIT_FAILURE);
                }

                dup2(fd, 0); //input stream from file
                break;

                case 'o':
                int fd2 = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
                if(fd2 < 0){
                    perror("Error while opening output file. \n");
                    exit(EXIT_FAILURE);
                }
                
                dup2(fd2, 1); //output stream to file
                break;

                default:
                perror("Illegal arg!\n");
                exit(EXIT_FAILURE);
             }
        }

    char** tab = (char**)malloc((argc-optind+2) * sizeof(char*));
    if(!tab){
        perror("Error while allocating memory. \n");
        exit(EXIT_FAILURE);
    }

    //pierwszy indeks przy wywolaniu musi zawierac nazwe programu
    //ostatni musi byc NULLem
    tab[0] = "tr";
    tab[argc-1] = NULL;

    for(int i=1; optind < argc; i++, optind++)
        tab[i] = argv[optind];

    execvp("tr", tab);

    exit(0);
}
