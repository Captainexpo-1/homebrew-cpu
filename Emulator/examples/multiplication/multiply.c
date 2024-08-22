#include <stdio.h>

/*

This c program is the equvalent of the code in multiply.asm

*/


typedef unsigned char byte;

int main(){
    byte a = 5; // 0x00
    byte b = 2; // 0x01
    byte sum = 0; // 0x02

    loop:
        sum += b;
        a--;

        if (a == 0) 
            goto finished;
        else
            goto loop;
    finished:
        printf("%d", sum);
        return 0;
}