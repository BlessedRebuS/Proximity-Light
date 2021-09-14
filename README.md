# Proximity-Light
![alt text](https://github.com/BlessedRebuS/Proximity-Light/blob/main/images/LightSensor%20v1.png)
Sensor Light powered by a ultrasound module (HC-SR04) built on a chip. (SMD version). 
When the proximity sensor sees an obsacle (for example your hand) the relays are toggled **(ON-OFF)** / **(OFF-OF)** and the 12v powers the pins.
The button triggers an interrupt (ATMega328P comes with D2 and D3 digital pin that can be used as interrupts, in this project only the D3 is used) that cycles 3 states:

* Relay 1 ON Relay 2 OFF
* Relay 1 ON Relay 2 ON
* Relay 1 OFF Relay 2 OFF

The project idea is to put two led strips in the pair of pins near the supply that can help you illuminate the kitchen/bathroom/other rooms. Leds can be replaced with all type of stuff you want but it hasn't to drain much current (Max around 0.1 amp), you have only to solder your device in place. Now are only supported devices without data pins, so you have to use only the **VCC** and **GND**.

[See polarity and button](https://github.com/BlessedRebuS/Proximity-Light/blob/main/images/PinButton.png)

# Board


## Electronic Board
Created with Autodesk EAGLE and Fusion360 Electronic.

To connect all pins we simply used autorouting, commit to suggest changes.

![alt text](https://github.com/BlessedRebuS/Proximity-Light/blob/main/images/Board.png)

## Board Schematic - Libraries
You can find all the libraries *(Footprint, Symbols and 3DModels)* [Here](https://github.com/BlessedRebuS/Proximity-Light/tree/main/libraries/Footprints)

![alt text](https://github.com/BlessedRebuS/Proximity-Light/blob/main/images/Schematic.png)

## 3D Model

Designed and rendered in Fusion360

![alt text](https://media.giphy.com/media/gLZiwmqNYszEZtdC1Y/giphy.gif?cid=790b7611a83148cbe7ad602f8bc8b3268413f0216be1d08f&rid=giphy.gif&ct=g)


![3D Model STL](https://github.com/BlessedRebuS/Proximity-Light/blob/main/Light-Sensor/Board/LightSensor.stl)
# Components

* ATMega328P  [Read more](#about-the-atmega328p)
* 22 PF Capacitors (Not polarized) 2x
* 20 MHZ Quartz Oscillator
* 220-1k OHM Resistor
* Ultrasonic Sensor (HC-SR04)
* 12 to 5V DC Mosfet
* 12V Supply Holder
* 12v Relays x2
* Button
* 2x1 pins x2
* 2x3 pins

# About the ATMega328P

ATMega328p is a very versatile processor, mounted on Arduino, that can be used also separately with a different pinout. In this case the base clock 8MHZ is replaced with the 16MHZ clock (not necessary) connected to the two grounded capacitors to generate the oscillation.

**How to program it?** I suggest to use the [USBASP programmer](www.learningaboutelectronics.com/Articles/Program-AVR-chip-using-a-USBASP-with-10-pin-cable.php) (6 or 10 PIN), but you can use an Arduino using "Arduino as ISP" programming.
You

## The clock
As [Here](https://doc.riot-os.org/group__boards__atmega328p.html) is explained:

> The ATmega328p has two internal oscillators clocked at 8MHz and at 128kHz that allow it to be operated without any external clock source or crystal. By default the fuses are configured to use the internal 8MHz oscillator and a clock divider resulting in a clock speed of 1MHz. By clearing the CKDIV8 fuse the clock divider can be disabled to operate the ATmega328p at 8MHz without an external clock source. This can be done like this:
> 
> `avrdude -c usbtiny -p m328p -B 32 -U lfuse:w:0xe2:m`
> 
> (Replace usbtiny with the ISP programmer you are using. The -B 32 might be needed on some ISP programmers to communicate with slow ATmega MCUs. It will not be needed anymore after the clock device has been disabled.)
This "board" is configured to use 8MHz as core clock, so that the ATmega328p runs at the highest frequency possible without external clock sources.
By setting the environment variable ATMEGA328P_CLOCK to a custom frequency in Hz (e.g. 1000000 for 1MHz), this core clock can be changed easily. Refer to the datasheet on how to configure the ATmega328p to use an external crystal, an external clock source or the clock divider.
