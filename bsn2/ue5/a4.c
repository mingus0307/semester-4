#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t pid = fork(); 
    //char text[100];  
    for (int i = 0; i < 50; i++){ 
        if (pid < 0){
            perror("fork failure!!! abort!!"); 
            exit(EXIT_FAILURE); 
            break;
        } else if(pid == 0){
            printf("Kind %d\nFORK: %d\nPID: %d\nPPID: %d\n\n",i + 1,  pid, getpid(), getppid()); 
            continue;       
        }else{
            printf("Eltern %d\nFORK: %d\nPID: %d\nPPID: %d\n\n",i + 1,  pid, getpid(), getppid()); 
            pid = fork(); 
            break; 
        } 
    }

    return 0; 
}

/* lösung für 4 c 
        pid = fork(); 
        if (pid < 0){
            perror("fork failure!!! abort!!"); 
            exit(EXIT_FAILURE); 
            break;
        } else if(pid == 0){
            printf("Kind %d\nFORK: %d\nPID: %d\nPPID: %d\n\n",i + 1,  pid, getpid(), getppid()); 
            if (i == 49){
                scanf("%s", text); 
                printf("HAT GEKLAPPT: %s\n", text); 
            } 
            continue;       
        }else{
            printf("Eltern %d\nFORK: %d\nPID: %d\nPPID: %d\n\n",i + 1,  pid, getpid(), getppid()); 
            wait(NULL);  
            break; 
        } 
*/