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

    int f = fork();
    
    if(f < 0)
        exit(EXIT_FAILURE);
    
    else if (f == 0){
    printf(", jestem potomkiem");
    nanosleep(&tim, NULL);
    printf(" %d", getppid());
    nanosleep(&tim, NULL);
    }

    else {
    printf(", jestem rodzicem");
    nanosleep(&tim, NULL);
    printf(" %d ", getpid());
    nanosleep(&tim, NULL);
    printf(" procesu pid=%d \n", f);
    }

    exit(0);
}