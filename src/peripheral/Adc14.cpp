#include "peripheral/Adc14.hpp"

peripheral::Adc14::Adc14(peripheral::adc::AnalogInputDevice i_eDevice)
    : m_bHasInterrupt(false),
      m_uf64InterruptMask(0),
      m_u32SimpleMemoryMap(0),
      m_u32AnalogMeasureDevice(i_eDevice) {
	ADC14_enableModule();

	bool l_bAdcPowered = false;
	do {
		waitForAdcModule();
		l_bAdcPowered = ADC14_setPowerMode(ADC_UNRESTRICTED_POWER_MODE);
	} while (false == l_bAdcPowered);

	bool l_bAdcStarted = false;

	switch (this->m_u32AnalogMeasureDevice) {
		case peripheral::adc::AnalogInputDevice::NONE:
			break;
		case peripheral::adc::AnalogInputDevice::JOYSTICK:
			break;
		case peripheral::adc::AnalogInputDevice::ACCELEREROMETER:
			break;
		case peripheral::adc::AnalogInputDevice::MICROPHONE:
			do {
				waitForAdcModule();
				l_bAdcStarted = ADC14_initModule(
				    peripheral::adc::g_stMicrophoneAdcInitConfiguration.u32ClockSource,
				    peripheral::adc::g_stMicrophoneAdcInitConfiguration
				        .u32ClockPreDivider,
				    peripheral::adc::g_stMicrophoneAdcInitConfiguration.u32ClockDivider,
				    peripheral::adc::g_stMicrophoneAdcInitConfiguration
				        .u32InternalChannelMask);
			} while (false == l_bAdcStarted);
			break;
		case peripheral::adc::AnalogInputDevice::TEMP_SENSOR:
			break;
		case peripheral::adc::AnalogInputDevice::AMBIENT_LIGHT:
			break;
		default:
			break;
	}
}

peripheral::Adc14::~Adc14() {
	ADC14_disableConversion();
	ADC14_disableSampleTimer();

	if (this->m_bHasInterrupt) {
		ADC14_disableInterrupt(this->m_uf64InterruptMask);
		ADC14_unregisterInterrupt();
	}

	bool l_bAdcDisabled = false;
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

bool peripheral::Adc14::ConfigureDevice() {
	if (!this->m_u32AnalogMeasureDevice ||
	    peripheral::adc::AnalogInputDevice::NONE ==
	        this->m_u32AnalogMeasureDevice) {
		return false;
	}

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
			// TODO: [brjmm] adc should take measurement each ~1s

			// microphone is a single input
			const bool l_bDifferentialMode = false;
			const bool l_bRepeatSimpleSample = false;

			SetResolution(ADC_14BIT);
			SetInterruptMask(ADC_INT10);
			SetMemoryMap(ADC_MEM10);

			MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
			    GPIO_PORT_P4, GPIO_PIN3, GPIO_TERTIARY_MODULE_FUNCTION);

			// configure memory map to adc save result in
			bool l_bConfigurationSuccess = false;

			do {
				waitForAdcModule();
				l_bConfigurationSuccess = ADC14_configureConversionMemory(
				    this->m_u32SimpleMemoryMap, ADC_VREFPOS_AVCC_VREFNEG_VSS,
				    ADC_INPUT_A10, l_bDifferentialMode);
			} while (false == l_bConfigurationSuccess);

			SetSimpleSampleMode(l_bRepeatSimpleSample);
			SetSampleManualTimer();

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
	TriggerSignalConvertion();
}

uint_fast32_t peripheral::Adc14::GetResolution() {
	return ADC14_getResolution();
}

void peripheral::Adc14::waitForAdcModule(void) {
	static bool l_bAdcIsBusyNow = true;
	while (l_bAdcIsBusyNow == ADC14_isBusy()) {
	}
}

uint_fast64_t peripheral::Adc14::GetInterruptMask() {
	return this->m_uf64InterruptMask;
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
