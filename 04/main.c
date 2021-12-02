#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

typedef unsigned char BYTE;

typedef struct __attribute__((__packed__)) record{
    short id;
    BYTE len;
    char text[0];
} record;

char buffer[3];

int main(int argc, char* argv[]){
    int fd;
    char a[10];
    char *b = a;
    char *c;
    printf("%ld to c\n",sizeof(c));
    printf("%ld \n",sizeof(b));
    /*switch(argc){
        case(1):
        perror("No args passed!\n");
        exit(EXIT_FAILURE);
        break;

        case(2):
        fd = open(argv[argc-1], O_RDWR);
        break;

        default:

        fd = open(argv[argc-1], O_CREAT, O_RDWR, O_APPEND);
        break;
    }*/

    fd = open(argv[argc-1], O_RDWR | O_CREAT, S_IRWXU);
    if(fd < 0){
        perror("Error while opening/creating file!\n");
        exit(EXIT_FAILURE);
    }

    int i = 1, max = 0;

    while(i < argc-1){
        if(max < strlen(argv[i]))
            max = strlen(argv[i]);
        
        i++;    
    }

    
    
    size_t size_to_malloc = sizeof(record) + max;
    
    record* x = malloc(sizeof(record));
    for(int i=0;i<strlen(argv[2]);i++){
        x->text[i] = argv[2][i];
    }
    printf("%s \n", x->text);/*
    printf("%ld %ld",sizeof(x),sizeof(*x));
    x->len = max;
  
    //plik jest pusty, zapisujemy na pierwszym miejscu
    if(lseek(fd, 0, SEEK_END) == 0){
        for(int i=1; i<argc-1; i++){
        x->id = i;
        strcpy(x->text, argv[i]);
        
        write(fd, "\n", 1);
        }
    }*/
 /*   
    else{
        i = 0;
        int id = 1;
        while(i != lseek(fd, 0 ,SEEK_END)){
            id++;
            //odczytuje 3 bajty
            char* c;
            i += read(fd, &c, 3);
            lseek(fd, i, SEEK_SET);
        }

    }
    */
    if( close(fd) <0 ){
        perror("Error while closing file! \n");
        exit(EXIT_FAILURE);
    }


    return 0;
}