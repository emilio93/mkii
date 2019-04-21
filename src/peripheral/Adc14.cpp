
#include <stdbool.h>

#include <peripheral/Adc14.hpp>

void peripheral::Adc14::Adc14(uint32_t i_u32ClockSource, uint32_t i_u32ClockPredivider,
						uint32_t i_u32ClockDivider, uint32_t i_u32InternalChannelMask)
	: m_bHasInterrupt(false), m_uf64InterruptMask(0) {
	bool l_bAdcStarted = false;
	bool l_bAdcPowered = false;

	ADC14_enableModule();

	do {
		waitForAdcModule();
		l_bAdcPowered = ADC14_setPowerMode(ADC_UNRESTRICTED_POWER_MODE);
	} while (false == l_bAdcPowered);

	do {
		waitForAdcModule();
		l_bAdcStarted = ADC14_initModule(i_u32ClockSource, i_u32ClockPredivider,
										i_u32ClockDivider, i_u32InternalChannelMask);
	} while (false == l_bAdcStarted);
}

void peripheral::Adc14::~Adc14() {
	bool l_bAdcDisabled = false;

	if (this->m_bHasInterrupt) {
		ADC14_disableInterrupt(this->m_uf64InterruptMask);
		ADC14_unregisterInterrupt();
	}

	do {
		waitForAdcModule();
		l_bAdcDisabled = ADC14_disableModule();
	} while (false == l_bAdcDisabled);
}

void peripheral::Adc14::SetResolution(uint32_t i_u32Resolution) {
	ADC14_setResolution(i_u32Resolution);
}

uint_fast32_t peripheral::Adc14::GetResolution() {
	return ADC14_getResolution();
}

void peripheral::Adc14::waitForAdcModule(void) {
	static bool l_bAdcIsBusyNow = true;
	while(l_bAdcIsBusyNow == ADC14_isBusy()) {
	}
}

void peripheral::Adc14::SetInterruptMask(uint_fast64_t i_uf64InterruptMask) {
	this->m_uf64InterruptMask = i_uf64InterruptMask;
}

void peripheral::Adc14::EnableAndRegisterInterrupt(void(*i_funcInterruptHandler)(void)) {
	ADC14_enableInterrupt(this->m_uf64InterruptMask);
	ADC14_registerInterrupt(i_funcInterruptHandler);
}

void peripheral::Adc14::ClearInterruptMask(void) {
	ADC14_clearInterruptFlag(this->m_uf64InterruptMask);
}
