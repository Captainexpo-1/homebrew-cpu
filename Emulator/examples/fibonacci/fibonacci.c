#include <stdio.h>

/*
This c program is the equvalent of the code in fibonacci.asm
*/

typedef unsigned char byte;

int main(){
    byte a = 0;
    byte b = 1;
    byte c = 0;

    loop:
        c = a;
        a = b;
        b = c + b;

        printf("%d\n", a);
        
        if (a > 220) 
            goto finished;
        else
            goto loop;

    finished:
        return 0;
}