# 3-Color RGB LED Arduino Library
LED3 is a simple library to control the colors on a 3-color (red, green, blue) LED. This library supports both common cathode and common anode modes.
For a common cathode LED, the MCU is a current source and you set each pin connected to the R, G, and B leads HIGH to turn them on. The LED has a common ground.
With a common anode LED, the MCU is a current sink. You have a common anode that is set to Vcc, and you set each pin connected to the R, G, and B leads LOW to turn the LED on.
In both cases, be sure to have a current limiting resistor on each of the red, green, and blue lines between the MCU and the LED.
(See [LEDCALC] for an online tool to help you determine the current resistor to use).


# Programming Interface
## Constructors
You have a choice of 2 constructors:
```C++
LED3 (const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED);
```
For a common anode LED, you simply declare the MCU pin connected to each of the red, green, and blue LED leads.

```C++
LED3 (const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED,  const LED3Mode mode);
```
Use this constructor to declare a common cathode LED.
Choices for the _mode_ parameter are:

|Parameter|Purpose|
|---|---|
**LED3_CATHODE**|common cathode
**LED3_ANODE**|common anode

The **LED_ANODE** mode is not strictly necessary but is included for completeness.

## Functions
```C++
void setLED3Color ( const uint32_t color );
```
Sets the LED _color_ to the specified RGB value. Values are created by using a 24-bit value,
with the most significant byte (byte 2) representing red, byte 1 representing green, and the least significant byte (byte 0) representing blue.
The following colors are predefined:

|Color|Hexadecimal value|
|---|---|
LED3_RED|0xFF0000
LED3_GREEN|0x00FF00
LED3_BLUE|0x0000FF
LED3_CYAN|0x00FFFF
LED3_WHITE|0xFFFFFF
LED3_ORANGE|0xFF8600
LED3_PURPLE|0x7700FF
LED3_OFF|0x000000

To turn the LED off, set the color to **LED_OFF** or just _0_.


# Examples
1. _LightCycle.ino_: Runs through the standard colors, switches off, then cycles again.
2. _ChooseColor.ino_: Reads a 24-bit heaxadecimal color code from the serial port and displays that color.

# Installation

There is still no Zip download button in Bitbucket (at least not that I can find) so to install this library,
click on the "Downloads" link on the left side menu and "Download Repository" on the next page.
This will download a .zip file that you can install by using the "Include Library>Add .ZIP Library" menu commands in the Arduino IDE.

Of course, you may also clone this repository and manually install the files if you prefer.

# Copyright Notice

Copyright 2016 Rob Redford
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
To view a copy of this license, visit [BY-NC-SA].

[LEDCALC]: http://ledcalc.com/
[BY-NC-SA]: http://creativecommons.org/licenses/by-nc-sa/4.0
