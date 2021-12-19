//int l
//(void*)(long) l - wydluzy do dlugiej i uzupelni zerami
//int k = (long ) w <- void*

//p1 = ((long) l) << (8*sizeof(int))

//dup, dup2
//3 otwarte pliki - umowne fd w tablicy kazdego procesu
//1 - stdin, 2-stdout ZAZWYCZAJ, bo mozna przekierowac wyjscie
//w bashu
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//program ktory wykonuje poprzedni program -> exec z ustalonymi
//parametrami, np napisy jeden dwa trzy
//program2 dostaje dowolna ilosc parametrow ->exec podmienia siebie
//na arguemnty o odwrotnej kolejnosci z tym drugim programem
int main(int argc, char** argv){
    char *T[] = {"plik_WE.txt", "plik_WY.txt", "plik_LOG.txt"};
    //i =           0           1                 2
    int fd;

    for(int i=0; i<strlen(*T); i++){
        fd = open(T[i], (i == 0) ? O_RDONLY : O_WRONLY);
        dup2(fd, i);
    }

    char *line = NULL;
	long size = 0;
	
	printf("testest \n");
	getline(&line, &size, stdin);
	fprintf(stderr, "%s \n", line);

	return 0;
}