
#ifndef MKII_PERIPHERAL_GPIO_H
#define MKII_PERIPHERAL_GPIO_H

#include "driverlib.h"

#include "peripheral/GPIO.hpp"

namespace peripheral {

namespace gpio {

/**
 * Available modes of operation for a GPIO.
 */
enum Mode {
	NONE,
	INPUT,
	OUTPUT,
	PERIPHERAL_MODULE_FUNCTION_INPUT,
	PERIPHERAL_MODULE_FUNCTION_OUTPUT,
	INPUT_WITH_PULL_DOWN_RESISTOR,
	INPUT_WITH_PULL_UP_RESISTOR
};

/**
 * Available GPIO ports. Copied values from driverlib for ease of access.
 */
enum Port {
	PORT1 = 1,
	PORT2 = 2,
	PORT3 = 3,
	PORT4 = 4,
	PORT5 = 5,
	PORT6 = 6,
	PORT7 = 7,
	PORT8 = 8,
	PORT9 = 9,
	PORT10 = 10,
	PORTA = 1,
	PORTB = 3,
	PORTC = 5,
	PORTD = 7,
	PORTE = 9,
	PORTJ = 11
};

/**
 * Available module functions. Copied values from driverlib for ease of access.
 */
enum ModuleFunction { PRIMARY = (0x01), SECONDARY = (0x02), TERTIARY = (0x03) };
/**
 * Available GPIO pins. Copied values from driverlib for ease of access.
 */
enum Pin {
	PIN0 = (0x0001),
	PIN1 = (0x0002),
	PIN2 = (0x0004),
	PIN3 = (0x0008),
	PIN4 = (0x0010),
	PIN5 = (0x0020),
	PIN6 = (0x0040),
	PIN7 = (0x0080),
	PIN8 = (0x0100),
	PIN9 = (0x0200),
	PIN10 = (0x0400),
	PIN11 = (0x0800),
	PIN12 = (0x1000),
	PIN13 = (0x2000),
	PIN14 = (0x4000),
	PIN15 = (0x8000),
	LL8 = (0xFF),
	LL16 = (0xFFFF)
};

/**
 * Direction of a state change in a GPIO. . Copied values from driverlib for
 * ease of access.
 */
enum Edge { HIGH_TO_LOW_TRANSITION = (0x01), LOW_TO_HIGH_TRANSITION = (0x00) };

}  // namespace gpio

/**
 * A base GPIO which is not necessarily bound to any mode of operation.
 */
class GPIO {
 public:
	/**
	 * Init a GPIO.
	 *
	 * @param i_u8Port The GPIO's Port.
	 * @param i_u32Pin The GPIO's Pin.
	 */
	GPIO(uint8_t i_u8Port, uint32_t i_u32Pin);

	/**
	 * Init a GPIO with a mode of operation.
	 *
	 * @param i_u8Port The GPIO's Port.
	 * @param i_u32Pin The GPIO's Pin.
	 * @param i_eMode The GPIO mode.
	 */
	GPIO(uint8_t i_u8Port, uint32_t i_u32Pin, peripheral::gpio::Mode i_eMode,
	     peripheral::gpio::ModuleFunction i_eModuleFunction);

	/**
	 * Obtain the GPIO's Port.
	 *
	 * @return uint8_t The GPIO's Port.
	 */
	uint8_t GetPort();

	/**
	 * Obtain the GPIO's Pin.
	 *
	 * @return uint32_t The GPIO's Pin.
	 */
	uint32_t GetPin();

	/**
	 * Set given GPIO as ouptut pin.
	 */
	void SetAsOutput();

	/**
	 * Set given GPIO as input pin.
	 */
	void SetAsInput();

	/**
	 * @TODO [emilio]
	 */
	void SetAsPeripheralModuleFunctionOutput(uint8_t i_u8Mode);

	/**
	 * @TODO [emilio]
	 */
	void SetAsPeripheralModuleFunctionInput(uint8_t i_u8Mode);

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void SetAsInputWithPullDownResistor();

	/**
	 * Set given GPIO as input pin with pull up resistor.
	 */
	void SetAsInputWithPullUpResistor();

	/**
	 * Enables the GPIO's port interrupt.
	 */
	void EnableInterrupt();

	/**
	 * Disables the GPIO's port interrupt.
	 */
	void DisableInterrupt();

	/**
	 * @TODO [emilio] Not in use.
	 */
	uint_fast16_t GetInterruptStatus();

	/**
	 * Clear the interrupt flag for the GPIO.
	 */
	void ClearInterruptFlag();

	/**
	 * @TODO [emilio] Not in use.
	 */
	void InterruptEdgeSelect(uint_fast8_t i_u8EdgeSelect);

	/**
	 * @TODO [emilio] Not in use.
	 */
	void SetDriveStrengthHigh();

	/**
	 * @TODO [emilio] Not in use.
	 */
	void SetDriveStrengthLow();

	/******************
	 * STATIC FUNCTIONS
	 ******************/

	/**
	 * @TODO [emilio] Not in use.
	 */
	static uint_fast16_t GetEnabledInterruptStatus(uint_fast8_t i_u8SelectedPort);

	/**
	 * @TODO [emilio] Not in use.
	 */
	static uint_fast16_t GetEnabledInterruptStatus(GPIO* i_pGPIO);

	/**
	 * Registers an interrupt on the given port.
	 *
	 * @param i_u8SelectedPort The port on which to register the interrupt.
	 * @param i_funcHandler The interrupt handler which is registered.
	 */
	static void RegisterInterrupt(uint_fast8_t i_u8SelectedPort,
	                              void (*i_funcHandler)(void));

	/**
	 * Registers an interrupt on the given GPIO.
	 *
	 * @param i_pGPIO The GPIO on which the interrupt is registered.
	 * @param i_funcHandler The interrupt handler which is registered.
	 */
	static void RegisterInterrupt(GPIO* i_pGPIO, void (*i_funcHandler)(void));

	/**
	 * Unregisters the interrupt handler and its call for the port in the given
	 * port.
	 *
	 * @param i_u8SelectedPort Port whose interrupt handler is unregistered.
	 */
	static void UnregisterInterrupt(uint_fast8_t i_u8SelectedPort);

	/**
	 * Unregisters the interrupt handler and its call for the port in the given
	 * GPIO.
	 *
	 * @param i_pGPIO GPIO whose port interrupt handler is unregistered.
	 */
	static void UnregisterInterrupt(GPIO* i_pGPIO);

 protected:
	/**
	 * Gpio's Port.
	 */
	uint8_t m_u8Port;

	/**
	 * Gpio's Pin.
	 */
	uint32_t m_u32Pin;

};

}  // namespace peripheral

#endif /* MKII_PERIPHERAL_GPIO_H */
