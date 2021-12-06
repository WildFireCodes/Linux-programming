#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define NANO 500000000L

int fd;

void function_output(){
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = NANO;

    time_t sys_time;
    time(&sys_time);

    nanosleep(&tim, NULL);
    if(write(fd, ctime(&sys_time), strlen(ctime(&sys_time))) < 0){
        perror("Error while writting to file.\n");
        exit(EXIT_FAILURE);
    }
}

void close_file(){
    if( close(fd) <0 ){
        perror("Error while closing file.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]){
    
    fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC);

    if(fd < 0){
        perror("Error while opening file.\n");
        exit(EXIT_FAILURE);
    }

    int loop_count, val;
    if(argc < 3)
        loop_count = 1;
    else
        loop_count = atoi(argv[2]);

    atexit(close_file);
    for(int i=0; i < loop_count; i++){
       
        //nanosleep(&tim, NULL);
        val = atexit(function_output);
        if(val != 0)
            perror("atexit() function registration failed\n");       
    }

    exit(0);
}