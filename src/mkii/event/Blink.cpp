#include "mkii/event/Blink.hpp"

bool mkii::event::Blink::m_bStaticIsBlinking = false;
uint32_t mkii::event::Blink::m_u32StaticBlinkCount = 0;
uint32_t mkii::event::Blink::m_u32StaticTimerCount = 0;
bool mkii::event::Blink::m_bStaticBlinkCountHasToggle = false;
mkii::Timer* mkii::event::Blink::m_pStaticBlinkTimer = NULL;
mkii::Led* mkii::event::Blink::m_pStaticBlinkLed = NULL;

mkii::event::Blink* mkii::event::Blink::m_pInstance = 0;

mkii::event::Blink* mkii::event::Blink::GetBlink() {
	if (mkii::event::Blink::m_pInstance == 0) {
		return NULL;
	}
	return mkii::event::Blink::m_pInstance;
}

mkii::event::Blink* mkii::event::Blink::GetBlink(uint32_t i_u32BlinkCount,
                                                 uint32_t i_u32TimerCount,
                                                 mkii::Timer* i_pBlinkTimer,
                                                 mkii::Led* i_pBlinkLed) {
	if (mkii::event::Blink::m_pInstance == 0) {
		mkii::event::Blink::m_pInstance = new mkii::event::Blink(
		    i_u32BlinkCount, i_u32TimerCount, i_pBlinkTimer, i_pBlinkLed);
	} else {
		mkii::event::Blink::m_pInstance->SetBlinkCount(i_u32BlinkCount);
		mkii::event::Blink::m_pInstance->SetTimerCount(i_u32TimerCount);
		mkii::event::Blink::m_pInstance->SetTimer(i_pBlinkTimer);
		mkii::event::Blink::m_pInstance->SetLed(i_pBlinkLed);
	}
	return mkii::event::Blink::m_pInstance;
}

void mkii::event::Blink::Init() {
	if (mkii::event::Blink::m_bStaticIsBlinking) {
		// Another blink is in course.
		// TODO: define behaviour.
		// Current behaviour is to not execute blink.
		return;
	}
	if (this->m_u32BlinkCount == 0 || this->m_u32TimerCount == 0) {
		return;
	}

	// Set blinking initial settings
	// These act as parameters for the handler
	mkii::event::Blink::m_bStaticIsBlinking = true;
	mkii::event::Blink::m_bStaticBlinkCountHasToggle = false;
	mkii::event::Blink::m_u32StaticBlinkCount = this->m_u32BlinkCount;
	mkii::event::Blink::m_u32StaticTimerCount = this->m_u32TimerCount;
	mkii::event::Blink::m_pStaticBlinkTimer = this->m_pBlinkTimer;
	mkii::event::Blink::m_pStaticBlinkLed = this->m_pBlinkLed;

	// First call as soon as posible
	// This call will manage following calls
	mkii::event::Blink::HandlerCaller();
}

bool mkii::event::Blink::IsBlinking(void) {
	return mkii::event::Blink::m_bStaticIsBlinking;
}

void mkii::event::Blink::HandlerCaller(void) {
	mkii::event::Blink::GetBlink()->Handler();
}

void mkii::event::Blink::End(void) {
	mkii::event::Blink::m_pStaticBlinkTimer->EndInterrupt();
	mkii::event::Blink::m_bStaticIsBlinking = false;
}

void mkii::event::Blink::Handler(void) {
	if (mkii::event::Blink::m_bStaticIsBlinking) {
		if (mkii::event::Blink::m_u32StaticBlinkCount <= 0 &&
		    !mkii::event::Blink::m_bStaticBlinkCountHasToggle) {
			// Stop condition: counter has reached 0 and both toggles for last blink
			// have happened.
			// No further interrupt is done and handler is unregistered. Blinking
			// state is turned off.
			mkii::event::Blink::GetBlink()->End();
			return;
		} else {
			// toggle led and clear interrupt flag
			mkii::event::Blink::m_pStaticBlinkLed->Toggle();
			mkii::event::Blink::m_pStaticBlinkTimer->EndInterrupt();

			// Regular operation: do both toggles for each count and reset timer and
			// interrupt.
			if (mkii::event::Blink::m_bStaticBlinkCountHasToggle) {
				mkii::event::Blink::m_u32StaticBlinkCount =
				    mkii::event::Blink::m_u32StaticBlinkCount - 1;
			}
			mkii::event::Blink::m_bStaticBlinkCountHasToggle =
			    !mkii::event::Blink::m_bStaticBlinkCountHasToggle;
			// Reset interrupt
			mkii::event::Blink::m_pStaticBlinkTimer->SetCounter(
			    mkii::event::Blink::m_u32StaticTimerCount);
			mkii::event::Blink::m_pStaticBlinkTimer->SetInterrupt(
			    mkii::event::Blink::HandlerCaller);
			return;
		}
	} else {
		// Shouldn't be blinking then
		return;
	}
}

mkii::event::Blink::Blink(uint32_t i_u32BlinkCount, uint32_t i_u32TimerCount,
                          mkii::Timer* i_pBlinkTimer, mkii::Led* i_pBlinkLed) {
	this->SetBlinkCount(i_u32BlinkCount);
	this->SetTimerCount(i_u32TimerCount);
	this->SetTimer(i_pBlinkTimer);
	this->SetLed(i_pBlinkLed);
}

void mkii::event::Blink::SetBlinkCount(uint32_t i_u32BlinkCount) {
	this->m_u32BlinkCount = i_u32BlinkCount;
}

void mkii::event::Blink::SetTimerCount(uint32_t i_u32TimerCount) {
	this->m_u32TimerCount = i_u32TimerCount;
}

void mkii::event::Blink::SetTimer(mkii::Timer* i_pTimer) {
	this->m_pBlinkTimer = i_pTimer;
}

void mkii::event::Blink::SetLed(mkii::Led* i_pLed) {
	this->m_pBlinkLed = i_pLed;
}
