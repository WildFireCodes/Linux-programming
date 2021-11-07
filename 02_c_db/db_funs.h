#ifndef _DBFUNS_H
#define _DBFUNS_H

#include <stdlib.h>

typedef struct db{
    int32_t key;
    char str[16];
    double val;
} db;

int OpenRecord(int32_t key){
}

//writerecord


#endif