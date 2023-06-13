#include "HMC5883.h"

void main(){
    twi_START();
while (1) {
    float angulo = HMC5883l_getHeadingDegrees();
    serial_put_etcetera();
    delayms(100);
}
}
