#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd;
    int errno; 


    if ( (fd = open("test3.txt", O_SYNC, S_IRUSR)) == -1 ) {
        fprintf(stderr, "%s \n", strerror(errno)); 
    }else {
        for (int i = 0; i < 30000; i++){
            write(fd, "Hallo", 6);
        }
    }
    close(fd); 

    return 0; 
}

/*
    mit rdwr 
    soeren@T-480:~/sem4/bsn2/ue3$ time ./a5
    real    0m0.356s
    user    0m0.030s
    sys     0m0.320s
    soeren@T-480:~/sem4/bsn2/ue3$ 

    mit sync
    soeren@T-480:~/sem4/bsn2/ue3$ make a5 && time ./a5
    gcc -Wall -pedantic-errors -g -c a5.c -o a5.o
    gcc -Wall -pedantic-errors -g a5.o -o a5

    real    0m0.067s
    user    0m0.043s
    sys     0m0.023s
    soeren@T-480:~/sem4/bsn2/ue3$ 

    sync ermöglicht ein synchrones schreiben in das file deshalb ist es so viel schneller, es läuft parallel anstatt nach einander


*/