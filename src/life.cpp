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

void processCZState() {
    cButton.update(nunchuk.getCState());
    zButton.update(nunchuk.getZState());
    if (cButton.isDown() && zButton.isDown()) {
        if (running) flipRunning();
        grid.clear();
    } else if (!running && cButton.isPressed()) {
        grid.flipCellUnderCursor();
    } else if (zButton.isPressed()) {
        flipRunning();
    }
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
    processCZState();
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
