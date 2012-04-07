#include <Arduino.h>

#include "Button.h"
#include "Grid.h"
#include "Nunchuk.h"

#define MOVE_CURSOR_REPEAT_DELAY 250

Nunchuk nunchuk;
Button  cButton;
Button  zButton;
Grid    grid;

bool running;

unsigned long lastMoveCursorTime;

void showOrHideCursor() {
    !running ? grid.showCursor() : grid.hideCursor();
}

void flipRunning() {
    running = !running;
    showOrHideCursor();
}

void processCState() {
    cButton.update(nunchuk.getCState());
    if (!running && cButton.isPressed()) grid.flipCellUnderCursor();
}

void processZState() {
    zButton.update(nunchuk.getZState());
    if (zButton.isPressed()) flipRunning();
}

void processUpDownLeftRightStates() {
    if (millis() - lastMoveCursorTime > MOVE_CURSOR_REPEAT_DELAY) {
        if (nunchuk.getUpState()) {
            grid.moveCursorUp();
            lastMoveCursorTime = millis();
        }
        if (nunchuk.getDownState()) {
            grid.moveCursorDown();
            lastMoveCursorTime = millis();
        }
        if (nunchuk.getLeftState()) {
            grid.moveCursorLeft();
            lastMoveCursorTime = millis();
        }
        if (nunchuk.getRightState()) {
            grid.moveCursorRight();
            lastMoveCursorTime = millis();
        }
    }
}

void processNunchukData() {
    processUpDownLeftRightStates();
    processCState();
    processZState();
}

void setup() {
    nunchuk.initialize();
    grid.initialize();
    showOrHideCursor();
}

void loop() {
    if (nunchuk.update()) processNunchukData();
    if (running) grid.createNextGeneration();
}
