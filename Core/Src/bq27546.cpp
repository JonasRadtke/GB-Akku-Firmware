/*
 * bq27546.cpp
 *
 *  Created on: Feb 9, 2025
 *      Author: Sentry
 */

#include "bq27546.h"
#include <stdint.h>
#include "twi.h"


#define REG_CONTROL						0x00
#define REG_VOLTAGE_MV					0x08
#define REG_TIME_TO_EMPTY_MIN 			0x16
#define REG_FULL_CHARGE_CAPACITY_MAH  	0x18
#define REG_REMAINING_CAPACITY_MAH 		0x22
#define REG_STATE_OF_CHARGE_PERCENT 	0x2C
#define REG_STATE_OF_HEALTH_PERCENT_NUM 0x2E


bq27546::bq27546() {
	// TODO Auto-generated constructor stub

}

void bq27546::readVoltage(){
	this->voltage = (uint32_t)this->readRegisterUint16(REG_VOLTAGE_MV);
	return;
}

void bq27546::readTimeToEmpty(){
	this->timeToEmpty = (uint32_t)this->readRegisterUint16(REG_TIME_TO_EMPTY_MIN);
	return;
}

void bq27546::readFullCharheCapa(){
	this->fullChargeCapa = (uint32_t)this->readRegisterUint16(REG_FULL_CHARGE_CAPACITY_MAH);
	return;
}

void bq27546::readRemainCapa(){
	this->remainCapa = (uint32_t)this->readRegisterUint16(REG_REMAINING_CAPACITY_MAH);
	return;
}


uint32_t bq27546::readStateOfCharge(){
	this->stateOfCharge = (uint32_t)this->readRegisterUint16(REG_STATE_OF_CHARGE_PERCENT);
	return this->stateOfCharge;
}

void bq27546::readStateOfHealth(){
	this->stateOfHealth = (uint32_t)this->readRegisterUint16(REG_STATE_OF_HEALTH_PERCENT_NUM);
	return;
}

uint16_t bq27546::readRegisterUint16(uint8_t command){
	return this->readRegisterWord(command);
}

uint16_t bq27546::readRegisterWord(uint8_t command){
	uint8_t *commandPtr = &command;
	uint8_t data[2];
	uint8_t *dataPtr = data;
	uint16_t returnValue;
	HAL_I2C_Master_Transmit(&hi2c1, (this->twiAdress << 1), commandPtr, 1, 100);
	HAL_I2C_Master_Receive(&hi2c1, (this->twiAdress << 1), dataPtr, 2, 100);
	returnValue = (data[1] << 8) | data[0];
	return returnValue;
}
