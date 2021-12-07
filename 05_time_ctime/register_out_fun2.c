#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

bool file_exists (char *filename) {
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}

int fd, argi;
char** args;

void write_time(){
    time_t sys_time;
    time(&sys_time);

    lseek(fd, 0, SEEK_SET);
    lseek(fd, atoi(args[2]), SEEK_CUR);
    
    if(write(fd, ctime(&sys_time), strlen(ctime(&sys_time))) < 0){
        perror("Error while writting to file.\n");
        exit(EXIT_FAILURE);
    }
}

void fill_file(){
    while(lseek(fd, 0, SEEK_CUR)+strlen(args[3]) < atoi(args[2])){
        if(write(fd, args[3], strlen(args[3])) < 0){
            perror("Error while writting to file.\n");
            exit(EXIT_FAILURE);
        }
    }
    
    if(lseek(fd, 0, SEEK_CUR) < atoi(args[2])){
        int missing = atoi(args[2]) - lseek(fd, 0, SEEK_CUR);
        if(write(fd, args[3], missing) < 0){
            perror("Error while writting to file.\n");
            exit(EXIT_FAILURE);
        }
    }

    /*for(int i=0; i<atoi(args[2]); i++){
        write(fd, args[3][i], 1);
    }*/
}

void close_file(){
    if( close(fd) <0 ){
        perror("Error while closing file.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv){
    if(argc < 4){
        perror("Too few args.\n");
        exit(EXIT_FAILURE);
    }

    argi = argc;
    args = argv;

    if(file_exists(argv[1])){
        perror("File already exists.\n");
        //exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_CREAT | O_RDWR);

    int val1, val2, val3;

    val1 = atexit(close_file);
    val2 = atexit(write_time);
    val3 = atexit(fill_file);

    if((val1 || val2 || val3) != 0)
            perror("atexit() function registration failed\n");

    exit(EXIT_SUCCESS);
}