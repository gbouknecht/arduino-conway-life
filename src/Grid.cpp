#include "Grid.h"

void Grid::initialize() {
    tv.begin(PAL, (GRID_WIDTH + 2 + 7) & 0xf8 /* nearest multiply of 8 */, GRID_HEIGHT + 2);
    tv.draw_rect(0, 0, GRID_WIDTH + 1, GRID_HEIGHT + 1, WHITE);
}

CellState Grid::getCell(uint8_t x, uint8_t y) {
    return (tv.get_pixel(x + 1, y + 1) == BLACK) ? DEAD : ALIVE;
}

void Grid::setCell(uint8_t x, uint8_t y, CellState cellState) {
    tv.set_pixel(x + 1, y + 1, (cellState == DEAD) ? BLACK : WHITE);
}

void Grid::createNextGeneration() {
    createNextGenerationIntoShadowGrid();
    copyShadowGridToScreen();
}

CellState Grid::getShadowGridCell(uint8_t x, uint8_t y) {
    uint8_t bitMask = 0x80 >> (x % 8);
    return (shadowGrid[x / 8][y] & bitMask) ? ALIVE : DEAD;
}

void Grid::setShadowGridCell(uint8_t x, uint8_t y, CellState cellState) {
    uint8_t bitMask = 0x80 >> (x % 8);
    if (cellState == DEAD) {
        shadowGrid[x / 8][y] &= ~bitMask;
    } else {
        shadowGrid[x / 8][y] |= bitMask;
    }
}

void Grid::createNextGenerationIntoShadowGrid() {
    for (uint8_t x = 0; x < GRID_WIDTH; x++) {
        for (uint8_t y = 0; y < GRID_HEIGHT; y++) {
            setShadowGridCell(x, y, applyRules(getCell(x, y), countNeighbours(x, y)));
        }
    }
}

uint8_t Grid::countNeighbours(uint8_t x, uint8_t y) {
    uint8_t result = 0;
    for (int8_t dx = -1; dx <= 1; dx++) {
        for (int8_t dy = -1; dy <= 1; dy++) {
            if ((dx == 0) && (dy == 0)) continue;
            uint8_t nx = ((x == 0) && (dx == -1)) ? GRID_WIDTH  - 1 : ((x + dx) % GRID_WIDTH);
            uint8_t ny = ((y == 0) && (dy == -1)) ? GRID_HEIGHT - 1 : ((y + dy) % GRID_HEIGHT);
            result += (getCell(nx, ny) == ALIVE) ? 1 : 0;
        }
    }
    return result;
}

CellState Grid::applyRules(CellState cellState, uint8_t numberOfNeighbours) {
    if (cellState == DEAD) {
        return (numberOfNeighbours == 3) ? ALIVE : DEAD;
    } else {
        return ((numberOfNeighbours == 2) || (numberOfNeighbours == 3)) ? ALIVE : DEAD;
    }
}

void Grid::copyShadowGridToScreen() {
    for (uint8_t x = 0; x < GRID_WIDTH; x++) {
        for (uint8_t y = 0; y < GRID_HEIGHT; y++) {
            setCell(x, y, getShadowGridCell(x, y));
        }
    }
}
