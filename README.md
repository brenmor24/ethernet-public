# ETHERNET EMBEDDED SYSTEM

The goal of this project is to explore the ethernet protocol and understand its use cases for sending information across a network from an embedded system. I achieved this using an Atmega328p microcontroller by taking voltage readings on an analog pin every second and sending the data off to a server on my LAN which console-logs the results.

[demonstration](https://youtu.be/2yh66Vl7pvo)

## COMPONENTS
- Atmega328p Microcontroller
- HD44780 LCD Screen
- ENC28J60 Ethernet Module
- Raspberry Pi 2B Rev 1.1 (python socket server)
- EA6300 Linksys Router

## PROGRAM FLOW
- The user adjusts a potentiometer which varies the load on one of the Atmega’s analog pins.
- This reading is transformed into a digital value between zero and five volts.
- An LCD connected to the Atmega displays this value for reference.
- The Atmega takes this digital reading, wraps it in an ethernet frame, and places it in the TX buffer on an ENC28J60 Ethernet module using the SPI protocol.
- This packet is routed through the LAN router over ethernet and delivered to a Raspberry Pi specified by its local IP within the frame.
- A simple python socket program running on the raspberry pi unpacks this and prints the result.
  

## FILE STRUCTURE

  > **NOTE:** The networking and LCD libraries were sourced from the following two authors:
  
Vojtěch Brožek -> [ENC28J60](https://github.com/Triplkrypl/avr-net-enc28j60)
Efthymios Koktsidis -> [HD44780](https://github.com/efthymios-ks/AVR-HD44780)
