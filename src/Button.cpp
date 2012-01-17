#include "Button.h"

void Button::update(bool currentState) {
    previousState = this->currentState;
    this->currentState = currentState;
}

bool Button::isPressed() {
    return !previousState && currentState;
}
