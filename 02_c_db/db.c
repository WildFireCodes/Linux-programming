#include <stdio.h>
#include <fcntl.h>

//#include ".../Linux-programming/02_c_db/db_funs.h"
#include "db_funs.h"

int main(int argc, char* argv[]){
    int mode=0; 
    // 1 - read, 2 - write, 3 - delete, -1 - error
    record db={0};
    mode=read_args(argc, argv, &db);
    int fd = open("db.txt", O_RDONLY);
    int c = read_record(fd, 1000);
    printf("%d to read record \n", c);
    //printf("%d \n",mode);

    return 0;
}