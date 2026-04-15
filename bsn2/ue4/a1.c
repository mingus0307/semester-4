#include <errno.h>
#include <stdio.h>
#include <string.h>


int main(void){
    for (int i = 0; i < 134; i++){
        printf("Error Code: %d\n", i);
        printf("message: %s\n",strerror(i));  
    }
    return 0; 
}