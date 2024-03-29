
#ifndef MKII_PERIPHERAL_ADC14_H
#define MKII_PERIPHERAL_ADC14_H

#include <cstdbool>

#include "driverlib.h"

#include "peripheral/GPIO.hpp"

namespace peripheral {

namespace adc14 {

const uint8_t MAX_GPIO_PINS = 3;

enum MaxConversionValue {
	SINGLE_ENDED_MODE = 0X4000,
	DIFFERENTIAL_MODE = 0X2000
};

enum Precision {
	P8BIT = (0x00000000),   // 8 bit (9 clock cycle conversion time)
	P10BIT = (0x00000010),  // 10 bit (11 clock cycle conversion time)
	P12BIT = (0x00000020),  // 12 bit (14 clock cycle conversion time)
	P14BIT = (0x00000030)   // 14 bit (16 clock cycle conversion time)
};

enum PowerMode { ULTRA_LOW = (0x00000002), UNRESTRICTED = (0x00000000) };

enum AnalogInputDevice {
	NONE,
	JOYSTICK,
	ACCELEREROMETER,
	MICROPHONE,
	TEMP_SENSOR,
	AMBIENT_LIGHT
};

enum DevicePort {
	PORT_NONE = peripheral::gpio::Port::PORT1,
	PORT_JOYSTICK = peripheral::gpio::Port::PORT1,
	PORT_ACCELEREROMETER_X = peripheral::gpio::Port::PORT6,
	PORT_ACCELEREROMETER_Y = peripheral::gpio::Port::PORT4,
	PORT_ACCELEREROMETER_Z = peripheral::gpio::Port::PORT4,
	PORT_MICROPHONE = peripheral::gpio::Port::PORT4,
	PORT_TEMP_SENSOR = peripheral::gpio::Port::PORT1,
	PORT_AMBIENT_LIGHT = peripheral::gpio::Port::PORT1
};

enum DevicePin {
	PIN_NONE = peripheral::gpio::Pin::PIN0,
	PIN_JOYSTICK = peripheral::gpio::Pin::PIN0,
	PIN_ACCELEREROMETER_X = peripheral::gpio::Pin::PIN1,
	PIN_ACCELEREROMETER_Y = peripheral::gpio::Pin::PIN0,
	PIN_ACCELEREROMETER_Z = peripheral::gpio::Pin::PIN2,
	PIN_MICROPHONE = peripheral::gpio::Pin::PIN3,
	PIN_TEMP_SENSOR = peripheral::gpio::Pin::PIN0,
	PIN_AMBIENT_LIGHT = peripheral::gpio::Pin::PIN0
};

enum DeviceDivider {
	DIV_NONE = ADC_DIVIDER_1,
	DIV_JOYSTICK = ADC_DIVIDER_1,
	DIV_ACCELEREROMETER = ADC_DIVIDER_8,
	DIV_MICROPHONE = ADC_DIVIDER_1,
	DIV_TEMP_SENSOR = ADC_DIVIDER_1,
	DIV_AMBIENT_LIGHT = ADC_DIVIDER_1
};

enum DevicePredivider {
	PREDIV_NONE = ADC_PREDIVIDER_1,
	PREDIV_JOYSTICK = ADC_PREDIVIDER_1,
	PREDIV_ACCELEREROMETER = ADC_PREDIVIDER_64,
	PREDIV_MICROPHONE = ADC_PREDIVIDER_1,
	PREDIV_TEMP_SENSOR = ADC_PREDIVIDER_1,
	PREDIV_AMBIENT_LIGHT = ADC_PREDIVIDER_1
};

}  // namespace adc14

/**
 * Default ADC14 module function.
 */
const peripheral::gpio::ModuleFunction ADC14_MODULE_FUNCTION =
    peripheral::gpio::ModuleFunction::TERTIARY;

/**
 * Default ADC14 precision.
 */
const peripheral::adc14::Precision ADC14_PRECISION =
    peripheral::adc14::Precision::P14BIT;

/**
 * Default ADC14 power mode.
 */
const peripheral::adc14::PowerMode ADC14_POWER_MODE =
    peripheral::adc14::PowerMode::UNRESTRICTED;

/**
 * Default ADC14 clock source.
 */
const uint32_t ADC14_CLOCK_SOURCE = ADC_CLOCKSOURCE_ADCOSC;

/**
 * Default ADC14 channel mask.
 */
const uint32_t ADC14_INTERNAL_CHANNEL_MASK = 0;

class Adc14 {
 public:
	Adc14(peripheral::adc14::AnalogInputDevice i_eDevice);
	~Adc14();

	/**
	 * Wait until the adc is not busy.
	 */
	void WaitForAdcModule(void);

	/**
	 * Get the interrupt mask
	 *
	 * @return Return the value of m_uf64InterruptMask
	 */
	uint_fast64_t GetInterruptMask(void);

	/**
	 * Set the adc resolution. Available options:
	 * 	 ADC_8BIT, ADC_10BIT, ADC_12BIT, ADC_14BIT
	 *
	 * @param i_u32Resolution The adc  resolution.
	 */
	void SetResolution(const uint32_t i_u32Resolution);

	/**
	 * Configure the adc to use a simple memory location for the
	 * conversion/sample. The memory used is m_u32SimpleMemoryMap
	 * member
	 *
	 * @param i_bRepeat Indicates if repeat the conversion/sample
	 * after the first sample/conversion
	 */
	void SetSimpleSampleMode(const bool i_bRepeat);

	/**
	 * Get the sample result from the adc when is working in simple
	 * sample mode.
	 */
	uint_fast16_t GetSimpleSampleModeResult(void);

	/**
	 * Configure the Adc14 module considering i_eAnalogMeasure. Each
	 * device has its single/unique configuration
	 *
	 * @return True if the configuration is success
	 */
	bool ConfigureDevice();

	/**
	 * Set the conversion timer in manual mode. The user has to trigger
	 * the conversion signal after aeach converion/sample using
	 * EnableAndTriggerConversion or TriggerSignalConversion.
	 */
	void SetSampleManualTimer(void);

	/**
	 * Set the conversion timer in automatic mode. After every the adc
	 * will automatically continue with the next sample
	 */
	void SetSampleAutmaticTimer(void);

	/**
	 * Trigger the conversion signal and start the next covertion/sample.
	 */
	void TriggerSignalConversion(void);

	/**
	 * Enable conversion and start with the first conversion/sample
	 */
	void EnableConversion(void);

	/**
	 * Get the adc conversion resolution
	 *
	 * @return Adc resolution
	 */
	uint_fast32_t GetResolution(void);

	/**
	 * Enable interrupt
	 *
	 */
	void EnableInterrupt(void);

	/**
	 * Register interrupt
	 *
	 * @param i_funcInterruptHandler Function to handler the interrupt
	 */
	void RegisterInterrupt(void (*i_funcInterruptHandler)(void) = 0);

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
	peripheral::GPIO* m_pGPIO[peripheral::adc14::MAX_GPIO_PINS];

	bool m_bHasInterrupt;
	uint32_t m_u32SimpleMemoryMap;
	uint_fast64_t m_uf64InterruptMask;
	peripheral::adc14::AnalogInputDevice m_u32AnalogMeasureDevice;

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
