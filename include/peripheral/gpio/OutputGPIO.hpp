
#ifndef MKII_PERIPHERAL_GPIO_OUTPUTGPIO_H
#define MKII_PERIPHERAL_GPIO_OUTPUTGPIO_H

#include "driverlib.h"

#include "peripheral/GPIO.hpp"

namespace peripheral {

namespace gpio {

/**
 * The output GPIO represents a GPIO pin(s) which is(are) set to be used as an
 * output(s) pin(s).
 *
 */
class OutputGPIO : public GPIO {
 public:
	/**
	 * Init an OutputGPIO.
	 * Initializes a GPIO as output pin.
	 *
	 * @param i_u8Port Port of the GPIO.
	 * @param i_u32Pin Pin mask for the GPIO.
	 * @param i_bInit Indicates if the GPIO is to be set as output.
	 */
	OutputGPIO(uint8_t i_u8Port, uint32_t i_u32Pin, bool i_bInit = true);

	/**
	 * Set the Output value of the gpio.
	 *
	 * @param value Output value of the gpio.
	 */
	void SetOutput(bool i_bValue);

	/**
	 * Get the Output value of the gpio.
	 *
	 * @return true value high.
	 * @return false value low.
	 */
	bool GetOutput();

	/**
	 * Toggles the output value of the gpio.
	 */
	void Toggle();

 private:
	/**
	 * Output value.
	 */
	bool m_bState;

	/**
	 * Updates gpio output value to m_bState.
	 */
	void UpdateState();
};

}  // namespace gpio
}  // namespace peripheral

#endif /* MKII_PERIPHERAL_GPIO_OUTPUTGPIO_H */
