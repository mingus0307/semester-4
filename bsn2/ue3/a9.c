#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd;
    int errno;  


    if ( (fd = open("test5.txt", O_RDWR | O_APPEND, S_IRUSR)) == -1 ) {
        fprintf(stderr, "%s \n", strerror(errno)); 
    }else {
        lseek(fd, -1, SEEK_END);
        write(fd, "Hallo", 5);
    }
    close(fd); 

    return 0; 
}

/*
    Wenn die Zieldatei noch nicht existiert macht das den Unterschied, dass wir einen error catchen,
    wenn die Datei bereits mit etwa gefüllt ist wird einfach davor gejumpt
*/