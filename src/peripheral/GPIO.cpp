#include <stdio.h>
#include <iostream>

#include "driverlib.h"

#include "peripheral/GPIO.hpp"

peripheral::GPIO::GPIO(uint8_t i_u8Port, uint32_t i_u32Pin) {
	this->m_u8Port = i_u8Port;
	this->m_u32Pin = i_u32Pin;
}

peripheral::GPIO::GPIO(uint8_t i_u8Port, uint32_t u32Pin,
                       peripheral::gpio::Mode i_eMode) {
	peripheral::GPIO(i_u8Port, u32Pin);
	switch (i_eMode) {
		case peripheral::gpio::Mode::INPUT:
			this->SetAsInput();
			break;
		case peripheral::gpio::Mode::OUTPUT:
			this->SetAsOutput();
			break;
		case peripheral::gpio::Mode::INPUT_WITH_PULL_DOWN_RESISTOR:
			this->SetAsInputWithPullDownResistor();
			break;
		case peripheral::gpio::Mode::INPUT_WITH_PULL_UP_RESISTOR:
			this->SetAsInputWithPullUpResistor();
			break;
		case peripheral::gpio::Mode::PERIPHERAL_MODULE_FUNCTION_INPUT:
			this->SetAsPeripheralModuleFunctionInput();
			break;
		case peripheral::gpio::Mode::PERIPHERAL_MODULE_FUNCTION_OUTPUT:
			this->SetAsPeripheralModuleFunctionOutput();
			break;
		case peripheral::gpio::Mode::NONE:
		default:
			break;
	}
}

uint8_t peripheral::GPIO::GetPort() { return this->m_u8Port; }

uint32_t peripheral::GPIO::GetPin() { return this->m_u32Pin; }

void peripheral::GPIO::SetAsInput() {
	GPIO_setAsInputPin(this->m_u8Port, this->m_u32Pin);
}

void peripheral::GPIO::SetAsOutput() {
	GPIO_setAsOutputPin(this->m_u8Port, this->m_u32Pin);
}

void peripheral::GPIO::SetAsPeripheralModuleFunctionOutput() {
	// TODO [emilio]
}

void peripheral::GPIO::SetAsPeripheralModuleFunctionInput() {
	// TODO [emilio]
}

void peripheral::GPIO::SetAsInputWithPullDownResistor() {
	// TODO [emilio]
}
void peripheral::GPIO::SetAsInputWithPullUpResistor() {
	// TODO [emilio]
}

void peripheral::GPIO::enableInterrupt() {
	// TODO [emilio]
}
void peripheral::GPIO::disableInterrupt() {
	// TODO [emilio]
}

uint_fast16_t peripheral::GPIO::getInterruptStatus() {
	// TODO [emilio]
}

void peripheral::GPIO::clearInterruptFlag() {
	// TODO [emilio]
}

void peripheral::GPIO::interruptEdgeSelect(uint_fast8_t edgeSelect) {
	// TODO [emilio]
}

void peripheral::GPIO::setDriveStrengthHigh() {
	GPIO_setDriveStrengthHigh(this->m_u8Port, this->m_u32Pin);
}

void peripheral::GPIO::setDriveStrengthLow() {
	GPIO_setDriveStrengthHigh(this->m_u8Port, this->m_u32Pin);
}

/******************
 * STATIC FUNCTIONS
 ******************/

uint_fast16_t peripheral::GPIO::getEnabledInterruptStatus(
    uint_fast8_t selectedPort) {
	// TODO [emilio]
}
uint_fast16_t peripheral::GPIO::getEnabledInterruptStatus(GPIO* i_pGPIO) {
	// TODO [emilio]
}

void peripheral::GPIO::RegisterInterrupt(uint_fast8_t selectedPort,
                                         void (*intHandler)(void)) {
	// TODO [emilio]
}
void peripheral::GPIO::RegisterInterrupt(GPIO* i_pGPIO,
                                         void (*intHandler)(void)) {
	// TODO [emilio]
}

void peripheral::GPIO::UnregisterInterrupt(uint_fast8_t selectedPort) {
	// TODO [emilio]
}
void peripheral::GPIO::UnregisterInterrupt(GPIO* i_pGPIO) {
	// TODO [emilio]
}
