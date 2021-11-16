#ifndef _DBFUNS_H
#define _DBFUNS_H
#define RECORD_LENGTH 42
#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

typedef struct record{
    int32_t key;
    char info[16];
    float val;
} record;

enum mode_vals{DEFAULT, READ, WRITE, DELETE};

int check_setmode(int setmode, int default_value){
    return setmode == 0 ? default_value : -1;
}

int validate_args(int mode, int skey, int sinfo, int sval){
    int validation = 1;

    switch(mode){
        case(DEFAULT):
        fprintf(stderr, "No args passed. Try again.\n");
        break; 

        case(READ):
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

        case(WRITE):
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

        case(DELETE):
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
    int opt, mode = 0, setmode = 0, setkey = 0, setinfo = 0, setvalue = 0;
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
            if(!optarg){
                fprintf(stderr,"optarg is null \n");
                return -1;
            }
            strncpy(instance->info, optarg, 16);
            setinfo = 1;
            break;

            case 'v':
            
            if(!optarg){
                fprintf(stderr,"optarg is null \n");
                return -1;
            }

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

int find_record(int fd, int32_t key){
    char current_line[RECORD_LENGTH], *token, *next_token, *end;

    while((read(fd, current_line, RECORD_LENGTH))){
        token = strtok_r(current_line, " ", &next_token);
        
        if(key == (int32_t)strtol(token, &end, 10))
            return lseek(fd, 0, SEEK_CUR)-RECORD_LENGTH;
    }
    
return -1;
}
 
int read_record(int fd, int32_t key){
   int check = find_record(fd, key);
   
   if(check >= 0){
       char current_line[RECORD_LENGTH];
       lseek(fd, check, SEEK_SET);
       read(fd, current_line, RECORD_LENGTH);
       printf("%s \n", current_line);
       return 1;
   }

    fprintf(stderr, "Record not found. \n");
    return -1;
}

int write_record(int fd, int32_t key, char *info, float value){
    if(key == -1)
        return -1;
    
    if(!info)
        info = '\0';

    if(!value)
        value = NAN;
    
    int check_empty = find_record(fd, key);

    if(check_empty >= 0)
        lseek(fd, check_empty, SEEK_SET);
    else
        lseek(fd, 0, SEEK_END);

    record new;
    new.key=key; 
    strcpy(new.info, info); 
    new.val=value;

    char new_line[RECORD_LENGTH], *line_format = "%-7d  %-16s  %-10.6lf\n";
    
    snprintf(new_line, RECORD_LENGTH, line_format, new.key, new.info, new.val);
    printf("%s",new_line);
    printf("%s",new_line);
    write(fd, new_line, strlen(new_line));

    return 1;
}

int delete_record(int fd, int32_t key){
    char current_line[RECORD_LENGTH], *token, *next_token, *end;

    if(key == -1)
        return -1;

    int find = find_record(fd, key);
    if(find >= 0){
        lseek(fd, find, SEEK_SET);
        char* line_format = "%-7d";
        char new_line[8];
        snprintf(new_line, sizeof(new_line), line_format, -1);
        write(fd, new_line, sizeof(new_line));
        return 1;
    }


    fprintf(stderr, "Couldn't find record to delete. \n");
    return -1;
    
}


#endif