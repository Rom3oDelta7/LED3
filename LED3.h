/*

Simple library for controlling an RGB LED
So simple, we'll just declare the functions here and inline everything
Supports both common anode (DEFAULT) and common cathode devices

Copyright 2016 Rob Redford
   This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
   To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/

#ifndef LED3_H
#define LED3_H

#define	PWM_MIN_RESOLUTION	255				// minimum and maximum PWM resolution (top end is arbitrary, really)
#define PWM_MAX_RESOLUTION	2048

/*
 common RGB colors using "positive" values - any 6-byte value may be used - these are just for convenience
 These values were determined empirically, so they may need to be adjusted for your particular LED.
 Not all colors reproduce well, and yellow has so far been impossible to find.
 Since you are combining colors from 3 different LEDs, frosted LEDs appear to have a more pure color.
*/
#define LED3_RED		0xFF0000
#define LED3_GREEN		0x00FF00
#define LED3_BLUE		0x0000FF
#define LED3_MAGENTA	0xFF0090
#define LED3_CYAN		0x00FFFF
#define LED3_WHITE		0xFFFFFF
#define LED3_ORANGE		0xFF8600
#define LED3_PURPLE		0x7700FF
#define LED3_OFF		0x000000

typedef enum { LED3_ANODE, LED3_CATHODE } LED3Mode;

class LED3 {
	
public:
	LED3 (const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED);
	LED3 (const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED,  const LED3Mode mode);
	void setLED3Color ( const uint32_t color );
private:
	LED3Mode	_MODE;				// type of LED (common cathode/anode)
	uint16_t	_RESOLUTION;		// PWM resolution of the GPIO ports
	uint8_t		_LED_RED_PIN;		// LED pins
	uint8_t		_LED_GREEN_PIN;
	uint8_t		_LED_BLUE_PIN;
};

LED3::LED3 ( const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED) {
	_MODE = LED3_ANODE;								// default
#ifdef ESP8266
	_RESOLUTION = PWMRANGE;
#else
	_RESOLUTION = PWM_MIN_RESOLUTION;
#endif
	_LED_RED_PIN = redLED;
	_LED_GREEN_PIN = greenLED;
	_LED_BLUE_PIN = blueLED;
	
	pinMode(_LED_RED_PIN, OUTPUT);
	pinMode(_LED_GREEN_PIN, OUTPUT);
	pinMode(_LED_BLUE_PIN, OUTPUT);

}

LED3::LED3 ( const uint8_t redLED, const uint8_t greenLED, const uint8_t blueLED,  const LED3Mode mode) {
	_MODE = mode;
#ifdef ESP8266
	_RESOLUTION = PWMRANGE;
#else
	_RESOLUTION = PWM_MIN_RESOLUTION;
#endif
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

#endif