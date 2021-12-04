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

    return max;
}

record* read_text_field(int id, char* argv[], record* ptr){
    for(int i=0; i<strlen(argv[id]); i++)
        ptr->text[i] = argv[id][i];

    return ptr;
}

int last_record_id(int fd, int line_len){
    return lseek(fd, 0, SEEK_END) - line_len;
}

void write_to_db(int fd, int argc, int max, char* argv[], record* ptr){
    if(ptr == NULL){
        exit(EXIT_FAILURE);
    }

    if(lseek(fd, 0, SEEK_END) == 0)
        ptr->id = 0;
    
    else{
        lseek(fd, last_record_id(fd, sizeof(record)+max+1), SEEK_SET);
        read(fd, ptr, 2);
        lseek(fd, 0, SEEK_END);
    }

    for(int i=2; i<argc; i++, ptr->id++){
        printf("%d ustalone id\n", ptr->id);
        read_text_field(i, argv, ptr);
        write(fd, ptr, sizeof(record)+max);
        write(fd, "\n", 1);
        memset(ptr->text, 0, max);
    }
        

        lseek(fd, 0, SEEK_SET);
        record* test = malloc(sizeof(record) + max);
        read(fd, test, sizeof(record)+max);
        printf("%d id, %d to len, %s to odczytane \n", test->id, test->len, test->text);
        lseek(fd, sizeof(record)+max+1, SEEK_SET);
        read(fd, test, sizeof(record)+max);
        printf("%d id, %d to len, %s to odczytane \n", test->id, test->len, test->text); 
}

int main(int argc, char* argv[]){
    int fd;


    /*switch(argc){
        case(1):
        perror("No args passed!\n");
        exit(EXIT_FAILURE);
        break;

        case(2):
        fd = open(argv[argc-1], O_RDWR);
        //wyswietl zawartosc pliku
        break;

        default:

        fd = open(argv[argc-1], O_CREAT, O_RDWR, O_APPEND);
        break;
    }*/

    fd = open(argv[1], O_RDWR | O_CREAT, S_IRWXU);
    if(fd < 0){
        perror("Error while opening/creating file!\n");
        exit(EXIT_FAILURE);
    }

    int max = find_max(argc, argv);
    if(max == 0){
        perror("Empty line.\n");
        exit(EXIT_FAILURE);
    }

    record* x = malloc(sizeof(record) + max);
    x->len = max;

    write_to_db(fd, argc, max, argv, x);

    if( close(fd) <0 ){
        perror("Error while closing file! \n");
        exit(EXIT_FAILURE);
    }


    return 0;
}