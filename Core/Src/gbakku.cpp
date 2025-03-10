/*
 * gbakku.cpp
 *
 *  Created on: Feb 8, 2025
 *      Author: Sentry
 */

#include "gbakku.h"
#include "main.h"
#include "leds.h"

leds ledInterface;
extern TIM_HandleTypeDef htim21;
extern TIM_HandleTypeDef htim22;
volatile uint32_t wakeUpRequest;
volatile uint32_t sleeping;

gbakku::gbakku() {
	// TODO Auto-generated constructor stub

}

void gbakku::init(){
	this->setChargerConfig();
	this->charger.ResetWatchDog();
}

void gbakku::run(){

	// Sleep and Wake Up
	if(!charging && !wakeUpRequest && !ledInterface.getShowSocStatus() &&(this->sleepingDelay + 1000 < HAL_GetTick())){
		sleeping = 1;
		this->charger.disableCharging();
		this->goingToSleep();

	}
	if(wakeUpRequest){
		wakeUpRequest = 0;
		this->wakeUp();
		sleeping = 0;
		this->sleepingDelay = HAL_GetTick();
	}

	// Get Status and Reset Watchdog
	if(this->timeStatus + 1000 < HAL_GetTick()){
		this->timeStatus = HAL_GetTick();
		this->getStatus();
		this->charger.ResetWatchDog();
		if(charger.detectToggle(this->charging, HAL_GetTick())){
			this->cantChargeDetected = 1;
		}
	}

	if(this->ovpUvpStepTime + 20000 < HAL_GetTick()){
			this->ovpUvpStepTime = HAL_GetTick();
			this->ovpUvpCycle();
		}


	// Status LED aktualisieren
	ledInterface.showSocCalc(this->stateOfCharge, this->charging);



	return;
}

void gbakku::setChargerConfig(){
	this->charger.enableCharging();
	this->charger.inputPowerSel2400();
	this->charger.setInputCurrentLimit(1500);
	this->charger.setChargeCurrentLimit(1000);
	this->charger.setPrechargeLimit(40);
	this->charger.setTerminationLimit(60);
	this->charger.chargeBitEnable(1);
	return;
}

void gbakku::getStatus(){
//	this->stateOfCharge = this->fuelGauge.readStateOfCharge();
	this->charging = this->charger.getCharingAndPower();
	this->charger.readChargerStatus();
}

void gbakku::goingToSleep() {
	HAL_TIM_Base_Stop_IT(&htim21);
	ledInterface.ledTurnOff();
	HAL_SuspendTick();
	HAL_TIM_Base_Start_IT(&htim22);
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void gbakku::wakeUp() {
	HAL_TIM_Base_Stop_IT(&htim22);
	HAL_TIM_Base_Start_IT(&htim21);
	HAL_ResumeTick();
	this->init();
}

void gbakku::ovpUvpCycle(){
	if(this->cantChargeDetected){
		switch(this->ovpUvpStep){
		case 0:
			this->charger.disableCharging();
			this->ovpUvpStep = 1;
		    break;
		case 1:
			this->charger.readWriteRegister(0x04, 0xF8, 0x08);
			this->charger.enableCharging();
			this->ovpUvpStep = 2;
		    break;
		case 2:
			this->charger.readWriteRegister(0x04, 0xF8, 0x40);
			this->ovpUvpStep = 3;
			this->cantChargeDetected = 0;
		    break;
		}
	}
	else{
		this->ovpUvpStep = 0;
	}
}


