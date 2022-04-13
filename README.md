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
  
## USAGE
### CONFIGURATION

Choose the correct pin and port mappings between each of your peripherals and the Atmega. Click the following links for respective peripheral mapping locations in the codebase:

LCD ->[HD44780](https://github.com/brenmor24/ethernet-public/blob/main/lib/lcd/HD44780_Settings.h#L35-L43)
ETHERNET -> [ENC28J60](https://github.com/brenmor24/ethernet-public/blob/main/lib/lcd/HD44780_Settings.h#L36-L43)

If you'd like to change your systems IP and MAC addresses, this can be done [here](https://github.com/brenmor24/ethernet-public/blob/main/src/client.c#L17-L18). You also need to specify the IP address of your server by changing the serverIp [here](https://github.com/brenmor24/ethernet-public/blob/main/src/client.c#L41) and the port number [here](https://github.com/brenmor24/ethernet-public/blob/main/src/client.c#L41) as the second argument to TcpConnect.

### EXECUTION

Start by spinning up the python socket server outlined in ```server/server.py``` . Make sure the IP and port numbers match the ones chosen above. Next, connect the Atmega to your computer via USB and run ```make build``` to load the program. The PORT value in the Makefile needs to match your USB port.

  > **NOTE:** The networking and LCD libraries were sourced from the following two authors:
  
Vojtěch Brožek -> [ENC28J60](https://github.com/Triplkrypl/avr-net-enc28j60)
Efthymios Koktsidis -> [HD44780](https://github.com/efthymios-ks/AVR-HD44780)
