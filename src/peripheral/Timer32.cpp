#include <peripheral/Timer32.hpp>

peripheral::Timer32::Timer32(mkii_timer32 i_mkiiTimer, uint32_t i_u32PreScaler,
                             uint32_t i_u32Resolution,
                             uint32_t i_u32OperationMode)
    : m_mkiiTimer(i_mkiiTimer), m_bHasInterrupt(false) {
	Timer32_initModule(this->m_mkiiTimer, i_u32PreScaler, i_u32Resolution,
	                   i_u32OperationMode);
	Timer32_startTimer(this->m_mkiiTimer,
	                   false);  // TODO: [brjmm] considers enable the one shot
}

peripheral::Timer32::~Timer32() {
	Timer32_haltTimer(this->m_mkiiTimer);
	if (this->m_bHasInterrupt) {
		this->RegisterInterrupt(false);  // unregister the interrupt
	}
}

void peripheral::Timer32::SetCounter(const uint32_t i_u32Count) {
	Timer32_haltTimer(this->m_mkiiTimer);
	Timer32_setCount(this->m_mkiiTimer, i_u32Count);
	Timer32_startTimer(this->m_mkiiTimer, false);
}

uint32_t peripheral::Timer32::GetCurrentValue(void) {
	return Timer32_getValue(this->m_mkiiTimer);
}

void peripheral::Timer32::EnableInterrupt(const bool i_bEnable) {
	if (i_bEnable) {
		Timer32_enableInterrupt(this->m_mkiiTimer);
	} else {
		Timer32_disableInterrupt(this->m_mkiiTimer);
	}
}

void peripheral::Timer32::ClearInterruptFlag(void) {
	Timer32_clearInterruptFlag(this->m_mkiiTimer);
}

void peripheral::Timer32::RegisterInterrupt(
    const bool i_bRegister, void (*i_funcInterruptHandler)(void)) {
	uint32_t l_u32TimerInterrupt = 0;

	switch (this->m_mkiiTimer) {
		case (mkii_timer32)TIMER32_0_BASE:
			l_u32TimerInterrupt = TIMER32_0_INTERRUPT;
			break;
		case (mkii_timer32)TIMER32_1_BASE:
			l_u32TimerInterrupt = TIMER32_1_INTERRUPT;
			break;
	}

	if (i_bRegister) {
		Timer32_registerInterrupt(l_u32TimerInterrupt, i_funcInterruptHandler);
		this->m_bHasInterrupt = true;
	} else {
		Timer32_unregisterInterrupt(l_u32TimerInterrupt);
	}
}
