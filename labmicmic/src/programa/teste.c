#include <mcs51/at89x52.h>

void teste(void) __interrupt IE0_VECTOR {
        P0_0 = 0;
        P0_1 = 1;
        P0_2 = 0;
        P0_3 = 1;
        P0_4 = 0;
        P0_5 = 1;
        P0_6 = 0;
        P0_7 = 1;
}

void teste2(void) __interrupt IE1_VECTOR {
        P0_0 = 1;
        P0_1 = 0;
        P0_2 = 1;
        P0_3 = 0;
        P0_4 = 1;
        P0_5 = 0;
        P0_6 = 1;
        P0_7 = 0;
}

void main(void) {
        P0_0 = 1;
        P0_1 = 0;
        P0_2 = 1;
        P0_3 = 0;
        P0_4 = 1;
        P0_5 = 0;
        P0_6 = 1;
        P0_7 = 0;
        EA = 1;
        IE = 0x81;
}
