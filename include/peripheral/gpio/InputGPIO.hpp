
#ifndef MKII_PERIPHERAL_GPIO_INPUT_GPIO_H
#define MKII_PERIPHERAL_GPIO_INPUT_GPIO_H

#include <iostream>

#include "driverlib.h"

#include "peripheral/GPIO.hpp"

namespace peripheral {

namespace gpio {

/**
 * The output GPIO represents a GPIO pin(s) which is(are) set to be used as an
 * output(s) pin(s).
 *
 */
class InputGPIO : public GPIO {
 public:
	/**
	 * Init an InputGPIO.
	 * Initializes a GPIO as input pin.
	 * @param i_u8Port Port of the GPIO.
	 * @param i_u32Pin Pin mask for the GPIO.
	 */
	InputGPIO(uint8_t i_u8Port, uint32_t i_u32Pin);

	/**
	 * Obtains the current value at the pin.
	 *
	 * @return true pin is high value.
	 * @return false pin is low value.
	 */
	bool ReadValue();
};

}  // namespace gpio
}  // namespace peripheral

#endif /* MKII_PERIPHERAL_GPIO_INPUT_GPIO_H */
