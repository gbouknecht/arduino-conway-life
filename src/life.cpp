#include <Arduino.h>

#include "Button.h"
#include "Grid.h"
#include "Nunchuk.h"

Nunchuk nunchuk;
Button  zButton;
Grid    grid;

bool running;

void setup() {
    nunchuk.initialize();
    grid.initialize();
    // TODO: Remove the following lines.
    grid.setCell(1, 3, ALIVE);
    grid.setCell(2, 3, ALIVE);
    grid.setCell(3, 3, ALIVE);
    grid.setCell(3, 2, ALIVE);
    grid.setCell(2, 1, ALIVE);
    // TODO: END
}

void loop() {
    if (nunchuk.update()) {
        zButton.update(nunchuk.getZState());
        if (zButton.isPressed()) {
            running = !running;
        }
    }
    if (running) {
        grid.createNextGeneration();
    }
}
