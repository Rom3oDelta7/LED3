/*
 Example sketch for LED3 library
 
 Reads a color code in hex from the serial port and displays that color
 
 For common anode implementations, attach the common lead to +Vcc and attach each RGB lead to the color pin through a current limiting resistor (current sink)
 For common cathode implementations, attach the common lead to ground, and attach each RGB lead to the color pin through a current limiting resistor (current source)
 
 Copyright 2016 Rob Redford
   This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
   To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/

#include <LED3.h>

#define RED_PIN		12			// pin assignments for ESP-12E. Change to match your confiruation
#define GREEN_PIN	14			// make sure there is a current limiting resistor attached to each color lead
#define BLUE_PIN	16


LED3		led(RED_PIN, GREEN_PIN, BLUE_PIN, LED3_CATHODE);
//LED3		led(RED_PIN, GREEN_PIN, BLUE_PIN);						// common anode constructor


void setup ( void ) {
	Serial.begin(9600);
	while (!Serial);
	Serial.println("\n\nInput 6-digit hexadecimal color values (RRGGBB)\n");
}

void loop ( void ) {
	uint32_t 	colorValue = 0;
	int 		bytePosition = 5;
	
	Serial.print("Input Color: ");
	while ( bytePosition >= 0 ) {
		byte inChar;
		
		// ignore non-conforming inputs
		if ( Serial.available() ) {
			byte inChar = Serial.read();
			if ( isDigit(inChar) ) {
				colorValue |= ((inChar - '0') << (bytePosition-- * 4));
			} else if ( isUpperCase(inChar) ) {
				colorValue |= ((inChar - 'A' + 10) << (bytePosition-- * 4));
			} else if ( isLowerCase(inChar) ) {
				colorValue |= ((inChar - 'a' + 10) << (bytePosition-- * 4));
			}
		}
	}
	Serial.println(colorValue, HEX);
	Serial.println();
	Serial.flush();
	led.setLED3Color(colorValue);
}
