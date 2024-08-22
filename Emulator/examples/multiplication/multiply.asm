lda_const 0x05   ; X = 5
sta 0x00         

lda_const 0x02   ; Y = 2
sta 0x01      

lda_const 0x01   ; load constant 1 into A
sta 0x03         ; store 1 into 0x03 to be used for later

loop:
lda 0x02         ; load the sum into A
ldb 0x01         ; load Y into B
add              ; add to the sum
sta 0x02         ; store sum

lda 0x00         ; load counter
ldb 0x03         ; load 1 into B
sub              ; decrement counter by 1
sta 0x00         ; store counter

ldb 0x04         ; load 0 into B
cmp              ; compare counter with register B (0)

je finished      ; if the counter is at zero, jump to finished
jmp loop         ; else repeat the loop

finished:
lda 0x02         ; Load the final result (res) into A
aout             ; Output the result, X * Y = 10
halt             ; Stop the program
