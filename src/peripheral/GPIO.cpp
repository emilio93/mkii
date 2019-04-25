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

void peripheral::GPIO::SetAsPeripheralModuleFunctionInput(uint8_t i_u8Mode) {
	GPIO_setAsPeripheralModuleFunctionInputPin(this->GetPort(), this->GetPin(),
	                                           i_u8Mode);
}

void peripheral::GPIO::SetAsInputWithPullDownResistor() {
	GPIO_setAsInputPinWithPullDownResistor(this->GetPort(), this->GetPin());
}

void peripheral::GPIO::SetAsInputWithPullUpResistor() {
	GPIO_setAsInputPinWithPullUpResistor(this->GetPort(), this->GetPin());
}

void peripheral::GPIO::EnableInterrupt() {
	if (this->HasInterruptFunction()) {
		GPIO_enableInterrupt(this->GetPort(), this->GetPin());
	}
}

void peripheral::GPIO::DisableInterrupt() {
	if (this->HasInterruptFunction()) {
		GPIO_getInterruptStatus(this->GetPort(), this->GetPin());
	}
}

uint_fast16_t peripheral::GPIO::GetInterruptStatus() {
	if (this->HasInterruptFunction()) {
		return GPIO_getInterruptStatus(this->GetPort(), this->GetPin());
	} else {
		return 0xff;
	}
}

void peripheral::GPIO::ClearInterruptFlag() {
	if (this->HasInterruptFunction()) {
		GPIO_clearInterrupt(this->GetPort(), this->GetPin());
	}
}

void peripheral::GPIO::InterruptEdgeSelect(uint_fast8_t edgeSelect) {
	GPIO_interruptEdgeSelect(this->GetPort(), this->GetPin(), edgeSelect);
}

void peripheral::GPIO::SetDriveStrengthHigh() {
	GPIO_setDriveStrengthHigh(this->m_u8Port, this->m_u32Pin);
}

void peripheral::GPIO::SetDriveStrengthLow() {
	GPIO_setDriveStrengthHigh(this->m_u8Port, this->m_u32Pin);
}

bool peripheral::GPIO::HasInterruptFunction() {
	return this->GetPort() == peripheral::gpio::Port::PORT1 ||
	       this->GetPort() == peripheral::gpio::Port::PORT2 ||
	       this->GetPort() == peripheral::gpio::Port::PORTA;
}

/******************
 * STATIC FUNCTIONS
 ******************/

uint_fast16_t peripheral::GPIO::GetEnabledInterruptStatus(
    uint_fast8_t i_u8SelectedPort) {
	return GPIO_getEnabledInterruptStatus(i_u8SelectedPort);
}

uint_fast16_t peripheral::GPIO::GetEnabledInterruptStatus(GPIO* i_pGPIO) {
	return peripheral::GPIO::GetEnabledInterruptStatus(i_pGPIO->GetPort());
}

void peripheral::GPIO::RegisterInterrupt(uint_fast8_t i_u8SelectedPort,
                                         void (*i_fIntHandler)(void)) {
	GPIO_registerInterrupt(i_u8SelectedPort, i_fIntHandler);
}

void peripheral::GPIO::RegisterInterrupt(GPIO* i_pGPIO,
                                         void (*i_fIntHandler)(void)) {
	peripheral::GPIO::RegisterInterrupt(i_pGPIO->GetPort(), i_fIntHandler);
}

void peripheral::GPIO::UnregisterInterrupt(uint_fast8_t i_u8SelectedPort) {
	GPIO_unregisterInterrupt(i_u8SelectedPort);
}

void peripheral::GPIO::UnregisterInterrupt(GPIO* i_pGPIO) {
	peripheral::GPIO::UnregisterInterrupt(i_pGPIO->GetPort());
}
