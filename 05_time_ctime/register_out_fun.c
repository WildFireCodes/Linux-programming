#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int fd;

void function_output(){
    time_t sys_time;
    time(&sys_time);
    printf("HEREE");
    if(write(fd, ctime(&sys_time), strlen(ctime(&sys_time))) < 0){
        perror("Error while writting to file.\n");
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

    //function_output();
    for(int i=0; i < loop_count; i++){
       
        val = atexit(function_output);;
        if(val != 0){
            perror("atexit() function registration Failed\n");
            exit(EXIT_FAILURE);
        }

    }




    if( close(fd) <0 ){
        perror("Error while closing file! \n");
        exit(EXIT_FAILURE);
    }

    exit(0);
}