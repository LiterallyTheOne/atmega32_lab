# Session 1: Introduction

## NSK108

Is a board that is made for educational purposes.
It is build by [Noavaran Electronic](http://www.ne-ir.com/).
It supports AVR and MCS-51 microcontroller,
In this class we are working on an AVR microcontroller,
called Atmega32.

![nsk108](figures/nsk108.jpg)

In the picture above, you can see the board that we are
working on this class.

## Programmer

To program our code to the microcontroller, we are
using ISP programmer. In the picture below you can
see the programmer that we are using right now.
We are connecting this programmer to our pc via usb
port.
Also, we connect the ISP to the board.

![programmer](figures/programmer.jpg)

## ATmega32

ATmega32 is an 8-bit AVR microcontroller developed
by Atmel (now Microchip Technology).
Commonly used in embedded systems, robotics,
and industrial automation due to its low power
consumption and ease of use.

* 32 KB of flash memory
  * non-volatile
  * Where our program is stored
* 2 KB of SRAM
  * volatile 
  * Where our variables, stack operations and buffer is stored
* 1 KB of EEPROM
  * non-volatile 
  * Config that we want it to remain 
* 32 general-purpose I/O pins
* 8-channel 10-bit ADC
* 3 timers (one 8-bit, two 16-bit)
* UART, SPI, and I2C communication interfaces

![atmega32_pins](figures/atmega32_pins.png)

In the picture above, you can see the pins on
ATmega32.
There are 32 geneal-purpose I/O pins:
* PA
* PB
* PC
* PD

Each pin is connected to a component on the board
which we are going to explain them in the according
lesson.
All of these 32 pins can be set as an output or an input.
(using their DDR)

## jumper

![jumper](figures/jumper.jpg)

![jumper_on](figures/jumper_on.jpg)

![jumper_off](figures/jumper_off.jpg)

![jumper_none](figures/jumper_none.jpg)

## ProgISP

### Erase

### Load Flash

### Write Flash

### Auto

## Code vision AVR

### Create a new project

## Hello world