/* MICRO PROGRAM TO TEST ADDITIONS */
ldr r4, 100
ldr r5, 200
add r4, r5, r6
for(i=0;i<2; i++){
    #pragma unroll
    ldr r4, 100
    add r4, r5, r6
    for(k=2;k<0; k--){
        #pragma unroll
        nop
    }
}
stop

