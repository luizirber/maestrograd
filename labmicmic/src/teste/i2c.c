#include <mcs51/at89x52.h>
#include "i2c.h"

int main() {
    
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
