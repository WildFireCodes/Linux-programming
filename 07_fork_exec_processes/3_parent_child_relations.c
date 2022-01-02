#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define NANO 1000000000L

struct timespec converter(float time){
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = time*NANO;

    return tim;
}

int main(int argc, char** argv){
    struct timespec tim;// = converter(3.5);
    tim.tv_sec=3;
    tim.tv_nsec=0;
    //nanosleep(&tim, NULL);
    int f = fork();
    
    if(f < 0)
        exit(EXIT_FAILURE);
    
    else if (f == 0) {
        //tim = converter(atof(argv[1]));
        printf("Potomek tim: %ld\n", tim.tv_nsec);
        printf("POTOMEK: \n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        nanosleep(&tim, NULL);
    }

    else {
        //tim = converter(atof(argv[2]));
        printf("Rodzic tim: %ld\n", tim.tv_nsec);
        printf("RODZIC: \n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        //nanosleep(&tim, NULL);
    }

//printf("PPID: %d\n", getppid());
return 0;
}