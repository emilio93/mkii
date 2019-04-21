
#include <stdbool.h>
#include <stdint.h>

#include "driverlib.h"

#include <peripheral/Adc14.hpp>

#define LUNAV_LED_PIN GPIO_PIN0
#define LUNAV_LED_PORT GPIO_PORT_P1

peripheral::Adc14 converter(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_1,
                            ADC_DIVIDER_1, ADC_MAPINTCH0);

void initLed(void) {
	MAP_GPIO_setAsOutputPin((uint_fast8_t)LUNAV_LED_PORT,
	                        (uint_fast16_t)LUNAV_LED_PIN);
}
void setLedHigh(void) {
	MAP_GPIO_setOutputHighOnPin(LUNAV_LED_PORT, LUNAV_LED_PIN);
}
void setLedLow(void) {
	MAP_GPIO_setOutputLowOnPin(LUNAV_LED_PORT, LUNAV_LED_PIN);
}
void toggleLed(void) {
	MAP_GPIO_toggleOutputOnPin(LUNAV_LED_PORT, LUNAV_LED_PIN);
}

void ADC14_IRQHandler(void) {
	uint64_t l_u64InterruptStatus = 0;
	uint64_t l_u64Result = 0;

	l_u64InterruptStatus = converter.GetInterruptStatus();
	converter.ClearInterruptMask();

	if (l_u64InterruptStatus & converter.m_uf64InterruptMask) {
		l_u64Result = converter.GetSimpleSampleModeResult();

		if ((peripheral::MaxConvertionValue::SingleEndedMode) / 2 <= l_u64Result) {
			toggleLed();
		}
	}
	converter.JustTriggerConvertion();
}

void main(void) {
	MAP_WDT_A_holdTimer();
	initLed();
	setLedHigh();

	// set information
	converter.SetResolution(ADC_14BIT);
	converter.SetAnalogMeasureDevice(peripheral::AnalogInputDevice::MICROPHONE);

	// configure work mode and memory
	converter.ConfigureDeviceMemory(ADC_VREFPOS_AVCC_VREFNEG_VSS);
	converter.SetSimpleSampleMode(false);  // no repeat
	converter.SetSampleManualTimer();

	// set interrupt and convertion and start to convert
	converter.EnableAndTriggerConvertion();
	converter.EnableAndRegisterInterrupt(ADC14_IRQHandler);

	while (true) {
	};
}
