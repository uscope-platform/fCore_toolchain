//
// Created by fils on 29/06/2021.
//`

int main(int arg1, float arg2){

    #pragma input(a, r1)
    int a;

    #pragma input(b, r2)
    int b;

    int c;

    c = a + b;

    #pragma output (test, r10);
    int test = c*5/6;
}
