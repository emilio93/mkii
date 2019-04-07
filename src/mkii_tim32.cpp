
#include "driverlib.h"
#include <stdint.h>
#include "mkii_tim32.hpp"

Timer32::Timer32(mkii_timer32 i_mkiiTimer, uint32_t i_u32PreScaler,
		uint32_t i_u32Resolution, uint32_t i_u32OperationMode)
	: m_mkiiTimer(i_mkiiTimer), m_bHasInterruption(false)
{
	Timer32_initModule(m_mkiiTimer, i_u32PreScaler, i_u32Resolution, i_u32OperationMode);
	Timer32_startTimer(m_mkiiTimer, false);
}
Timer32::~Timer32()
{
	Timer32_haltTimer(m_mkiiTimer);
	if(m_bHasInterruption)
	{
		RegisterInterruption(false); // unregister the interruption
	}
}
void Timer32::SetCounter(const uint32_t i_mkiiCount)
{
	Timer32_setCount(m_mkiiTimer, i_mkiiCount);
	Timer32_setCountInBackground(m_mkiiTimer, i_mkiiCount);
}
void Timer32::GetCurrentValue(uint32_t* o_u32Value)
{
	*o_u32Value = Timer32_getValue(m_mkiiTimer);
}
void Timer32::EnableInterruption(const bool i_bEnable)
{
	if(i_bEnable)
	{
		Timer32_enableInterrupt(m_mkiiTimer);
	}
	else
	{
		Timer32_disableInterrupt(m_mkiiTimer);
	}
}
void Timer32::ClearInterruptionFlag(void)
{
	Timer32_clearInterruptFlag(m_mkiiTimer);
}
void Timer32::RegisterInterruption(const bool i_bRegister, void (*i_funcInterruptHandler)(void))
{
	if(TIMER32_0_BASE == m_mkiiTimer)
	{
		if (i_bRegister)
		{
			Timer32_registerInterrupt(TIMER32_0_INTERRUPT, i_funcInterruptHandler);
			m_bHasInterruption = true;
		}
		else
		{
			Timer32_unregisterInterrupt(TIMER32_0_INTERRUPT);
		}
	}
	if(TIMER32_1_BASE == m_mkiiTimer)
	{
		if (i_bRegister)
		{
			Timer32_registerInterrupt(TIMER32_1_INTERRUPT, i_funcInterruptHandler);
			m_bHasInterruption = true;
		}
		else
		{
			Timer32_unregisterInterrupt(TIMER32_1_INTERRUPT);
		}
	}
}
