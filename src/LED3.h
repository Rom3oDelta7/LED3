/*

Simple library for controlling an RGB LED

Supports both common anode (DEFAULT) and common cathode devices

Color reference charts: http://cloford.com/resources/colours/500col.htm

Copyright 2016 Rob Redford
   This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
   To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/

#ifndef LED3_H
#define LED3_H

#include "Arduino.h"

#define PWM_MIN_RESOLUTION	255				// minimum and maximum PWM resolution
#define PWM_MAX_RESOLUTION	4096				// may need to chnage this for MCUs that have greater resolution

/*
 common RGB colors using "positive" values - any 6-byte value may be used - these are just for convenience
 however, some many not reproduce well depending on the LED
*/
#define LED3_RED			0xFF0000
#define LED3_GREEN		0x00FF00
#define LED3_BLUE			0x0000FF
#define LED3_MAGENTA		0xFF00FF
#define LED3_YELLOW		0xFFFF00
#define LED3_CYAN			0x00FFFF
#define LED3_WHITE		0xFFFFFF
#define LED3_ORANGE		0xFFA500
#define LED3_PURPLE		0x800080
#define LED3_OFF			0x000000

typedef enum { LED3_ANODE, LED3_CATHODE } LED3Mode;

class LED3 {
	
public:
	LED3 (const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED);
	LED3 (const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED,  const LED3Mode mode);
	LED3 (const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED,  const LED3Mode mode, const int pwmResolution);
	void setLED3Color ( const uint32_t color );
	uint32_t getLED3Color ( void );
private:
	LED3Mode		_MODE;				// typ of LED (common cathode/anode)
	uint16_t		_RESOLUTION;		// PWM resolution of the GPIO port
	uint8_t		_LED_RED_PIN;		// LED pins
	uint8_t		_LED_GREEN_PIN;
	uint8_t		_LED_BLUE_PIN;
	uint32_t		_CURRENT_COLOR;
};

#endif