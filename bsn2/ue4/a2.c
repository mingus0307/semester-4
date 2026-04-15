#include <stdio.h>


int main(void){
    int c; 
    FILE* fp = fopen("input.txt", "r"); 
    // wir müssen hier so seltsam zuweisen, weil wir durch den call ja bereits Sachen aus dem Buffer rausnehmen
    // wenn wir das nicht tun, verlieren wir infos durch die Überprüfung
    while ((c = fgetc(fp)) != EOF){
        fputc(c , stdout); 
    }

    return 0;  
}