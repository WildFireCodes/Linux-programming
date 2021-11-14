#ifndef _DBFUNS_H
#define _DBFUNS_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct record{
    int32_t key;
    char info[16];
    float val;
} record;

enum mode_vals{READ=1, WRITE=2, DELETE=3};

int check_setmode(int setmode, int default_value){
    return setmode == -1 ? default_value : -1;
}

int validate_args(int mode, int skey, int sinfo, int sval){
    int validation = 1;

    switch(mode){
        case(1):
        if(skey){
            printf("sinfo sval: %d %d\n",sinfo,sval);
            if(sinfo || sval){
                fprintf(stderr, "The read method takes only the key as an argument. Try again.\n"); 
                validation = -1;
            }
        }
        break;

        case(2):
        if(skey){
            if(!sinfo || !sval ){
                fprintf(stderr, "The write method takes only the key as an argument. It also requires the info parameter or value. Try again.\n"); 
                validation = -1;
            }
        }
        break;

        case(3):
        if(!skey){
            fprintf(stderr, "The delete method requires the key as an argument. Try again.\n"); 
            validation=-1;
        }
        break;

        default:
        fprintf(stderr, "Unmatched case\n");
        validation = -1;
    }

    printf("Validation before return %d\n",validation);
    return validation;
}

int read_args(int argc, char* argv[]){
    int opt, mode = -1, setmode = -1, setkey = -1, setinfo = -1, setvalue = -1;
    int32_t key = -1;
    float val = 0;
    char info[16]={}, *end; 

    while((opt = getopt(argc, argv, "rwdk:i::v::")) != -1){
        switch(opt){
            case 'r':
            mode = check_setmode(setmode, READ);
            printf("Read %d\n",mode);
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
            //key = (int32_t)atoi(optarg);
            key = (int32_t)strtol(optarg, &end, 10);
            setkey = 1;
            break;

            case 'i':
            strncpy(info, optarg, 16);
            setinfo = 1;
            break;

            case 'v':
            val = strtof(optarg, NULL);
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





#endif