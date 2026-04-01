#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd;
    int errno; 


    if ( (fd = open("test4.txt", O_RDWR | O_CREAT | O_EXCL, S_IRUSR)) == -1 ) {
        fprintf(stderr, "%s \n", strerror(errno)); 
    }else {
        write(fd, "Hallo", 5);
    }
    close(fd); 

    return 0; 
}
/*
    Ja, ich kann es lesen, beim zweiten bekomme ich nur den error raus, dass das file bereits existiert. 
*/

