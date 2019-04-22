
#ifndef MKII_PERIPHERAL_ADC14_H
#define MKII_PERIPHERAL_ADC14_H

#include "driverlib.h"

namespace peripheral {

namespace adc {

enum MaxConvertionValue { SingleEndedMode = 16384, DifferentialMode = 8192 };

enum AnalogInputDevice {
	NONE,
	JOYSTICK,
	ACCELEREROMETER,
	MICROPHONE,
	TEMP_SENSOR,
	AMBIENT_LIGHT
};

}  // namespace adc

class Adc14 {
 public:
	uint_fast64_t m_uf64InterruptMask;

	Adc14(uint32_t i_u32ClockSource, uint32_t i_u32ClockPredivider,
	      uint32_t i_u32ClockDivider, uint32_t i_u32InternalChannelMask);
	~Adc14();

	/**
	 * Wait until the adc is not busy
	 */
	void waitForAdcModule(void);

	/**
	 * Set the adc resolution. Available options:
	 * 	 ADC_8BIT, ADC_10BIT, ADC_12BIT, ADC_14BIT
	 *
	 * @param i_u32Resolution The adc convertion resolution.
	 */
	void SetResolution(const uint32_t i_u32Resolution);

	/**
	 * Configure the adc to use a simple memory location for the
	 * convertion/sample. The memory used is m_u32SimpleMemoryMap
	 * member
	 *
	 * @param i_bRepeat Indicates if repeat the convertion/sample
	 *	after the first sample/convertion
	 */
	void SetSimpleSampleMode(const bool i_bRepeat);

	/**
	 * Get the sample result from the adc when is working in simple
	 * sample mode.
	 */
	uint_fast16_t GetSimpleSampleModeResult(void);

	/**
	 * Indicates what analog device will be measured in the current
	 * adc instance. Every adc instance should be set an
	 * device to know how work.
	 *
	 * @param i_eAnalogMeasure Indicates what supported analog input
	 * device will be measure.
	 */
	void SetAnalogMeasureDevice(
	    const peripheral::adc::AnalogInputDevice i_eAnalogMeasure);

	// Return true if the memory configuration is success
	bool ConfigureDevice(const uint32_t i_u32VoltageRef);

	/**
	 * Set the convertion timer in manual mode. The user has to trigger
	 * the convertion signal after aeach converion/sample using
	 * EnableAndTriggerConvertion or TriggerSignalConvertion.
	 */
	void SetSampleManualTimer(void);

	/**
	 * Set the convertion timer in automatic mode. After every the adc
	 * will automatically continue with the next sample
	 */
	void SetSampleAutmaticTimer(void);

	/**
	 * Trigger the convertion signal and start the next covertion/sample.
	 */
	void TriggerSignalConvertion(void);

	/**
	 * Enable convertion and start with the first convertion/sample
	 */
	void EnableAndTriggerConvertion(void);

	/**
	 * Get the adc convertion resolution
	 *
	 * @return Adc resolution
	 */
	uint_fast32_t GetResolution(void);

	/**
	 * Enable convertion and start with the first convertion/sample
	 *
	 * @param i_funcInterruptHandler Function to handler the interruption
	 */
	void EnableAndRegisterInterrupt(void (*i_funcInterruptHandler)(void) = 0);

	/**
	 * Clear the interrupt flag using m_uf64InterruptMask as mask
	 */
	void ClearInterruptFlag(void);

	/**
	 * Get the interrupt status.
	 * This returned value should be compare with m_uf64InterruptMask
	 * to know if the result is valid for the desired interrupt
	 *
	 * @return Interrupt status
	 */
	uint_fast64_t GetInterruptStatus(void);

 private:
	bool m_bHasInterrupt;
	uint32_t m_u32SimpleMemoryMap;
	peripheral::adc::AnalogInputDevice m_u32AnalogMeasureDevice;

	/**
	 * Set the memory map.
	 * Available values are: ADC_MEM0 to ADC_MEM31.
	 *
	 * @param i_u32MemoryMap The map to save the sample
	 */
	void SetMemoryMap(const uint32_t i_u32MemoryMap);

	/**
	 * Set the interrupt mask.
	 * Available values are: ADC_INT0 to ADC_INT31, ADC_IN_INT, ADC_LO_INT,
	 * ADC_HI_INT, ADC_OV_INT, ADC_TOV_INT and ADC_RDY_INT
	 *
	 * @param i_uf64InterruptMask The interrupt mask
	 */
	void SetInterruptMask(const uint_fast64_t i_uf64InterruptMask);
};

}  // namespace peripheral

#endif /* MKII_PERIPHERAL_ADC14_H */
