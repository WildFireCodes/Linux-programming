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
    char text[];
} record;

int find_max(int argc, char* argv[]){
    int i = 1, max = 0;

    while(i < argc-1){
        if(max < strlen(argv[i]))
            max = strlen(argv[i]);
        
        i++;    
    }
    //printf("MAX: %d\n", max);
    return max;
}

record* read_text_field(int id, char* argv[], int max, record* ptr){
    for(int i=0; i<strlen(argv[id]); i++)
        ptr->text[i] = argv[id][i];

    if(strlen(argv[id]) < max){
        for(int j=strlen(argv[id]); j<max; j++)
            ptr->text[j] = ' ';
    }

    return ptr;
}

int find_last_id(int fd, record* ptr){
    int last_id, end = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    
    while(lseek(fd, 0, SEEK_CUR) < end - 1){
        read(fd, ptr, 2);
        last_id = ptr->id;
        //printf("odczytane id to: %d poz %ld \n", last_id, lseek(fd, 0, SEEK_CUR));
        read(fd, ptr, 1);
        lseek(fd, ptr->len+1, SEEK_CUR);
    }
    //printf("Ostatnie ID to %d\n", last_id);
    return last_id;
}

void write_to_db(int fd, int argc, int max, char* argv[], record* ptr){
    for(int i=2; i<argc; i++){
        if(lseek(fd, 0, SEEK_END) == 0)
            ptr->id = 0;
        else
            ptr->id = find_last_id(fd, ptr) + 1;

        read_text_field(i, argv, max, ptr);
        write(fd, ptr, sizeof(record)+max);
        write(fd, "\n", 1);
        memset(ptr->text, 0, max);
    }
}

void read_db(int fd, record* ptr){
    int end;
    if((end=lseek(fd, 0, SEEK_END)) == 0){
        perror("Empty file.\n");
        exit(EXIT_FAILURE);
    }

    lseek(fd, 0, SEEK_SET);
    while(lseek(fd, 0, SEEK_CUR) < end){
        read(fd, ptr, 3);
        lseek(fd, -3, SEEK_CUR);
        read(fd, ptr, ptr->len+3);
        printf("%d %d %s\n", ptr->id, ptr->len, ptr->text);
        lseek(fd, 1, SEEK_CUR);
    }
}

int main(int argc, char* argv[]){
    int fd;

    int max = find_max(argc, argv);

    record* x = malloc(sizeof(record) + max);
    if(x == NULL){
        exit(EXIT_FAILURE);
    }

    x->len = max;

    switch(argc){
        case(1):
        perror("No args passed!\n");
        exit(EXIT_FAILURE);
        break;

        case(2):
        fd = open(argv[1], O_RDWR);
        if(fd < 0)
            exit(EXIT_FAILURE);

        read_db(fd, x);
        break;

        default:
        fd = open(argv[1], O_CREAT | O_RDWR | O_APPEND);
        if(fd < 0)
            exit(EXIT_FAILURE);

        write_to_db(fd, argc, max, argv, x);
        break;
    }

    if( close(fd) <0 ){
        perror("Error while closing file! \n");
        exit(EXIT_FAILURE);
    }

    free(x);

    return 0;
}