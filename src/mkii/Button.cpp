#include "mkii/Button.hpp"

mkii::Button::Button(mkii::button::ButtonId i_eButtonId) {
	this->SetButtonId(i_eButtonId);
	switch (this->GetButtonId()) {
		case mkii::button::ButtonId::S1:
			this->m_pButtonGPIO = new peripheral::gpio::InputGPIO(
			    mkii::BUTTON_PORT, mkii::BUTTON_S1_PIN);
			break;
		case mkii::button::ButtonId::S2:
			this->m_pButtonGPIO = new peripheral::gpio::InputGPIO(
			    mkii::BUTTON_PORT, mkii::BUTTON_S2_PIN);
			break;
		default:
			break;
	}
}

void mkii::Button::TrackButtonPush(mkii::Led* i_pLed,
                                   peripheral::Timer32* i_pTimer32) {
	mkii::event::Push::GetPush(this, i_pLed, i_pTimer32)->Init();
}

void mkii::Button::IgnoreButtonPush() { mkii::event::Push::GetPush()->End(); }

peripheral::gpio::InputGPIO* mkii::Button::GetGPIO() {
	return this->m_pButtonGPIO;
}

void mkii::Button::SetButtonId(mkii::button::ButtonId i_eButtonId) {
	this->m_eButtonId = i_eButtonId;
}

mkii::button::ButtonId mkii::Button::GetButtonId() { return this->m_eButtonId; }