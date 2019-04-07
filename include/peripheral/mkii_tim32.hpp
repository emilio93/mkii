
#ifndef MKII_TIM32_H
#define MKII_TIM32_H

#include <stdint.h>
#include <stdbool.h>

#include "driverlib.h"

typedef uint32_t mkii_timer32;


class Timer32
{
	public:
		Timer32(mkii_timer32 i_mkiiTimer, uint32_t i_u32PreScaler,
				uint32_t i_u32Resolution, uint32_t i_u32OperationMode);
		~Timer32();
		void SetCounter(const uint32_t i_mkiiCount);
		void GetCurrentValue(uint32_t* o_u32Value);

		//*****************************************************************************
		//	EnableInterruption
		//         - true: enable interruption
		//         - false: disable interruption
		//*****************************************************************************
		void EnableInterruption(const bool i_bEnable);

		//*****************************************************************************
		//	EnableInterruption
		//         - i_bRegister true: register interruption
		//         - i_bRegister false: unregister interruption
		//		   - i_fInterruptHandler: required if i_bRegister is true
		//*****************************************************************************
		void RegisterInterruption(const bool i_bRegister, void (*i_funcInterruptHandler)(void) = 0);
		void ClearInterruptionFlag(void);
	private:
		mkii_timer32 m_mkiiTimer;
		bool m_bHasInterruption;
};

#endif /* MKII_TIM32_H */
