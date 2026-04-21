#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();
    
    switch (pid) {
        case -1 :
            perror("fork(2) failure!!! abort!!!!"); 
            exit(EXIT_FAILURE); 
            break; 
        case 0 : 
            printf("Kind!\nFORK: %d\nPID: %d\nPPID: %d\n\n", pid, getpid(), getppid()); 
            break; 
        default:
            printf("Eltern!\nFORK: %d\nPID: %d\nPPID: %d\n\n", pid, getpid(), getppid()); 
            break;  
    }

    return 0; 
}