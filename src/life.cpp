#include <WProgram.h>

#include "Nunchuk.h"

Nunchuk nunchuk;

void setup() {
    Serial.begin(9600);
    nunchuk.initialize();
}

void loop() {
    if (nunchuk.update()) {
        nunchuk.print();
    }
    delay(1000);
}
