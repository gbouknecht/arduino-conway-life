TARGET = main_loop

ARDUINO = /Applications/Arduino.app
ARDUINO_BIN = $(ARDUINO)/Contents/Resources/Java/hardware/tools/avr/bin
ARDUINO_ETC = $(ARDUINO)/Contents/Resources/Java/hardware/tools/avr/etc
ARDUINO_SRC = $(ARDUINO)/Contents/Resources/Java/hardware/arduino/cores/arduino
ARDUINO_OBJS = main.o \
               wiring.o \
               wiring_digital.o \
               pins_arduino.o \
               cxa_pure_virtual.o

VPATH = $(ARDUINO_SRC)

CC = $(ARDUINO_BIN)/avr-gcc
OBJCOPY = $(ARDUINO_BIN)/avr-objcopy
AVRDUDE = $(ARDUINO_BIN)/avrdude

MCU = atmega328p

CFLAGS = -Os -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=16000000L -I $(ARDUINO_SRC)

all: upload

build: $(TARGET).hex

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(TARGET).elf: $(TARGET).o $(ARDUINO_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: $(TARGET).hex
	$(AVRDUDE) -C $(ARDUINO_ETC)/avrdude.conf -p $(MCU) -P /dev/tty.usbmodem* -c stk500v1 -b 115200 -D -U flash:w:$<:i

clean:
	rm -f *.o *.elf *.hex

.PHONY:	all build upload clean
