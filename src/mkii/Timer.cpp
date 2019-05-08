#include "mkii/Timer.hpp"

peripheral::Timer32* mkii::Timer::m_pStaticTimer32_0 = NULL;
peripheral::Timer32* mkii::Timer::m_pStaticTimer32_1 = NULL;

mkii::Timer* mkii::Timer::GetTimer(mkii::timer::TimerTypes i_eTimerType) {
	if (mkii::Timer::m_pStaticTimer32_0 == NULL) {
		mkii::Timer::m_pStaticTimer32_0 =
		    new peripheral::Timer32(TIMER32_0_BASE, TIMER32_PRESCALER_256,
		                            TIMER32_16BIT, TIMER32_PERIODIC_MODE);
	}
	return new Timer(mkii::Timer::m_pStaticTimer32_0);
}

void mkii::Timer::SetCounter(uint32_t i_u32TimerCount) {
	this->GetTimer32()->SetCounter(i_u32TimerCount);
}

void mkii::Timer::SetInterrupt(void (*i_funcHandler)(void)) {
	this->GetTimer32()->RegisterInterrupt(true, i_funcHandler);
	this->GetTimer32()->EnableInterrupt(true);
}

void mkii::Timer::EndInterrupt() {
	this->GetTimer32()->ClearInterruptFlag();
	this->GetTimer32()->EnableInterrupt(false);
	this->GetTimer32()->RegisterInterrupt(false);
}

mkii::Timer::Timer(peripheral::Timer32* i_pTimer32) {
	this->SetTimer32(i_pTimer32);
}

void mkii::Timer::SetTimer32(peripheral::Timer32* i_pTimer32) {
	this->m_pTimer32 = i_pTimer32;
}

peripheral::Timer32* mkii::Timer::GetTimer32() { return this->m_pTimer32; }