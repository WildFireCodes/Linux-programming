#include <stdio.h>

//#include ".../Linux-programming/02_c_db/db_funs.h"
#include "db_funs.h"

int main(int argc, char* argv[]){
    int mode=0; 
    // 1 - read, 2 - write, 3 - delete, -1 - error

    mode=read_args(argc, argv);

    printf("%d \n",mode);

    return 0;
}