#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd;
    int errno;  


    if ( (fd = open("test4.txt", O_RDONLY, S_IRUSR)) == -1 ) {
        fprintf(stderr, "%s \n", strerror(errno)); 
    }else {
        printf("Das ist der Output am Ende: %ld\n",lseek(fd, -2, SEEK_END)); 
    }
    close(fd); 

    return 0; 
}
/*
    die bedeutung des offsets von lseek ergibt sich aus dem whence dahinter. bei seek_end wird das offset genutzt um den abstand zum ende des files zu messen 
    und die Distanz der bytes bis zum Ende des Files als long zurückgegeben. 
    eine positive Zahl heißt wir gehen über die bisherige Distanz hinaus und füllen mit Nullen auf 
    negativ heißt wir sind im File 
*/