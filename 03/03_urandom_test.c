#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define LENGTH 64

int main(){
    int fd;
    if((fd = open("/dev/urandom", O_RDONLY)) <0 ){
        perror("Error while opening file!\n");
        exit(EXIT_FAILURE);
    }
    
    char T[LENGTH];
    read(fd, &T, LENGTH);

    for(int i=0; i<LENGTH; i++){
        printf(" %02hhx", T[i]);

        if((i+1)%8 == 0)
            printf("\n");
    }

    printf("\n");
    unsigned short *s = T;

    for(int i=0; i<LENGTH; i+=2){

        printf(" %hu", *(s+i));

        if( (i+2)%8 == 0)
            printf("\n");
    }

    if( close(fd) <0 ){
        perror("Error while closing file! \n");
        exit(EXIT_FAILURE);
    }

    printf("\n");

    struct test{
        short key;
        char t[16];
        double v;
    }test;

    struct __attribute__((__packed__)) test2{
        short key;
        char t[16];
        double v;
    }test2;

    char a; 
    short b;
    long c;
    long long d;

    printf("Sizes compare:\n char a - %ld\n short b - %ld\n long c - %ld\n long long d - %ld\n struct test - %ld\n struct (packed) test2 - %ld\n",
               sizeof(a), sizeof(b), sizeof(c), sizeof(d), sizeof(test), sizeof(test2));

    exit(EXIT_SUCCESS);
}