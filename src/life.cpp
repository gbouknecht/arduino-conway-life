#include <Arduino.h>

#include "Nunchuk.h"
#include "Screen.h"

Nunchuk nunchuk;
Screen  screen;

void setup() {
    nunchuk.initialize();
    screen.initialize();
    screen.draw();
}

void loop() {
    if (nunchuk.update()) {
        // TODO: Implement.
    }
    delay(1000);
}
