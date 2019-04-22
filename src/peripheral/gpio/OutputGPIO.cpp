#include "peripheral/gpio/OutputGPIO.hpp"

peripheral::gpio::OutputGPIO::OutputGPIO(uint8_t i_u8Port, uint32_t i_u32Pin)
    : peripheral::GPIO(i_u8Port, i_u32Pin) {
	this->SetAsOutput();
}

void peripheral::gpio::OutputGPIO::SetOutput(bool i_bValue) {
	this->m_bState = i_bValue;
	this->UpdateState();
}

bool peripheral::gpio::OutputGPIO::GetOutput() { return this->m_bState; }

void peripheral::gpio::OutputGPIO::Toggle() {
	this->m_bState = !this->m_bState;
	this->UpdateState();
}

void peripheral::gpio::OutputGPIO::UpdateState() {
	if (this->m_bState) {
		GPIO_setOutputHighOnPin(this->m_u8Port, this->m_u32Pin);
	} else {
		GPIO_setOutputLowOnPin(this->m_u8Port, this->m_u32Pin);
	}
}
