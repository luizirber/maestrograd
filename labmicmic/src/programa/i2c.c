#include "i2c.h"

int main() {
    //Esse celular é de São carlos mesmo ??
    SendData(9);
    SendData(0);
    SendData(9);
    SendData(0);
    // =  P Ai não precisa pagar, antes de dar o sinal
    SendData(8);
    SendData(1);   
    SendData(2);   
    SendData(8);   
    SendData(0);   
    SendData(9);   
    SendData(4);   
    SendData(7);      

    return 0;
}
