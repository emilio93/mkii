#include "mkii/Button.hpp"

mkii::Button::Button(mkii::button::ButtonId i_eButtonId) {
	this->SetButtonId(i_eButtonId);
	switch (this->GetButtonId()) {
		case mkii::button::ButtonId::S1:
			this->m_pButtonGPIO = new peripheral::gpio::InputGPIO(
			    mkii::BUTTON_PORT, mkii::BUTTON_S1_PIN,
			    peripheral::gpio::InputMode::PULL_UP_RESISTOR);
			break;
		case mkii::button::ButtonId::S2:
			this->m_pButtonGPIO = new peripheral::gpio::InputGPIO(
			    mkii::BUTTON_PORT, mkii::BUTTON_S2_PIN,
			    peripheral::gpio::InputMode::PULL_UP_RESISTOR);
			break;
		default:
			break;
	}
}

void mkii::Button::TrackButtonPush(mkii::Led* i_pLed) {
	mkii::event::Push::GetPush(this, i_pLed)->Init();
}

void mkii::Button::IgnoreButtonPush() { mkii::event::Push::GetPush()->End(); }

peripheral::gpio::InputGPIO* mkii::Button::GetGPIO() {
	return this->m_pButtonGPIO;
}

void mkii::Button::SetButtonId(mkii::button::ButtonId i_eButtonId) {
	this->m_eButtonId = i_eButtonId;
}

mkii::button::ButtonId mkii::Button::GetButtonId() { return this->m_eButtonId; }


void mkii::Button::SetInterruptDirection(peripheral::gpio::Edge i_eEdge) {
	this->GetGPIO()->InterruptEdgeSelect(i_eEdge);

}

void mkii::Button::SetInterrupt(void (*i_funcHandler)(void)) {
	peripheral::GPIO::RegisterInterrupt(this->GetGPIO(), i_funcHandler);
	this->GetGPIO()->EnableInterrupt();
}

void mkii::Button::EndInterrupt() {
	this->GetGPIO()->ClearInterruptFlag();
	peripheral::GPIO::UnregisterInterrupt(this->GetGPIO());
	this->GetGPIO()->DisableInterrupt();
}