#ifndef Nunchuk_h
#define Nunchuk_h

#include <Arduino.h>

#define NUNCHUK_DATA_SIZE 6

/**
 * This class implements an interface to the Nintendo Nunchuk controller.
 *
 * Usage:
 *
 * \code
 * #include "Nunchuk.h"
 * 
 * Nunchuk nunchuk;
 * 
 * void setup() {
 *     nunchuk.initialize();
 * }
 * 
 * void loop() {
 *     if (nunchuk.update()) {
 *         // Use Nunchuk::get... methods to query updated data.
 *     }
 *     // Introduce some delay.
 * }
 * \endcode
 */
class Nunchuk {
private:
    byte data[NUNCHUK_DATA_SIZE];
    byte receivedBytesCount;
public:
    void initialize();

    /**
     * \returns true if and only if the update was successful
     */
    bool update();

    byte     getXPosition();
    byte     getYPosition();
    bool     getUpState();
    bool     getDownState();
    bool     getLeftState();
    bool     getRightState();
    uint16_t getXAcceleration();
    uint16_t getYAcceleration();
    uint16_t getZAcceleration();
    bool     getCState();
    bool     getZState();

    /**
     * Prints the data in human-readable form to the serial port.
     *
     * Make sure you have opened the serial port in your setup method:
     *
     * \code
     * void setup() {
     *     Serial.begin(9600);
     * }
     * \endcode
     */
    void print();
private:
    void sendHandshake();
    void sendRequest();
    void receive();
    byte decodeByte(byte b);
    void printHeader();
    void printLabelValue(String label, uint16_t value);
};

#endif
