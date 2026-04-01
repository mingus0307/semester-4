#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd;
    int errno; 
    char* output = malloc(6); 


    if ( (fd = open("test4.txt", O_RDONLY, S_IRUSR)) == -1 ) {
        fprintf(stderr, "%s \n", strerror(errno)); 
    }else {
        read(fd, output, 5);
        printf("Hier müsste Hallo stehen: %s\n", output); 
    }
    close(fd); 

    return 0; 
}