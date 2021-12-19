#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define NANO 300000000L

int main(int argc, char** argv){
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = NANO;
    
    printf("Witaj");
    nanosleep(&tim, NULL);

    printf(", jestem procesem");
    nanosleep(&tim, NULL);

    printf(" %d.\n", getpid());
    exit(0);
}