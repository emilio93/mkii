#include "peripheral/Adc14.hpp"

peripheral::Adc14::Adc14(peripheral::adc14::AnalogInputDevice i_eDevice) {
	this->m_bHasInterrupt = false;
	this->m_uf64InterruptMask = 0;
	this->m_u32SimpleMemoryMap = 0;
	this->m_u32AnalogMeasureDevice = i_eDevice;

	while (!ADC14_setPowerMode(peripheral::ADC14_POWER_MODE)) {
		;
	}

	bool l_bIsInit = false;
	switch (this->m_u32AnalogMeasureDevice) {
		/***************************************************************************
		 * Microphone
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::MICROPHONE:
			this->m_pGPIO[0] =
			    new GPIO(peripheral::adc14::DevicePort::PORT_MICROPHONE,
			             peripheral::adc14::DevicePin::PIN_MICROPHONE);

			ADC14_enableModule();

			do {
				l_bIsInit = ADC14_initModule(
				    peripheral::ADC14_CLOCK_SOURCE,
				    peripheral::adc14::DevicePredivider::PREDIV_MICROPHONE,
				    peripheral::adc14::DeviceDivider::DIV_MICROPHONE,
				    peripheral::ADC14_INTERNAL_CHANNEL_MASK);
			} while (!l_bIsInit);

			break;

		/***************************************************************************
		 * Joystick
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::JOYSTICK:
			// TODO

		/***************************************************************************
		 * Accelerometer
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::ACCELEREROMETER:
			this->m_pGPIO[0] =
			    new GPIO(peripheral::adc14::DevicePort::PORT_ACCELEREROMETER_X,
			             peripheral::adc14::DevicePin::PIN_ACCELEREROMETER_X);
			this->m_pGPIO[1] =
			    new GPIO(peripheral::adc14::DevicePort::PORT_ACCELEREROMETER_Y,
			             peripheral::adc14::DevicePin::PIN_ACCELEREROMETER_Y);
			this->m_pGPIO[2] =
			    new GPIO(peripheral::adc14::DevicePort::PORT_ACCELEREROMETER_Z,
			             peripheral::adc14::DevicePin::PIN_ACCELEREROMETER_Z);

			for (uint8_t i = 0; i < 3; i++) {
				this->m_pGPIO[i]->SetAsPeripheralModuleFunctionInput(
				    peripheral::gpio::ModuleFunction::TERTIARY);
			}

			ADC14_enableModule();

			do {
				l_bIsInit = ADC14_initModule(
				    peripheral::ADC14_CLOCK_SOURCE,
				    peripheral::adc14::DevicePredivider::PREDIV_ACCELEREROMETER,
				    peripheral::adc14::DeviceDivider::DIV_ACCELEREROMETER,
				    peripheral::ADC14_INTERNAL_CHANNEL_MASK);
			} while (!l_bIsInit);

			break;

		/***************************************************************************
		 * Temp Sensor
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::TEMP_SENSOR:
			// TODO

		/***************************************************************************
		 * Ambient Light
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::AMBIENT_LIGHT:
			// TODO

		/***************************************************************************
		 * None
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::NONE:
			// TODO
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

	while (!ADC14_disableModule()) {
		;
	}
}

void peripheral::Adc14::SetMemoryMap(uint32_t i_u32MemoryMap) {
	this->m_u32SimpleMemoryMap = i_u32MemoryMap;
}

void peripheral::Adc14::SetResolution(uint32_t i_u32Resolution) {
	ADC14_setResolution(i_u32Resolution);
}

void peripheral::Adc14::SetSimpleSampleMode(const bool i_bRepeat) {
	bool l_bIsSampleMode = false;
	do {
		l_bIsSampleMode =
		    ADC14_configureSingleSampleMode(this->m_u32SimpleMemoryMap, i_bRepeat);
	} while (!l_bIsSampleMode);
}

uint_fast16_t peripheral::Adc14::GetSimpleSampleModeResult() {
	return ADC14_getResult(this->m_u32SimpleMemoryMap);
}

bool peripheral::Adc14::ConfigureDevice() {
	if (!this->m_u32AnalogMeasureDevice ||
	    peripheral::adc14::AnalogInputDevice::NONE ==
	        this->m_u32AnalogMeasureDevice) {
		return false;
	}

	switch (this->m_u32AnalogMeasureDevice) {
		/***************************************************************************
		 * Microphone
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::MICROPHONE:
			const bool l_bDifferentialMode = false;
			const bool l_bRepeatSimpleSample = false;

			SetResolution(peripheral::ADC14_PRECISION);
			SetInterruptMask(ADC_INT10);
			SetMemoryMap(ADC_MEM10);

			this->m_pGPIO[0]->SetAsPeripheralModuleFunctionInput(
			    peripheral::ADC14_MODULE_FUNCTION);

			// configure memory map to adc save result in
			bool l_bConfigurationSuccess = false;

			do {
				this->WaitForAdcModule();
				l_bConfigurationSuccess = ADC14_configureConversionMemory(
				    this->m_u32SimpleMemoryMap, ADC_VREFPOS_AVCC_VREFNEG_VSS,
				    ADC_INPUT_A10, l_bDifferentialMode);
			} while (false == l_bConfigurationSuccess);

			SetSimpleSampleMode(l_bRepeatSimpleSample);
			SetSampleManualTimer();

			break;

		/***************************************************************************
		 * Joystick
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::JOYSTICK:
			// TODO

		/***************************************************************************
		 * Accelerometer
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::ACCELEREROMETER:

			/* Configuring ADC Memory (ADC_MEM0 - ADC_MEM2 (A11, A13, A14)  with no
			 * repeat) with internal 2.5v reference */
			ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM2, true);
			ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS,
			                                ADC_INPUT_A14,
			                                ADC_NONDIFFERENTIAL_INPUTS);

			ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS,
			                                ADC_INPUT_A13,
			                                ADC_NONDIFFERENTIAL_INPUTS);

			ADC14_configureConversionMemory(ADC_MEM2, ADC_VREFPOS_AVCC_VREFNEG_VSS,
			                                ADC_INPUT_A11,
			                                ADC_NONDIFFERENTIAL_INPUTS);

			this->SetResolution(peripheral::ADC14_PRECISION);

			this->SetSampleAutmaticTimer();
			this->EnableConversion();

		/***************************************************************************
		 * Temp Sensor
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::TEMP_SENSOR:
			// TODO

		/***************************************************************************
		 * Ambient Light
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::AMBIENT_LIGHT:
			// TODO

		/***************************************************************************
		 * None
		 **************************************************************************/
		case peripheral::adc14::AnalogInputDevice::NONE:
			// TODO
		default:
			return false;
	}
	return true;
}

