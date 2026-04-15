#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void file_type(char* name){
    struct stat stat_buff;

    if (stat(name, &stat_buff) == -1){
        fprintf(stderr, "stat failed: %s\n", strerror(errno));  
        return;
        // wir müssen return machen, weil wir sonst einfach random speicher einlesen und das erzeugt undefined behaviour
    }

    if (S_ISREG(stat_buff.st_mode)){
        printf("%s is a normal file\n", name); 
    }else if(S_ISDIR(stat_buff.st_mode)){
        printf("%s is a directory\n", name); 
        
    }
}

int main(void){
    file_type("input.txt");
    file_type("should_fail.txt");
    file_type("test_dir");
    file_type("fail_dir");
}