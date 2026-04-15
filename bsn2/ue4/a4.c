#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

void list_dir(char* name){
    DIR* d;

    if (( d = opendir(name)) == NULL){
        fprintf(stderr, "stat failed: %s\n", strerror(errno));  
        return;
        // wir müssen return machen, weil wir sonst einfach random speicher einlesen und das erzeugt undefined behaviour
    }

    struct dirent* file = readdir(d);
    
    while(file != NULL){
        // d_type ist zwar ein char aber so nicht darstellbar, deshalb als Zahl. man könnte dann mit stat natürlich anfangen das File dann so auszulesen 
        printf("name: %s\ntype: %d\n", file->d_name, file->d_type); 
        file = readdir(d); 
    }

}

int main(void){
    list_dir("test_dir"); 
}