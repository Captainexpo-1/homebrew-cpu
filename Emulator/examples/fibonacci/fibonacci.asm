
lda_const 0x00
sta 0x00        ; A

lda_const 0x01
sta 0x01        ; B

lda_const 0x00
sta 0x02        ; C

lda_const 0xC8  ; 200 
sta 0x03

loop:
lda 0x00    ; A
sta 0x02    ; C = A

lda 0x01    ; B
sta 0x00    ; A = B

lda 0x02
ldb 0x01    ; C
add         ; C + B
sta 0x01    ; B = C + B

aout

ldb 0x03    ; 200
cmp         ; compare fibbonaci number with 200

jg finished ; if fibbonaci number is greater than 200, jump to finished
jmp loop    ; else repeat the loop

finished:
halt