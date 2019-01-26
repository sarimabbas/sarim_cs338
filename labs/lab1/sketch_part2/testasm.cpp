#include "testasm.h"

/* the attribute "used" tells the compiler to not inline this function */
__attribute__((used))
unsigned int testasm(unsigned char a, unsigned char b) {
  unsigned int out;

  asm volatile(R"(

   rjmp start_of_assembly

   .data
   ; any data values/static storage can go here

   .text

start_of_assembly:
   ; Your assembly language program goes here
   ;
   ; For this example, your program must not modify any registers other than 
   ; r24 and r25. In other words, save and restore all the registers that
   ; are modified by your code.

   ; Tell the compiler to move the arguments a, b into registers 
   ; r24, r25 respectively
   ;
   mov r24,%1
   mov r25,%2
   ;
   ;  --- YOUR CODE GOES HERE ---
   ;       r24 = a, r25 = b
   ;

start:
    ; prolog
    push r12            ; use r13:r12 for word
    push r13
    push r16            ; use r17:r16 for word
    push r17

    ; body
    ;clr r24             ; clr r25:24
    ;clr r25
    ;call sumval         ; a + b
    ;movw r16, r24       ; save the result

    clr r24
    clr r25
    call diffval        ; abs(a - b)
    movw r12, r24       ; save the result

    clr r24
    clr r25
    movw r24, r12       ; save the final result

    ; epilog
    pop r17
    pop r16
    pop r13
    pop r12
    rjmp end_of_assembly

diffval:
    ; prolog
    push r16
    push r17
    mov r16, %1     ; arg a - 3 
    mov r17, %2     ; arg b - 10

    ; body
    cp r17, r16     ; compare b with a

    brsh samehigher       ; 
    sub r16, r17          ; a > b
    ; mov r24, r16
    ldi r24, 1

    samehigher:           ; b >= a
    sub r17, r16
    ; mov r24, r17 
    ldi r24, 0

    ; epilog
    pop r17
    pop r16
    ret

sumval: 
    ; prolog
    ; use r16 and r17 for storage
    push r16
    push r17
    mov r16, %1    ; arg a
    mov r17, %2    ; arg b

    ; body
    add r16, r17    ; add r16 into r17
    clr r17         ; set all the bits of r17 to 0
    adc r17, r1     ; add the zero-reg + carry into r17
    movw r24, r16   ; move r17:r16 to the 16-bit word in r25:r24

    ; epilog
    pop r17
    pop r16
    ret

   ;
   ;  --- YOUR CODE ENDS ---
   ;      The result must be in the register pair r25:r24
   ;      You can also rjmp to the label end_of_assembly if you need to.
   ;
end_of_assembly: 
   ; -- move r25:r24 to the 16-bit word in variable out
   movw %0,r24

)"
               : "=w"(out) /* out is %0, and a 16-bit variable that is modified
                              by the assembly language */
               : "r"(a), "r"(b) /* a is %1, b is %2, both are register-sized
                                   variables */
               : "r25", "r24"); /* r24, r25 are modified by this assembly
                                   language fragment */

  return out;
}
