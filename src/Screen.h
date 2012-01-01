#ifndef Screen_h
#define Screen_h

#include "TVout.h"

/**
 * This class implements the methods to display the Life grid on a TV screen.
 *
 * Usage:
 *
 * \code
 * #include "Screen.h"
 * 
 * Screen screen;
 * 
 * void setup() {
 *     screen.initialize();
 * }
 * \endcode
 */
class Screen {
private:
    TVout tv;
public:
    void initialize();
    void draw();
};

#endif
