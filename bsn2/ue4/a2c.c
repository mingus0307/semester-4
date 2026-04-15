#include <stdlib.h>
#include <stdio.h>


int main(void){
    char* s = malloc(sizeof(char) * 11); 
    FILE* fp = fopen("input.txt", "r"); 
    // wir lesen immer nur die Menge von count (n) aus den input stream auf einmal und schreiben sie direkt in out 
    // wenn der input danach nicht leer ist, dann holen wir uns den Rest und schreiben ihn dahinter
    // wenn der Input erschöpft ist, dann machen wir einen Zeilenumbruch
    while (fgets(s, 11, fp) != NULL){
        fputs(s, stdout); 
    }

    return 0;  
}

/*
soeren@T-480:~/Documents/sem4/bsn2/ue4$ time ./a2c > output_c.txt

real    0m0.646s
user    0m0.534s
sys     0m0.097s

Es ist langsamer da mein Buffer schlichtweg kleiner ist mit 11 bytes, realistisch ist es fast gleichschnell 
*/