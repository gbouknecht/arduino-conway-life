#include <Arduino.h>

#include "Nunchuk.h"
#include "Grid.h"

Nunchuk nunchuk;
Grid    grid;

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
        // TODO: Implement.
    }
    grid.createNextGeneration();
}
