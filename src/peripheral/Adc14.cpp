
#include <stdbool.h>

#include "driverlib.h"

#include <peripheral/Adc14.hpp>

peripheral::Adc14::Adc14(uint32_t i_u32ClockSource,
                         uint32_t i_u32ClockPredivider,
                         uint32_t i_u32ClockDivider,
                         uint32_t i_u32InternalChannelMask)
    : m_bHasInterrupt(false),
      m_uf64InterruptMask(0),
      m_u32SimpleMemoryMap(0),
      m_u32AnalogMeasureDevice(peripheral::adc::AnalogInputDevice::NONE) {
	bool l_bAdcStarted = false;
	bool l_bAdcPowered = false;

	ADC14_enableModule();

	do {
		waitForAdcModule();
		l_bAdcPowered = ADC14_setPowerMode(ADC_UNRESTRICTED_POWER_MODE);
	} while (false == l_bAdcPowered);

	do {
		waitForAdcModule();
		l_bAdcStarted =
		    ADC14_initModule(i_u32ClockSource, i_u32ClockPredivider,
		                     i_u32ClockDivider, i_u32InternalChannelMask);
	} while (false == l_bAdcStarted);
}

peripheral::Adc14::~Adc14() {
	bool l_bAdcDisabled = false;

	ADC14_disableConversion();
	ADC14_disableSampleTimer();

	if (this->m_bHasInterrupt) {
		ADC14_disableInterrupt(this->m_uf64InterruptMask);
		ADC14_unregisterInterrupt();
	}

	do {
		waitForAdcModule();
		l_bAdcDisabled = ADC14_disableModule();
	} while (false == l_bAdcDisabled);
}

void peripheral::Adc14::SetMemoryMap(uint32_t i_u32MemoryMap) {
	this->m_u32SimpleMemoryMap = i_u32MemoryMap;
}

void peripheral::Adc14::SetResolution(uint32_t i_u32Resolution) {
	ADC14_setResolution(i_u32Resolution);
}

void peripheral::Adc14::SetAnalogMeasureDevice(
    peripheral::adc::AnalogInputDevice i_eAnalogMeasure) {
	this->m_u32AnalogMeasureDevice = i_eAnalogMeasure;
}

void peripheral::Adc14::SetSimpleSampleMode(const bool i_bRepeat) {
	bool l_bSampleModeSuccess = false;

	do {
		waitForAdcModule();
		l_bSampleModeSuccess =
		    ADC14_configureSingleSampleMode(this->m_u32SimpleMemoryMap, i_bRepeat);
	} while (false == l_bSampleModeSuccess);
}

uint_fast16_t peripheral::Adc14::GetSimpleSampleModeResult() {
	return ADC14_getResult(this->m_u32SimpleMemoryMap);
}

bool peripheral::Adc14::ConfigureDevice(const uint32_t i_u32VoltageRef) {
	if (!this->m_u32AnalogMeasureDevice ||
	    peripheral::adc::AnalogInputDevice::NONE ==
	        this->m_u32AnalogMeasureDevice) {
		return false;
	}

	uint32_t l_u32AdcInput = 0;
	bool l_bDifferentialMode = false;

	switch (this->m_u32AnalogMeasureDevice) {
		case peripheral::adc::AnalogInputDevice::NONE:
			return false;
		case peripheral::adc::AnalogInputDevice::JOYSTICK:
			// TODO: [brjmm] define an action
			// TODO: [brjmm] Define if this value will handler
			// the VERT_Y and HOR_X JOYSTICK components
			return false;
		case peripheral::adc::AnalogInputDevice::ACCELEREROMETER:
			// TODO: [brjmm] define an action
			// TODO: [brjmm] Define if this value will handler
			// the X, Y and Z ACCELEROMETER components
			return false;
		case peripheral::adc::AnalogInputDevice::MICROPHONE:
			l_u32AdcInput = ADC_INPUT_A10;
			l_bDifferentialMode = false;  // microphone is a single input

			SetInterruptMask(ADC_INT10);
			SetMemoryMap(ADC_MEM10);

			// setting gpio as analog input
			MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
			    GPIO_PORT_P4, GPIO_PIN3, GPIO_TERTIARY_MODULE_FUNCTION);
			break;
		case peripheral::adc::AnalogInputDevice::TEMP_SENSOR:
			// TODO: [brjmm] define an action
			return false;
		case peripheral::adc::AnalogInputDevice::AMBIENT_LIGHT:
			// TODO: [brjmm] define an action
			return false;
		default:
			return false;
	}

	bool l_bConfigurationSuccess = false;

	do {
		waitForAdcModule();
		l_bConfigurationSuccess = ADC14_configureConversionMemory(
		    this->m_u32SimpleMemoryMap, i_u32VoltageRef, l_u32AdcInput,
		    l_bDifferentialMode);
	} while (false == l_bConfigurationSuccess);

	return true;
}

void peripheral::Adc14::SetSampleManualTimer() {
	bool l_bTimerSetted = false;

	do {
		waitForAdcModule();
		l_bTimerSetted = ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);
	} while (false == l_bTimerSetted);
}

void peripheral::Adc14::SetSampleAutmaticTimer() {
	bool l_bTimerSetted = false;

	do {
		waitForAdcModule();
		l_bTimerSetted = ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
	} while (false == l_bTimerSetted);
}

void peripheral::Adc14::TriggerSignalConvertion() {
	ADC14_toggleConversionTrigger();
}

void peripheral::Adc14::EnableAndTriggerConvertion() {
	ADC14_enableConversion();
	ADC14_toggleConversionTrigger();
}

uint_fast32_t peripheral::Adc14::GetResolution() {
	return ADC14_getResolution();
}

void peripheral::Adc14::waitForAdcModule(void) {
	static bool l_bAdcIsBusyNow = true;
	while (l_bAdcIsBusyNow == ADC14_isBusy()) {
	}
}

void peripheral::Adc14::SetInterruptMask(uint_fast64_t i_uf64InterruptMask) {
	this->m_uf64InterruptMask = i_uf64InterruptMask;
}

void peripheral::Adc14::EnableAndRegisterInterrupt(
    void (*i_funcInterruptHandler)(void)) {
	ADC14_enableInterrupt(this->m_uf64InterruptMask);
	ADC14_registerInterrupt(i_funcInterruptHandler);
}

void peripheral::Adc14::ClearInterruptFlag(void) {
	ADC14_clearInterruptFlag(this->m_uf64InterruptMask);
}

uint_fast64_t peripheral::Adc14::GetInterruptStatus() {
	return ADC14_getEnabledInterruptStatus();
}
