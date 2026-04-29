#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid; 
    int my_pipe[2]; 
    char* zeile = malloc(sizeof(char) * 30); 

    if (pipe(my_pipe) < 0){
        perror("PIPE FAILED"); 
    }

    if ((pid = fork()) == -1 ){
        perror("fork(2) failure!!! abort!!!!"); 
        exit(EXIT_FAILURE); 
    } else if (pid > 0){
        // child 
        close(my_pipe[0]); 
        printf("Hier bitte Übergabe-Satz reinschreiben:\n"); 
        fgets(zeile, 30, stdin); 
        write(my_pipe[1], zeile, strlen(zeile)); 

        if (waitpid(pid, NULL, 0) < 0){
            perror("WAIT FAILED"); 
        }

    } else if (pid == 0){
        close(my_pipe[1]);
        int n = read(my_pipe[0], zeile, 30); 

        for (int i = 0; i< n; i++){
            zeile[i] = toupper(zeile[i]); 
        }

        printf("Das hier ist die Kind-Zeile in UpperCase: \n%s\n", zeile); 
    }
    return 0; 
}