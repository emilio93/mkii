#include "peripheral/gpio/InputGPIO.hpp"

peripheral::gpio::InputGPIO::InputGPIO(uint8_t i_u8Port, uint32_t i_u32Pin,
                                       peripheral::gpio::InputMode i_eInputMode)
    : peripheral::GPIO(i_u8Port, i_u32Pin) {
	switch (i_eInputMode)
	{
		case peripheral::gpio::InputMode::NONE:
			this->SetAsInput();
			break;
		case peripheral::gpio::InputMode::PULL_DOWN_RESISTOR:
			this->SetAsInputWithPullDownResistor();
			break;
		case peripheral::gpio::InputMode::PULL_UP_RESISTOR:
			this->SetAsInputWithPullUpResistor();
			break;
		default:
			break;
	}
}

bool peripheral::gpio::InputGPIO::ReadValue() {
	return GPIO_getInputPinValue(this->GetPort(), this->GetPin());
}
