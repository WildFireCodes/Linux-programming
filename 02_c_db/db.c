#include <stdio.h>
#include <unistd.h>
//#include ".../Linux-programming/02_c_db/db_funs.h"
#include "db_funs.h"

int main(int argc, char* argv[]){

    //getopt
    int opt;
    while((opt=getopt(argc,argv,"rw:d::")) != -1){
        switch(opt){
            case 'r':
            break;
            case 'w':
            break;
            case 'd':
            break;
        }
    }

    return 0;
}