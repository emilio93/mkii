
#include <stdbool.h>
#include <stdint.h>

#include "driverlib.h"

#include <peripheral/Adc14.hpp>

peripheral::Adc14 converter(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_1,
                            ADC_DIVIDER_1, ADC_MAPINTCH0);

void ADC14_IRQHandler(void)
{
    uint64_t l_u64InterruptStatus = 0;
    uint64_t l_u64Result = 0;

    l_u64InterruptStatus = converter.GetInterruptStatus();
    converter.ClearInterruptMask();

    if(l_u64InterruptStatus & converter.m_uf64InterruptMask)
    {
        l_u64Result = converter.GetSimpleSampleModeResult();
    }
}


void main(void) {
	MAP_WDT_A_holdTimer();

	// set information
	converter.SetResolution(ADC_14BIT);
	converter.SetMemoryMap(ADC_MEM0);
	converter.SetAnalogMeasureDevice(peripheral::AnalogInputDevice::MICROPHONE);

	// configure work mode and memory
	converter.SetSimpleSampleMode(false); // no repeat
	converter.ConfigureDeviceMemory(ADC_VREFPOS_AVCC_VREFNEG_VSS, false); // no differential inputs

	// set interrupt and convertion and start to convert
	converter.EnableAndRegisterInterrupt(ADC14_IRQHandler);
	converter.EnableAndTriggerConvertion();
	while (true) {
	};
}
