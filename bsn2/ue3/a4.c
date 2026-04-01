#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd;
    int errno; 


    if ( (fd = open("test2.txt", O_RDWR, S_IRUSR)) == -1 ) {
        fprintf(stderr, "%s \n", strerror(errno)); 
    }else {
        printf("Das ist der File Descriptor: %d\n", fd); 
        write(fd, "Hallo", 6);
    }

    return 0; 
}

/*
    wenn wir die flag in read only ändern wird zwar weiterhin kompiliert aber es wird nichts ins file geschrieben
*/