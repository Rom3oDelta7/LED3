/*

Simple library for controlling an RGB LED

Supports both common anode (DEFAULT) and common cathode devices

Color reference charts: http://cloford.com/resources/colours/500col.htm

Copyright 2016 Rob Redford
   This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
   To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/

#include "LED3.h"

LED3::LED3 ( const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED) {
	_MODE = LED3_ANODE;								// default
	_RESOLUTION = PWM_MIN_RESOLUTION;				// default
	_LED_RED_PIN = redLED;
	_LED_GREEN_PIN = greenLED;
	_LED_BLUE_PIN = blueLED;
	
	pinMode(_LED_RED_PIN, OUTPUT);
	pinMode(_LED_GREEN_PIN, OUTPUT);
	pinMode(_LED_BLUE_PIN, OUTPUT);
}

LED3::LED3 ( const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED,  const LED3Mode mode) {
	_MODE = mode;
	_RESOLUTION = PWM_MIN_RESOLUTION;			// default
	_LED_RED_PIN = redLED;
	_LED_GREEN_PIN = greenLED;
	_LED_BLUE_PIN = blueLED;
	
	pinMode(_LED_RED_PIN, OUTPUT);
	pinMode(_LED_GREEN_PIN, OUTPUT);
	pinMode(_LED_BLUE_PIN, OUTPUT);
}

LED3::LED3 ( const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED,  const LED3Mode mode, const int pwmResolution) {
	_MODE = mode;
	_RESOLUTION = constrain(pwmResolution, PWM_MIN_RESOLUTION, PWM_MAX_RESOLUTION);
	_LED_RED_PIN = redLED;
	_LED_GREEN_PIN = greenLED;
	_LED_BLUE_PIN = blueLED;
	
	pinMode(_LED_RED_PIN, OUTPUT);
	pinMode(_LED_GREEN_PIN, OUTPUT);
	pinMode(_LED_BLUE_PIN, OUTPUT);
}

void LED3::setLED3Color ( const uint32_t color ) {
	uint8_t redPWM, greenPWM, bluePWM;
	
	redPWM   = (color & 0xFF0000) >> 16;
	greenPWM = (color & 0xFF00) >> 8;
	bluePWM   = (color & 0xFF);
	if ( _MODE == LED3_ANODE ) {
		// for common anode configs, the logic is active LOW (turn on LED with 0), so we invert the values
		redPWM = map(redPWM, 0, 0xFF, 0xFF, 0);
		greenPWM = map(greenPWM, 0, 0xFF, 0xFF, 0);
		bluePWM = map(bluePWM, 0, 0xFF, 0xFF, 0);
	}
	if ( _RESOLUTION > PWM_MIN_RESOLUTION ) {
		redPWM = map(redPWM, 0, PWM_MIN_RESOLUTION, 0, _RESOLUTION);
		greenPWM = map(greenPWM, 0, PWM_MIN_RESOLUTION, 0, _RESOLUTION);
		bluePWM = map(bluePWM, 0, PWM_MIN_RESOLUTION, 0, _RESOLUTION);
	}
	analogWrite(_LED_RED_PIN, redPWM);
	analogWrite(_LED_GREEN_PIN, greenPWM);
	analogWrite(_LED_BLUE_PIN, bluePWM);
}