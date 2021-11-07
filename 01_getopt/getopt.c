#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
    for(int i=0;i<argc;i++)
        printf("Argv[%d]=%s\n",i,argv[i]);
    
    printf("\n");

    int opt, i;
    char* end;

    while((opt=getopt(argc,argv,":oxd")) != -1){
        return 1;
        switch(opt){
            case 'o':
                //octal representation
                printf("%o\n",(unsigned)strtol(argv[argc-1],&end,0));
                break;
            case 'x':
                //hexadecimal representation
                printf("%x\n",(unsigned)strtol(argv[argc-1],&end,0));
                break;
            case 'd':
                //decimal representation
                printf("%d\n",(unsigned)strtol(argv[argc-1],&end,0));
                //%lu
                break;
            case '?':
                //fprintf(stderr,"\033[0;31m Unknown option -%c \n",optopt);
                break;
        }
    }

    printf("\n");

    if(optind < argc){
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ",argv[optind++]);
        printf ("\n");
    }
    
    return 0;
}   