#include <Wire.h>

#include "Nunchuk.h"

#define NUNCHUK_ADDRESS 0x52

void Nunchuk::initialize() {
    Wire.begin();
    sendHandshake();
    delay(1);
    receive();
}

bool Nunchuk::update() {
    sendRequest();
    delay(1);
    receive();
    return receivedBytesCount == NUNCHUK_DATA_SIZE;
}

void Nunchuk::sendHandshake() {
    Wire.beginTransmission(NUNCHUK_ADDRESS);
    Wire.write((byte) 0x40);
    Wire.write((byte) 0x00);
    Wire.endTransmission();
}

void Nunchuk::sendRequest() {
    Wire.beginTransmission(NUNCHUK_ADDRESS);
    Wire.write((byte) 0x00);
    Wire.endTransmission();
}

void Nunchuk::receive() {
    Wire.requestFrom(NUNCHUK_ADDRESS, NUNCHUK_DATA_SIZE);
    for (receivedBytesCount = 0; (receivedBytesCount < NUNCHUK_DATA_SIZE) && Wire.available(); receivedBytesCount++) {
        data[receivedBytesCount] = decodeByte(Wire.read());
    }
}

byte Nunchuk::decodeByte(byte b) {
    return (b ^ 0x17) + 0x17;
}

byte Nunchuk::getXPosition() {
    return data[0];
}

byte Nunchuk::getYPosition() {
    return data[1];
}

bool Nunchuk::getUpState() {
    return getYPosition() > 160;
}

bool Nunchuk::getDownState() {
    return getYPosition() < 96;
}

bool Nunchuk::getLeftState() {
    return getXPosition() < 96;
}

bool Nunchuk::getRightState() {
    return getXPosition() > 160;
}

uint16_t Nunchuk::getXAcceleration() {
    return (data[2] << 2) | ((data[5] >> 2) & 0x03);
}

uint16_t Nunchuk::getYAcceleration() {
    return (data[3] << 2) | ((data[5] >> 4) & 0x03);
}

uint16_t Nunchuk::getZAcceleration() {
    return (data[4] << 2) | ((data[5] >> 6) & 0x03);
}

bool Nunchuk::getCState() {
    return !((data[5] >> 1) & 0x01);
}

bool Nunchuk::getZState() {
    return !(data[5] & 0x01);
}

void Nunchuk::print() {
    printHeader();
    printLabelValue("x position    : ", getXPosition());
    printLabelValue("y position    : ", getYPosition());
    printLabelValue("x acceleration: ", getXAcceleration());
    printLabelValue("y acceleration: ", getYAcceleration());
    printLabelValue("z acceleration: ", getZAcceleration());
    printLabelValue("c state?        ", getCState());
    printLabelValue("z state?        ", getZState());
}

void Nunchuk::printHeader() {
    Serial.println("Nunchuk data:");
}

void Nunchuk::printLabelValue(String label, uint16_t value) {
    Serial.print("    ");
    Serial.print(label);
    Serial.println(value);
}
