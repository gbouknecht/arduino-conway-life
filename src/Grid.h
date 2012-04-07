#ifndef Grid_h
#define Grid_h

#include "TVout.h"

#define GRID_WIDTH  50
#define GRID_HEIGHT 40

enum CellState { DEAD, ALIVE };

/**
 * This class is responsible for the Life grid. It provides methods to setup
 * the initial pattern and to create next generations. It also displays the
 * grid on a TV screen.
 *
 * Note that in general it is better practice to separate the grid from the
 * code that displays the grid. But due to the limited memory size of the
 * Arduino's SRAM, we have to be creative. Therefore, this class will use the
 * TVout library to store the current generation as black/white pixels
 * displayed on the screen.
 */
class Grid {
private:
    TVout   tv;
    uint8_t shadowGrid[((GRID_WIDTH + 7) / 8) /* 8 cells per byte */][GRID_HEIGHT];
    uint8_t cursorX;
    uint8_t cursorY;
    bool    cursorVisible;
    bool    savedCursorVisible;
public:
    void      initialize();
    CellState getCell(uint8_t x, uint8_t y);
    void      setCell(uint8_t x, uint8_t y, CellState cellState);
    void      createNextGeneration();
    void      clear();
    void      flipCellUnderCursor();
    void      showCursor();
    void      hideCursor();
    void      moveCursorUp();
    void      moveCursorDown();
    void      moveCursorLeft();
    void      moveCursorRight();
    void      moveCursorTo(uint8_t x, uint8_t y);
private:
    CellState getShadowGridCell(uint8_t x, uint8_t y);
    void      setShadowGridCell(uint8_t x, uint8_t y, CellState cellState);
    void      createNextGenerationIntoShadowGrid();
    uint8_t   countNeighbours(uint8_t x, uint8_t y);
    CellState applyRules(CellState cellState, uint8_t numberOfNeighbours);
    void      copyShadowGridToScreen();
    void      saveAndHideCursor();
    void      restoreCursor();
    void      invertPixelsAround(uint8_t x, uint8_t y);
    void      invertPixel(uint8_t x, uint8_t y);
};

#endif
