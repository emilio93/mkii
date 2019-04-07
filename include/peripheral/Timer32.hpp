
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
		void SetCounter(const uint32_t i_u32Count);
		uint32_t GetCurrentValue();

		/**
		 * Enables the timer interruption
		 * @param i_bEnable Defines whether interrupt is enabled(true) or disabled(false).
		 */
		void EnableInterrupt(const bool i_bEnable);

		/**
		 * Register the timer interruption
		 * @param i_bRegister Defines whether interrupt is register(true) or unregister(false).
		 * @param i_funcInterruptHandler Function of the interrupt vector to handler the interruption
		 */
		void RegisterInterrupt(const bool i_bRegister, void (*i_funcInterruptHandler)(void) = 0);
		void ClearInterruptionFlag(void);
	private:
		mkii_timer32 m_mkiiTimer;
		bool m_bHasInterrupt;
};

#endif /* MKII_TIM32_H */
