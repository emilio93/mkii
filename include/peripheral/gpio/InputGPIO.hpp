
#ifndef MKII_PERIPHERAL_GPIO_INPUTGPIO_H
#define MKII_PERIPHERAL_GPIO_INPUTGPIO_H

#include "driverlib.h"

#include "peripheral/GPIO.hpp"

namespace peripheral {

namespace gpio {

/**
 * Types of input mode.
 */
enum InputMode { REGULAR, PULL_UP_RESISTOR, PULL_DOWN_RESISTOR };

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
	 * @param i_eInputMode The type of input to use.
	 */
	InputGPIO(uint8_t i_u8Port, uint32_t i_u32Pin,
	          peripheral::gpio::InputMode i_eInputMode);

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

#endif /* MKII_PERIPHERAL_GPIO_INPUTGPIO_H */
