/* MICRO PROGRAM TO TEST ADDITIONS */
ldr r4, 100
add r4, r5, r6
mov r3, r4
bgt r2, r3, 0x500
ble r2, r3, 0x500
beq r2, r3, 0x500
bne r2, r3, 0x500
stop

