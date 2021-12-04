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

void write_to_db(int fd, int argc, int max, char* argv[], record* ptr){
    if(ptr == NULL){
        exit(EXIT_FAILURE);
    }

    //to i = 2
    if(lseek(fd, 0, SEEK_END) == 0){ 
        for(int i=2; i<argc; i++){
            ptr->id = i-2;
            ptr = read_text_field(i, argv, ptr);
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
        lseek(fd, sizeof(record)+max+1, SEEK_SET);
        read(fd, test, 2);
        printf("%d idto odczytane \n", test->id);
        
    }
    //to i to ostatnie id
    else
        lseek(fd, 28, SEEK_SET);
        //lseek(fd, 28, SEEK_SET);
        record* test = malloc(sizeof(record) + max);
        read(fd, test, 2);
        printf("pozycja to %ld\n",lseek(fd,0,SEEK_CUR));
        //find_last_index
        printf("%d idto odczytane \n", test->id);
            
    
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

    
    //odtad dzialalo!
    /*

    record* x = malloc(sizeof(record) + max);
    x->len = max;

    //plik pusty - zaczynamy wpisywanie od poczatku
    //znak po znaku do text[], aby napis byl w strukturze
  
    /*for(int j=2; j<argc; j++){
        for(int k=0; k<strlen(argv[j]); k++){
        x->text[k] = argv[j][k];
        }
        
        printf("%s to text w txt\n", x->text);
        memset(x->text, 0, sizeof(max));
    }*/
    //argc = 4 ->   v[0] program v[1]=a v[2]=aa v[3]=aaa
/*
    if(lseek(fd, 0, SEEK_END) == 0){
        for(int i=2; i<argc; i++){
        x->id = i-2;
        //strcpy(x->text, argv[i]); zamiast strcpy funkcja ktora wczyta 
        
        for(int k=0; k<strlen(argv[i]); k++)
            x->text[k] = argv[i][k];
        
        write(fd, x, sizeof(record)+max);
        write(fd, "\n", 1);
        printf("%s txt przed \n", x->text);
        memset(x->text, 0, max);
        printf("%s txt \n\n", x->text);

        record* test = malloc(sizeof(record) + max);
        lseek(fd, 0, SEEK_SET);
        read(fd, test, sizeof(record)+max);

        printf("%d id %d to len %s a to odczytane \n", test->id, test->len, test->text);
        }
    }
    lseek(fd, 0, SEEK_SET); */
    //record test2;
    //read(fd, &test2, sizeof(record)+max);
    //printf("%d id2 %d to len2 %s a to odczytane2 \n", test2.id, test2.len, test2.text);

    /*for(int i=0;i<strlen(argv[2]);i++){
        x->text[i] = argv[2][i];
    }*/
    /*
    
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