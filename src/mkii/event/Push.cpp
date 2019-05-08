#include "mkii/event/Push.hpp"

mkii::event::Push* mkii::event::Push::m_pInstance = 0;

const uint32_t mkii::event::Push::m_u32StaticTimeoutCount =
    mkii::event::push::TIMEOUT_COUNT;

bool mkii::event::Push::m_bStaticIsTracking = false;
bool mkii::event::Push::m_bStaticIsActive = false;
bool mkii::event::Push::m_bStaticHasTimeout = false;

mkii::Button* mkii::event::Push::m_pStaticButton = NULL;
mkii::Led* mkii::event::Push::m_pStaticLed = NULL;
mkii::Timer* mkii::event::Push::m_pStaticTimer = NULL;

mkii::event::Push* mkii::event::Push::GetPush() {
	if (mkii::event::Push::m_pInstance == 0) {
		return NULL;
	}
	return mkii::event::Push::m_pInstance;
}

mkii::event::Push* mkii::event::Push::GetPush(mkii::Button* i_pButton,
                                              mkii::Led* i_pLed,
                                              mkii::Timer* i_pTimer) {
	if (mkii::event::Push::m_pInstance == 0) {
		mkii::event::Push::m_pInstance =
		    new mkii::event::Push(i_pButton, i_pLed, i_pTimer);
	} else {
		mkii::event::Push::m_pInstance->SetButton(i_pButton);
		mkii::event::Push::m_pInstance->SetLed(i_pLed);
		mkii::event::Push::m_pInstance->SetTimer(i_pTimer);
	}
	return mkii::event::Push::m_pInstance;
}

void mkii::event::Push::Init() {
	if (!mkii::event::Push::m_bStaticIsTracking) {
		if (mkii::event::Push::m_bStaticIsActive) {
			return;
		}
		mkii::event::Push::m_bStaticIsActive = true;
		mkii::event::Push::m_bStaticHasTimeout = false;

		mkii::event::Push::m_pStaticButton = this->m_pButton;
		mkii::event::Push::m_pStaticLed = this->m_pLed;
		mkii::event::Push::m_pStaticTimer = this->m_pTimer;

		mkii::event::Push::m_bStaticIsTracking = true;

		mkii::event::Push::m_pStaticButton->GetGPIO()->ClearInterruptFlag();
		mkii::event::Push::m_pStaticButton->GetGPIO()->EnableInterrupt();
		peripheral::GPIO::RegisterInterrupt(
		    mkii::event::Push::m_pStaticButton->GetGPIO(),
		    mkii::event::Push::HandlerCaller);
	}
}

void mkii::event::Push::HandlerCaller(void) {
	mkii::event::Push::GetPush()->Handler();
}

void mkii::event::Push::Handler(void) {
	mkii::event::Push::m_pStaticButton->GetGPIO()->ClearInterruptFlag();
	mkii::event::Push::m_pStaticLed->Toggle();
}

void mkii::event::Push::End(void) {
	if (mkii::event::Push::m_bStaticIsTracking) {
		peripheral::GPIO::UnregisterInterrupt(
		    mkii::event::Push::m_pStaticButton->GetGPIO());

		mkii::event::Push::m_pStaticButton = NULL;
		mkii::event::Push::m_pStaticLed = NULL;
		mkii::event::Push::m_pStaticTimer = NULL;

		mkii::event::Push::m_bStaticIsTracking = false;
	}
}

mkii::event::Push::Push(mkii::Button* i_pButton, mkii::Led* i_pLed,
                        mkii::Timer* i_pTimer) {
	this->SetButton(i_pButton);
	this->SetLed(i_pLed);
	this->SetTimer(i_pTimer);
}

void mkii::event::Push::SetButton(mkii::Button* i_pButton) {
	this->m_pButton = i_pButton;
}

void mkii::event::Push::SetLed(mkii::Led* i_pLed) { this->m_pLed = i_pLed; }

void mkii::event::Push::SetTimer(mkii::Timer* i_pTimer) {
	this->m_pTimer = i_pTimer;
}
