#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    int fd = open("abc.txt", O_RDWR, O_APPEND); 

    pid_t pid = fork();
    
    if (pid < 0){

        perror("FAILURE TO FORK!");
        exit(EXIT_FAILURE);  
    } else if (pid == 0){
        for (int i = 0; i < 100000; i++){
            //printf("wir sind im Kindprozess\n"); 
            write(fd,"Ich bin ein Kind!\n", 19); 
        }
    } else {
        for (int i = 0; i < 100000; i++){
            //printf("wir sind bei den Eltern\n"); 
            write(fd, "ich bin Elternteil!\n", 21); 
        }
    }
    close(fd); 
    return 0; 
}

/*
    Der random gestreute Output liegt daran, dass wir hier in zwei Threads arbeiten, welche nicht synchronisiert sind 
    Deshalb verwenden wir lieber den sys call open() un dwirte() da wir so direkt am kernel arbeiten und befehle geben. bei fopen/write()
    schreiben wir ja in den stdio buffer und der kind prozess eben auch was das ganze durcheinander bringt. Ein faires Scheduling erhalten 
    wir so oder so nicht. 
*/