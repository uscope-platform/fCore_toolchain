ldr r1, 1
ldr r2, 2
ldr r3, 3
ldr r4, 4
ldr r5, 5
ldr r6, 6
ldr r7, 7
ldr r8, 8
ldr r9, 9
ldr r10, 10
ldr r11, 11
ldr r12, 12
ldr r13, 13
ldr r14, 14
ldr r15, 15
nop
nop
nop
nop
nop
add r4, r5, r6
addi r4, 500, r7
for(i=0;i<4074; i++){
        #pragma unroll
        nop
    }
stop