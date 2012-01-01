#include "Screen.h"

void Screen::initialize() {
    tv.begin(PAL);
}

void Screen::draw() {
    tv.draw_circle(50, 50, 20, WHITE);    // TODO: Remove this line.
    // TODO: Implement.
}
