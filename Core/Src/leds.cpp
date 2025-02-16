/*
 * leds.cpp
 *
 *  Created on: Feb 14, 2025
 *      Author: Sentry
 */

#include "main.h"
#include "leds.h"

leds::leds() {
	// TODO Auto-generated constructor stub

}

uint32_t leds::getShowSocStatus(){
	return this->showSoc;
}

void leds::setShowSoc(){
	this->showSoc = 1;
	this->showSocTime = HAL_GetTick();
}

void leds::showSocCalc(uint32_t soc, uint32_t charging){
	if(this->showSoc){
		if(soc > 90){
			this->led = 5;
		}
		else if (soc > 75){
			this->led = 4;
		}
		else if (soc > 50){
			this->led = 3;
		}
		else if (soc > 25){
			this->led = 2;
		}
		else{
			this->led = 1;
		}

		if(this->showSocTime + 3000 < HAL_GetTick()){
			this->showSoc = 0;
		}

	}

	if(!showSoc && !charging){
		this->led = 0;
	}

	if((charging == 1) && !this->showSoc){
		if(this->chargingTime + 200 < HAL_GetTick()){
			this->chargingTime = HAL_GetTick();
			switch(this->charigingLedStep){
			case 0:
				this->led = 1;
				this->charigingLedStep = 1;
				break;
			case 1:
				this->led = 2;
				this->charigingLedStep = 2;
				break;
			case 2:
				this->led = 3;
				this->charigingLedStep = 3;
				break;
			case 3:
				this->led = 4;
				this->charigingLedStep = 4;
				break;
			case 4:
				this->led = 5;
				this->charigingLedStep = 0;
				break;
			}
		}
	}
	else if ((charging == 2) && !this->showSoc){
		this->led = 5;
	}

	if(this->led == 1){
		this->led1 = 1; this->led2 = 0; this->led3 = 0; this->led4 = 0; this->led5 = 0;
	}
	else if(this->led == 2){
		this->led1 = 1; this->led2 = 1; this->led3 = 0; this->led4 = 0; this->led5 = 0;
	}
	else if(this->led == 3){
		this->led1 = 1; this->led2 = 1; this->led3 = 1; this->led4 = 0; this->led5 = 0;
	}
	else if(this->led == 4){
		this->led1 = 1; this->led2 = 1; this->led3 = 1; this->led4 = 1; this->led5 = 0;
	}
	else if(this->led == 5){
		this->led1 = 1; this->led2 = 1; this->led3 = 1; this->led4 = 1; this->led5 = 1;
	}
	else if(this->led == 0){
		this->led1 = 0; this->led2 = 0; this->led3 = 0; this->led4 = 0; this->led5 = 0;
	}


}

void leds::ledTurnOff(){
	LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
	LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
	LL_GPIO_ResetOutputPin(LED3_GPIO_Port, LED3_Pin);
}

void leds::charliePlexing(){

	switch (this->step) {
	//LED D1
	case 0:
		LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
		LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
		LL_GPIO_ResetOutputPin(LED3_GPIO_Port, LED3_Pin);
		LL_GPIO_SetPinMode(LED1_GPIO_Port, LED1_Pin, LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinMode(LED2_GPIO_Port, LED2_Pin, LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinMode(LED3_GPIO_Port, LED3_Pin, LL_GPIO_MODE_INPUT);
		this->step = 11;
		break;

	case 11:
		if (this->led1) {
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
		} else {
			LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
		}
		LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
		this->step = 20;
		break;

		//LED D2
	case 20:
		LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
		LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
		LL_GPIO_ResetOutputPin(LED3_GPIO_Port, LED3_Pin);
		LL_GPIO_SetPinMode(LED1_GPIO_Port, LED1_Pin, LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinMode(LED2_GPIO_Port, LED2_Pin, LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinMode(LED3_GPIO_Port, LED3_Pin, LL_GPIO_MODE_INPUT);
		this->step = 21;
		break;

	case 21:
		if (this->led2) {
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
		} else {
			LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
		}
		LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
		this->step = 30;
		break;

		//LED D5
	case 30:
		LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
		LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
		LL_GPIO_ResetOutputPin(LED3_GPIO_Port, LED3_Pin);
		LL_GPIO_SetPinMode(LED1_GPIO_Port, LED1_Pin, LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinMode(LED2_GPIO_Port, LED2_Pin, LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinMode(LED3_GPIO_Port, LED3_Pin, LL_GPIO_MODE_OUTPUT);
		this->step = 31;
		break;

	case 31:
		if (this->led3) {
			LL_GPIO_SetOutputPin(LED3_GPIO_Port, LED3_Pin);
		} else {
			LL_GPIO_ResetOutputPin(LED3_GPIO_Port, LED3_Pin);
		}
		LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
		this->step = 40;
		break;

		//LED D5
	case 40:
		LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
		LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
		LL_GPIO_ResetOutputPin(LED3_GPIO_Port, LED3_Pin);
		LL_GPIO_SetPinMode(LED1_GPIO_Port, LED1_Pin, LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinMode(LED2_GPIO_Port, LED2_Pin, LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinMode(LED3_GPIO_Port, LED3_Pin, LL_GPIO_MODE_OUTPUT);
		this->step = 41;
		break;

	case 41:
		if (this->led4) {
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
		} else {
			LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
		}
		LL_GPIO_ResetOutputPin(LED3_GPIO_Port, LED3_Pin);
		this->step = 50;
		break;

		//LED D5
	case 50:
		LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
		LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
		LL_GPIO_ResetOutputPin(LED3_GPIO_Port, LED3_Pin);
		LL_GPIO_SetPinMode(LED1_GPIO_Port, LED1_Pin, LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinMode(LED2_GPIO_Port, LED2_Pin, LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinMode(LED3_GPIO_Port, LED3_Pin, LL_GPIO_MODE_OUTPUT);
		this->step = 51;
		break;

	case 51:
		if (this->led5) {
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
		} else {
			LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
		}
		LL_GPIO_ResetOutputPin(LED3_GPIO_Port, LED3_Pin);
		this->step = 0;
		break;



	}
	return;
}

