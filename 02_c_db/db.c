#include <stdio.h>
#include <fcntl.h>
#include "db_funs.h"

int main(int argc, char* argv[]){
    // 1 - read, 2 - write, 3 - delete, -1 - error
    record db;
  
    int mode = read_args(argc, argv, &db), fd, res=0;

    switch(mode){
        case(READ):
        fd = open("db.txt", O_RDONLY);
        res = read_record(fd, db.key);
        if(!res)
            return -1;

        break;

        case(WRITE):
        fd = open("db.txt", O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
        res = write_record(fd, db.key, db.info, db.val);
        if(!res)
            return -1;

        break;

        case(DELETE):
        fd = open("db.txt", O_RDWR);
        res = delete_record(fd, db.val);
        if(!res)
            return -1;

        break;

        default:
        break;
    }

    res = close(fd);
    if(res < 0){
        fprintf(stderr, "Error while closing file! \n");
        return -1;
    }

    return 0;
}