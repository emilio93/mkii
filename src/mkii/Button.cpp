#include <string>

#include "mkii/Button.hpp"

bool mkii::Button::m_bIsTrackingS1 = false;
bool mkii::Button::m_bIsPushActiveS1 = false;
bool mkii::Button::m_bPushHasTimeoutS1 = false;
mkii::Button* mkii::Button::m_pPushButtonS1 = NULL;
peripheral::Timer32* mkii::Button::m_pTimer32S1 = NULL;
mkii::Led* mkii::Button::m_pLed = NULL;

const uint32_t mkii::Button::m_u32PushTimeoutCountS1 = 100;

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

peripheral::gpio::InputGPIO* mkii::Button::GetGPIO() {
	return this->m_pButtonGPIO;
}

void mkii::Button::SetButtonId(mkii::button::ButtonId i_eButtonId) {
	this->m_eButtonId = i_eButtonId;
}

mkii::button::ButtonId mkii::Button::GetButtonId() { return this->m_eButtonId; }

void mkii::Button::StartTrackPush(peripheral::Timer32* i_pTimer32,
                                  mkii::Led* i_pLed) {
	switch (this->GetButtonId()) {
		case mkii::button::ButtonId::S1:
			if (!mkii::Button::m_bIsTrackingS1) {
				if (mkii::Button::m_bIsPushActiveS1) {
					break;
				}
				mkii::Button::m_bIsPushActiveS1 = true;
				mkii::Button::m_bPushHasTimeoutS1 = false;

				mkii::Button::m_pPushButtonS1 = this;
				mkii::Button::m_pTimer32S1 = i_pTimer32;
				mkii::Button::m_pLed = i_pLed;

				mkii::Button::m_bIsTrackingS1 = true;

				this->GetGPIO()->ClearInterruptFlag();
				this->GetGPIO()->EnableInterrupt();
				peripheral::GPIO::RegisterInterrupt(
				    this->GetGPIO(), mkii::Button::PushInterruptHandlerS1);
			}
			break;

		default:
			break;
	}
}

void mkii::Button::StopTrackPush() {
	switch (this->GetButtonId()) {
		case mkii::button::ButtonId::S1:
			if (mkii::Button::m_bIsTrackingS1) {
				mkii::Button::m_pPushButtonS1 = NULL;
				mkii::Button::m_pTimer32S1 = NULL;

				mkii::Button::m_bIsTrackingS1 = false;

				peripheral::GPIO::UnregisterInterrupt(this->GetGPIO());
			}
			break;

		default:
			break;
	}
}

void mkii::Button::PushInterruptHandlerS1(void) {
	mkii::Button::m_pPushButtonS1->GetGPIO()->ClearInterruptFlag();
	mkii::Button::m_pLed->Toggle();
}