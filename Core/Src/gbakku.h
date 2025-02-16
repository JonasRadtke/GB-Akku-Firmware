/*
 * gbakku.h
 *
 *  Created on: Feb 8, 2025
 *      Author: Sentry
 */

#ifndef SRC_GBAKKU_H_
#define SRC_GBAKKU_H_

#include <stdint.h>

#include "bq25619.h"
#include "bq27546.h"

class gbakku {
private:
	uint32_t leds = 0;
	bq25619 charger = bq25619(0x6A);
	bq27546 fuelGauge;

	uint32_t charging = 0;
	uint32_t stateOfCharge = 0;

	uint32_t timeStatus = 0;
	uint32_t sleepingDelay = 0;
public:
	gbakku();
	void init();
	void run();
	void setChargerConfig();
	void getStatus();

	void goingToSleep();
	void wakeUp();
};

#endif /* SRC_GBAKKU_H_ */
