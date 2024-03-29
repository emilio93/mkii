#include "mkii/event/LedTimeout.hpp"

mkii::event::LedTimeout* mkii::event::LedTimeout::m_pInstance = 0;

mkii::Led* mkii::event::LedTimeout::m_pStaticLed = NULL;
mkii::Timer* mkii::event::LedTimeout::m_pStaticTimer = NULL;

uint32_t mkii::event::LedTimeout::m_u32StaticTimerCount = 0;
bool mkii::event::LedTimeout::m_bStaticIsTimeoutOn = false;
bool mkii::event::LedTimeout::m_bStaticIsInterruptOn = false;

/******************************************************************************
 * GET LED TIMEOUT                                                            *
 ******************************************************************************/
mkii::event::LedTimeout* mkii::event::LedTimeout::GetLedTimeout() {
	if (mkii::event::LedTimeout::m_pInstance == 0) {
		return NULL;
	}
	return mkii::event::LedTimeout::m_pInstance;
}

/******************************************************************************
 * GET LED TIMEOUT                                                            *
 ******************************************************************************/
mkii::event::LedTimeout* mkii::event::LedTimeout::GetLedTimeout(
    mkii::Led* i_pLed, mkii::Timer* i_pTimer, uint32_t i_u32TimerCount) {
	if (mkii::event::LedTimeout::m_pInstance == 0) {
		mkii::event::LedTimeout::m_pInstance =
		    new mkii::event::LedTimeout(i_pLed, i_pTimer, i_u32TimerCount);
	} else {
		mkii::event::LedTimeout::m_pInstance->SetTimerCount(i_u32TimerCount);
		mkii::event::LedTimeout::m_pInstance->SetTimer(i_pTimer);
		mkii::event::LedTimeout::m_pInstance->SetLed(i_pLed);
	}
	return mkii::event::LedTimeout::m_pInstance;
}

/******************************************************************************
 * INIT                                                                       *
 ******************************************************************************/
void mkii::event::LedTimeout::Init(void) {
	// cases to stop
	if (mkii::event::LedTimeout::m_bStaticIsTimeoutOn) {
		return;
	}
	if (this->GetTimerCount() == 0) {
		return;
	}
	if (!this->GetLed()->GetState()) {
		return;
	}

	// set static variables to object values
	mkii::event::LedTimeout::m_pStaticLed = this->GetLed();
	mkii::event::LedTimeout::m_pStaticTimer = this->GetTimer();
	mkii::event::LedTimeout::m_u32StaticTimerCount = this->GetTimerCount();

	// lock event as it is ongoing from now on
	mkii::event::LedTimeout::m_bStaticIsTimeoutOn = true;
	mkii::event::LedTimeout::m_bStaticIsInterruptOn = false;

	mkii::event::LedTimeout::HandlerCaller();
}

/******************************************************************************
 * HANDLER CALLER                                                             *
 ******************************************************************************/
void mkii::event::LedTimeout::HandlerCaller(void) {
	if (mkii::event::LedTimeout::GetLedTimeout() == NULL ||
	    !mkii::event::LedTimeout::m_bStaticIsTimeoutOn) {
		return;
	}
	mkii::event::LedTimeout::GetLedTimeout()->Handler();
}

/******************************************************************************
 * HANDLER                                                                    *
 ******************************************************************************/
void mkii::event::LedTimeout::Handler(void) {
	if (mkii::event::LedTimeout::m_bStaticIsTimeoutOn) {
		if (!mkii::event::LedTimeout::m_bStaticIsInterruptOn) {
			// set timer interrupt
			mkii::event::LedTimeout::m_pStaticTimer->SetCounter(
			    this->GetTimerCount());
			mkii::event::LedTimeout::m_pStaticTimer->SetInterrupt(
			    mkii::event::LedTimeout::HandlerCaller);
			mkii::event::LedTimeout::m_bStaticIsInterruptOn = true;
		} else {
			mkii::event::LedTimeout::GetLedTimeout()->End();
		}
	}
}

/******************************************************************************
 * END                                                                        *
 ******************************************************************************/
void mkii::event::LedTimeout::End(void) {
	mkii::event::LedTimeout::m_pStaticTimer->EndInterrupt();
	mkii::event::LedTimeout::m_pStaticLed->SetState(false);
	mkii::event::LedTimeout::m_bStaticIsTimeoutOn = false;
}

/******************************************************************************
 * IS TIMEOUT ON                                                              *
 ******************************************************************************/
bool mkii::event::LedTimeout::IsTimeoutOn() {
	return mkii::event::LedTimeout::m_bStaticIsTimeoutOn;
}

/******************************************************************************
 * SETTERS                                                                    *
 ******************************************************************************/
void mkii::event::LedTimeout::SetLed(mkii::Led* i_pLed) {
	this->m_pLed = i_pLed;
}

void mkii::event::LedTimeout::SetTimer(mkii::Timer* i_pTimer) {
	this->m_pTimer = i_pTimer;
}

void mkii::event::LedTimeout::SetTimerCount(uint32_t i_u32TimerCount) {
	this->m_u32TimerCount = i_u32TimerCount;
}

/******************************************************************************
 * GETTERS                                                                    *
 ******************************************************************************/
mkii::Led* mkii::event::LedTimeout::GetLed() { return this->m_pLed; }

mkii::Timer* mkii::event::LedTimeout::GetTimer() { return this->m_pTimer; }

uint32_t mkii::event::LedTimeout::GetTimerCount() {
	return this->m_u32TimerCount;
}

/******************************************************************************
 * CONSTRUCTOR                                                                *
 ******************************************************************************/
mkii::event::LedTimeout::LedTimeout(mkii::Led* i_pLed, mkii::Timer* i_pTimer,
                                    uint32_t i_u32TimerCount) {
	this->SetLed(i_pLed);
	this->SetTimer(i_pTimer);
	this->SetTimerCount(i_u32TimerCount);
}
