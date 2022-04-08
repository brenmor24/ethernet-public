# Makefile
MCU=atmega328p
F_CPU=16000000UL
CC=avr-gcc
OBJCOPY=avr-objcopy
TARGET=client
PORT=/dev/ttyACM0

clean:
	rm bin/*

build: clean
	$(CC) -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o bin/client.o src/client.c
	$(CC) -mmcu=$(MCU) bin/client.o -o bin/client
	$(OBJCOPY) -O ihex -R .eeprom bin/client bin/client.hex

load: build
	avrdude -p $(MCU) -P $(PORT) -c arduino -D -U flash:w:bin/$(TARGET).hex:i