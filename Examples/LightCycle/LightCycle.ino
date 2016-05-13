/*
 Example sketch for LED3 library
 
 Runs through the standard colors, switches off, then cycles again
 
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

uint32_t	colors[] = {LED3_RED, LED3_GREEN, LED3_BLUE, LED3_MAGENTA, LED3_CYAN, LED3_WHITE, LED3_ORANGE, LED3_PURPLE, LED3_OFF};

LED3		led(RED_PIN, GREEN_PIN, BLUE_PIN, LED3_CATHODE);
//LED3		led(RED_PIN, GREEN_PIN, BLUE_PIN);						// constructor for common anode

void setup ( void ) {
	Serial.begin(9600);
	while (!Serial);
}

void loop ( void ) {
	for ( auto color : colors ) {
		led.setLED3Color(color);
		Serial.print("Color: "); Serial.println(color, HEX);
		delay(5000);
	}	
}