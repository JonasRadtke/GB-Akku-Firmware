/*
 * leds.h
 *
 *  Created on: Feb 14, 2025
 *      Author: Sentry
 */

#ifndef SRC_LEDS_H_
#define SRC_LEDS_H_

class leds {
private:
	uint32_t step = 0;
	uint32_t led1 = 0;
	uint32_t led2 = 0;
	uint32_t led3 = 0;
	uint32_t led4 = 1;
	uint32_t led5 = 0;

	uint32_t led = 0;

	uint32_t showSoc = 0;
	uint32_t showSocTime = 0;

	uint32_t charigingLedStep = 0;
	uint32_t chargingTime = 0;
public:
	leds();
	void setShowSoc();
	uint32_t getShowSocStatus();
	void showSocCalc(uint32_t soc, uint32_t charging);
	void ledTurnOff();
	void charliePlexing();
};

#endif /* SRC_LEDS_H_ */
