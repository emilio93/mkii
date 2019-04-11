
#ifndef MKII_PERIPHERAL_GPIO_H
#define MKII_PERIPHERAL_GPIO_H

#include <stdbool.h>
#include <stdint.h>

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
	 */
	GPIO(uint8_t i_u8Port, uint32_t u32Pin);

	/**
	 * Init a GPIO with a mode of operation.
	 *
	 * @param i_u8Port
	 * @param u32Pin
	 * @param i_u32Mode
	 */
	GPIO(uint8_t i_u8Port, uint32_t u32Pin, peripheral::gpio::Mode i_eMode);

	/**
	 * @brief Obtain the GPIO's Port.
	 *
	 * @return uint8_t The GPIO's Port.
	 */
	uint8_t GetPort();

	/**
	 * @brief Obtain the GPIO's Pin.
	 *
	 * @return uint32_t The GPIO's Pin.
	 */
	uint32_t GetPin();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void SetAsOutput();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void SetAsInput();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void SetAsPeripheralModuleFunctionOutput();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void SetAsPeripheralModuleFunctionInput();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void SetAsInputWithPullDownResistor();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void SetAsInputWithPullUpResistor();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void enableInterrupt();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void disableInterrupt();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	uint_fast16_t getInterruptStatus();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void clearInterruptFlag();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void interruptEdgeSelect(uint_fast8_t edgeSelect);

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void setDriveStrengthHigh();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	void setDriveStrengthLow();

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	static uint_fast16_t getEnabledInterruptStatus(uint_fast8_t selectedPort);

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	static uint_fast16_t getEnabledInterruptStatus(GPIO* i_pGPIO);

	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	static void RegisterInterrupt(uint_fast8_t selectedPort,
	                              void (*intHandler)(void));
	/**
	 * @breif
	 *
	 * @TODO [emilio]
	 */
	static void RegisterInterrupt(GPIO* i_pGPIO, void (*intHandler)(void));

	/**
	 * @breif
	 */
	static void UnregisterInterrupt(uint_fast8_t selectedPort);

	/**
	 * @breif
	 *
	 * @TODO [emilio]
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
