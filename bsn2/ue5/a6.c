#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    pid_t pid; 

    for (int i = 1; i < argc; i++){
        pid = fork(); 
         if (pid < 0){
            perror("Fail at Forking!!!!!\n"); 
            exit(EXIT_FAILURE); 
         }else if (pid == 0){
            execlp(argv[i], argv[i], NULL); 
         }else{
            wait(NULL); 
         }
    }
    return 0;
}