void peripheral::Adc14::SetSampleManualTimer() {
	while (!ADC14_enableSampleTimer(ADC_MANUAL_ITERATION)) {
		;
	}
}

void peripheral::Adc14::SetSampleAutmaticTimer() {
	while (!ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION)) {
		;
	}
}

void peripheral::Adc14::TriggerSignalConversion() {
	ADC14_toggleConversionTrigger();
}

void peripheral::Adc14::EnableConversion() { ADC14_enableConversion(); }

uint_fast32_t peripheral::Adc14::GetResolution() {
	return ADC14_getResolution();
}

void peripheral::Adc14::WaitForAdcModule(void) {
	while (ADC14_isBusy()) {
		;
	}
}

uint_fast64_t peripheral::Adc14::GetInterruptMask() {
	return this->m_uf64InterruptMask;
}

void peripheral::Adc14::SetInterruptMask(uint_fast64_t i_uf64InterruptMask) {
	this->m_uf64InterruptMask = i_uf64InterruptMask;
}

void peripheral::Adc14::EnableInterrupt(void) {
	ADC14_enableInterrupt(this->m_uf64InterruptMask);
}

void peripheral::Adc14::RegisterInterrupt(
    void (*i_funcInterruptHandler)(void)) {
	ADC14_registerInterrupt(i_funcInterruptHandler);
}

void peripheral::Adc14::ClearInterruptFlag(void) {
	uint_fast64_t status = MAP_ADC14_getEnabledInterruptStatus();
	ADC14_clearInterruptFlag(status);
}

uint_fast64_t peripheral::Adc14::GetInterruptStatus() {
	return ADC14_getEnabledInterruptStatus();
}
