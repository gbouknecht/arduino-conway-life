TARGET = main_loop

SRC = src
BUILD = build

ARDUINO = /Applications/Arduino.app
ARDUINO_BIN = $(ARDUINO)/Contents/Resources/Java/hardware/tools/avr/bin
ARDUINO_ETC = $(ARDUINO)/Contents/Resources/Java/hardware/tools/avr/etc
ARDUINO_SRC = $(ARDUINO)/Contents/Resources/Java/hardware/arduino/cores/arduino
ARDUINO_OBJS = main.o \
               wiring.o \
               wiring_digital.o \
               pins_arduino.o \
               cxa_pure_virtual.o

VPATH = $(ARDUINO_SRC):$(SRC)

CC = $(ARDUINO_BIN)/avr-gcc
OBJCOPY = $(ARDUINO_BIN)/avr-objcopy
AVRDUDE = $(ARDUINO_BIN)/avrdude

MCU = atmega328p

CFLAGS = -Os -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=16000000L -I $(ARDUINO_SRC)

.PHONY:	all
all: upload

.PHONY:	build
build: init $(BUILD)/$(TARGET).hex

.PHONY:	init
init:
	@mkdir -p $(BUILD)

$(BUILD)/%.o: %.cpp
	@$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/$(TARGET).elf: $(addprefix $(BUILD)/,$(TARGET).o $(ARDUINO_OBJS))
	@$(CC) $(CFLAGS) -o $@ $^

$(BUILD)/$(TARGET).hex: $(BUILD)/$(TARGET).elf
	@$(OBJCOPY) -O ihex -R .eeprom $< $@

.PHONY:	upload
upload: build
	@$(AVRDUDE) -C $(ARDUINO_ETC)/avrdude.conf -p $(MCU) -P /dev/tty.usbmodem* -c stk500v1 -b 115200 -D -U flash:w:$(BUILD)/$(TARGET).hex:i

.PHONY:	clean
clean:
	@rm -rf $(BUILD)
