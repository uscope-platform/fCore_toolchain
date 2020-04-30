/* MICRO PROGRAM TO TEST ADDITIONS */
ldr r4, 100
ldr r5, 200
add r4, r5, r6
for(i=0;i<200; i++){
    ldr r4, 100
    add r4, r5, r6
    for(i=0;i<20; i++){
       nop
    }
}
stop

