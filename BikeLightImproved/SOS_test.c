#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int time, ctime, ptime;
int LEDstate = 1;
const int freq = 10;

void LEDchange( int *state){
    if (*state == 0) {
        *state = 1;
    }
    else {
        *state = 0;
    }
}

int S ( void ){
    static i;

    if (ctime - ptime > freq){
        ptime = ctime;
        i++;
        LEDstate = i%2;
        printf("%d\n", LEDstate);
        if ( i > 5){
            i = 0;
            return 1;
        }
    }
    return 0;
}

int O ( void ){
    static i;

    if( ctime - ptime > freq){
        ptime = ctime;
        i++;
        if ( i % 4 == 0 ) LEDstate = 0;
        else LEDstate = 1;
        printf("%d\n", LEDstate);
        if ( i > 11){
            i = 0;
            return 1;
        }
    }
    return 0;
}

int main( int argc, char *argv[]){
    int iterate, i, j, k = 0;
    
    for(iterate = 0; iterate < 500; ++iterate) {
        //Increment the time function
        time++;
        ctime = time; 
        
        // Switch the j for each individual letter
        switch(j) {
            case 0: k = S(); break;
            case 1: k = O(); break;
            case 2: k = S(); break;
        }
        if ( k == 1){
            k = 0;
            j++;
            if (j > 2) {
                j = 0;
                return;
            }
        }
    }
}   

