#include <stdio.h>
#include <time.h>
#define NANO 1000000000L

int main(int argc, char* argv[]){
    //ctime wzraca wskaznik do buforu z tekstem
    //static
    time_t sys_time;
    time(&sys_time);
    printf("1.Time is: %s \n", ctime(&sys_time));
    //1,75 sekundy

    struct timespec tim, tim2;
    tim.tv_sec  = 1;
    tim.tv_nsec = 500;

    //oba argumenty nanosleep to wskaznik na strukture opisujaca
    //odstep w czasie - czesc sekundy i nanosekundy
    
    if(nanosleep(&tim, NULL) < 0){
        return -1;
    }

    time_t sys_time2;
    time(&sys_time2);
    printf("2.Time 2 is: %s\n", ctime(&sys_time2));
    printf("1. Time (again) is: %s\n", ctime(&sys_time));

    return 0;
    //open z odpowiednia flaga!
}