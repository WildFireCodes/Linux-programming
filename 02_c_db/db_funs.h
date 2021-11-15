#ifndef _DBFUNS_H
#define _DBFUNS_H
#define RECORD_LENGTH 30
#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

typedef struct record{
    int32_t key;
    char info[16];
    float val;
} record;

enum mode_vals{READ=1, WRITE=2, DELETE=3};

int check_setmode(int setmode, int default_value){
    return setmode == 0 ? default_value : -1;
}

int validate_args(int mode, int skey, int sinfo, int sval){
    int validation = 1;

    switch(mode){
        case 0:
        fprintf(stderr, "No args passed. Try again.\n");
        break; 

        case(1):
        if(skey){
            if(sinfo || sval){
                fprintf(stderr, "The read method takes only the key as an argument. Try again.\n"); 
                validation = -1;
            }
        }

        else{
            fprintf(stderr, "No key arg passed! Try again.\n");
            validation = -1;
        }

        break;

        case(2):
        if(skey){
            if(!sinfo && !sval){
                fprintf(stderr, "Info/Value arg required. Try again.\n"); 
                validation = -1;
            }
        }

        else{
            fprintf(stderr, "No key arg passed! Try again.\n");
            validation = -1;
        }

        break;

        case(3):
        if(!skey){
            fprintf(stderr, "The delete method requires the key as an argument. Try again.\n"); 
            validation = -1;
        }
        break;

        default:
            fprintf(stderr, "Unmatched case! Wrong args passed. Try again.\n");
            validation = -1;
    }

    return validation;
}

int read_args(int argc, char* argv[], record *instance){
    int opt, mode = 0, setmode = 0, setkey = 0, setinfo = 0, setvalue = 0; //default value = 0
    char *end; 
    
    while((opt = getopt(argc, argv, "rwdk:i::v::")) != -1){
        switch(opt){
            case 'r':
            mode = check_setmode(setmode, READ);
            setmode = mode;
            break;

            case 'w':
            mode = check_setmode(setmode, WRITE);
            setmode = mode;
            break;

            case 'd':
            mode = check_setmode(setmode, DELETE);
            setmode = mode;
            break;

            case 'k':
            instance->key = (int32_t)strtol(optarg, &end, 10);
            setkey = 1;
            break;

            case 'i':
            strncpy(instance->info, optarg, 16);
            setinfo = 1;
            break;

            case 'v':
            instance->val = strtof(optarg, NULL);
            setvalue = 1;
            break;

            default:
            fprintf(stderr, "ILLEGAL ARG!\n");
            return -1;
        }
    }

    if(!validate_args(mode, setkey, setinfo, setvalue))
        mode = -1;

    return mode;
}
 
int read_record(int fd, int32_t key){
    char current_line[RECORD_LENGTH], *token, *next_token, *end;

    while((read(fd, current_line, sizeof(current_line)))){
        token = strtok_r(current_line, " ", &next_token);
    
        if(key == (int32_t)strtol(token, &end, 10)){
            printf("%s %s \n", current_line, next_token);
            return 1;
        }
    }
    fprintf(stderr, "Record not found. \n");
    return -1;
}

void write_record(){

}

void delete_record(){

}


#endif