#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd;
    int errno; 


    if ( (fd = open("test.txt", O_RDONLY, S_IRUSR)) == -1 ) {
        fprintf(stderr, "%s \n", strerror(errno)); 
    }else {
        printf("Das ist der File Descriptor: %d\n", fd); 
    }
    sleep(60);
    return 0; 
}

/*
soeren@T-480:~/Documents/sem4/bsn2/ue3$ ps -e | grep a3
  44285 pts/1    00:00:00 a3
soeren@T-480:~/Documents/sem4/bsn2/ue3$ ps -e | grep a3
  45137 pts/1    00:00:00 a3
soeren@T-480:~/Documents/sem4/bsn2/ue3$ ls -l /proc/45137/fd
total 0
lrwx------. 1 soeren skrumm 64 Mar 31 23:36 0 -> /dev/pts/1
lrwx------. 1 soeren skrumm 64 Mar 31 23:36 1 -> /dev/pts/1
lrwx------. 1 soeren skrumm 64 Mar 31 23:36 2 -> /dev/pts/1
lr-x------. 1 soeren skrumm 64 Mar 31 23:36 3 -> /home/skrumm/Documents/sem4/bsn2/ue3/test.txt

mit output in ein file: 

soeren@T-480:~/sem4/bsn2/ue3$ ps -e | grep a3
  45288 pts/3    00:00:00 a3
soeren@T-480:~/sem4/bsn2/ue3$ ls -l /proc/45288/fd
total 0
lrwx------. 1 soeren skrumm 64 Mar 31 23:39 0 -> /dev/pts/3
l-wx------. 1 soeren skrumm 64 Mar 31 23:39 1 -> /home/skrumm/Documents/sem4/bsn2/ue3/out.txt
lrwx------. 1 soeren skrumm 64 Mar 31 23:39 2 -> /dev/pts/3
lr-x------. 1 soeren skrumm 64 Mar 31 23:39 3 -> /home/skrumm/Documents/sem4/bsn2/ue3/test.txt
soeren@T-480:~/sem4/bsn2/ue3$ 

*/