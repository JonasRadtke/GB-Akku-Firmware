/*
 * bq27546.h
 *
 *  Created on: Feb 9, 2025
 *      Author: Sentry
 */

#ifndef SRC_BQ27546_H_
#define SRC_BQ27546_H_

#include <stdint.h>
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

class bq27546 {
private:
	uint8_t twiAdress = 0x55;

	uint32_t voltage = 0;
	uint32_t timeToEmpty = 0;
	uint32_t fullChargeCapa = 0;
	uint32_t remainCapa = 0;
	uint32_t stateOfCharge = 0;
	uint32_t stateOfHealth = 0;

public:
	bq27546();
	void readVoltage();
	void readTimeToEmpty();
	void readFullCharheCapa();
	void readRemainCapa();
	uint32_t readStateOfCharge();
	void readStateOfHealth();

	uint16_t readRegisterUint16(uint8_t command);
	uint16_t readRegisterWord(uint8_t command);
};

#endif /* SRC_BQ27546_H_ */
