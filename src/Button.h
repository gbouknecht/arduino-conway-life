#ifndef Button_h
#define Button_h

/**
 * This class may be used to represent a physical button.
 *
 * Usage:
 *
 * \code
 * #include "Button.h"
 *
 * Button button;
 *
 * void loop() {
 *     button.update(...);    // Update button with current state of physical button.
 *     // Use Button::is... methods to check for specific events.
 * }
 * \endcode
 */
class Button {
private:
    bool previousState;
    bool currentState;
public:

    /**
     * \param currentState
     *     true if and only if the physical button is currently held down
     */
    void update(bool currentState);

    /**
     * \return
     *     true if and only if state of button was changed from false to true
     */
    bool isPressed();
};

#endif
