/* MICRO PROGRAM TO TEST ADDITIONS */
ldr r4, 100
ldr r5, 200
add r4, r5, r6
for(i=0;i<2; i++){
    #pragma unroll
    ldr r4, 100
    add r4, r5, r6
    for(i=2;i<0; i--){
        #pragma unroll
        nop
    }
}
stop

