TARGET = life

SRC = src
BUILD = build

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(addprefix $(BUILD)/,$(notdir $(SRCS:.cpp=.o)))

DEPEND_MAKEFILE = depend

ARDUINO = /Applications/Arduino.app
ARDUINO_BIN = $(ARDUINO)/Contents/Resources/Java/hardware/tools/avr/bin
ARDUINO_ETC = $(ARDUINO)/Contents/Resources/Java/hardware/tools/avr/etc
ARDUINO_SRC = $(ARDUINO)/Contents/Resources/Java/hardware/arduino/cores/arduino
ARDUINO_LIB = $(ARDUINO)/Contents/Resources/Java/libraries
ARDUINO_LIBS = $(addprefix $(ARDUINO_LIB)/,Wire \
                                           Wire/utility)
ARDUINO_OBJS = $(addprefix $(BUILD)/,main.o \
                                     wiring.o \
                                     wiring_digital.o \
                                     pins_arduino.o \
                                     HardwareSerial.o \
				     Print.o \
				     WString.o \
                                     Wire.o \
                                     twi.o \
                                     cxa_pure_virtual.o)

VPATH = $(ARDUINO_SRC):$(ARDUINO_LIBS):$(SRC)

CC = $(ARDUINO_BIN)/avr-gcc
OBJCOPY = $(ARDUINO_BIN)/avr-objcopy
AVRDUDE = $(ARDUINO_BIN)/avrdude

MCU = atmega328p

CFLAGS = -Os -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=16000000L $(addprefix -I,$(ARDUINO_SRC) $(ARDUINO_LIBS))

.PHONY:	all
all: upload

.PHONY:	build
build: $(DEPEND_MAKEFILE) makedirs $(BUILD)/$(TARGET).hex

$(DEPEND_MAKEFILE): $(SRCS)
	@$(CC) -MM $(CFLAGS) $^ | sed 's/\([^ ]*\)\.o[ :]*/$(BUILD)\/\1.o: /' > $@

include $(DEPEND_MAKEFILE)

.PHONY:	makedirs
makedirs:
	@mkdir -p $(BUILD)

$(BUILD)/%.o: %.cpp
	@$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/$(TARGET).elf: $(OBJS) $(ARDUINO_OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

$(BUILD)/$(TARGET).hex: $(BUILD)/$(TARGET).elf
	@$(OBJCOPY) -O ihex -R .eeprom $< $@

.PHONY:	upload
upload: build
	@$(AVRDUDE) -C $(ARDUINO_ETC)/avrdude.conf -p $(MCU) -P /dev/tty.usbmodem* -c stk500v1 -b 115200 -D -U flash:w:$(BUILD)/$(TARGET).hex:i

.PHONY:	clean
clean:
	@rm -rf $(DEPEND_MAKEFILE) $(BUILD) doxygen
