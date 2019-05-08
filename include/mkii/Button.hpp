#ifndef MKII_MKII_BUTTON_H
#define MKII_MKII_BUTTON_H

#include <cstddef>

#include "mkii/Led.hpp"
#include "mkii/event/Push.hpp"
#include "peripheral/GPIO.hpp"
#include "mkii/Timer.hpp"
#include "peripheral/gpio/InputGPIO.hpp"

namespace mkii {

namespace button {

/**
 * Existing buttons.
 */
enum ButtonId { S1, S2 };
}  // namespace button

/**
 * Default Button gpio port.
 */
const peripheral::gpio::Port BUTTON_PORT = peripheral::gpio::Port::PORT1;

/**
 * Default Button S1 gpio pin.
 */
const peripheral::gpio::Pin BUTTON_S1_PIN = peripheral::gpio::Pin::PIN1;

/**
 * Default Button S2 gpio pin.
 */
const peripheral::gpio::Pin BUTTON_S2_PIN = peripheral::gpio::Pin::PIN4;

/**
 * Representation of a Button.
 */
class Button {
 public:
	/**
	 * Class constructor obtains corresponding GPIO.
	 */
	Button(mkii::button::ButtonId i_eButtonId);

	/**
	 * Obtains the Button's GPIO.
	 *
	 * @return peripheral::gpio::InputGPIO* Button's GPIO.
	 */
	peripheral::gpio::InputGPIO* GetGPIO();

	/**
	 * Sets the button ID.
	 *
	 * @param i_eButtonId The button ID.
	 */
	void SetButtonId(mkii::button::ButtonId i_eButtonId);

	/**
	 * Obtain the button ID.
	 *
	 * @return mkii::button::ButtonId The button ID.
	 */
	mkii::button::ButtonId GetButtonId();

	/**
	 * Start listening for a button push to trigger an interrupt which will
	 * trigger the Push Event.
	 *
	 * @param i_pLed The led to toggle on push.
	 * @param i_pTimer The timer used.
	 */
	void TrackButtonPush(mkii::Led* i_pLed, mkii::Timer* i_pTimer);

	/**
	 * Disables the interrupts for the Push Event and reset it's variables.
	 */
	void IgnoreButtonPush();

 private:
	/**
	 * GPIO of the Button.
	 */
	peripheral::gpio::InputGPIO* m_pButtonGPIO;

	/**
	 * Id of the limited buttons available.
	 */
	mkii::button::ButtonId m_eButtonId;
};
}  // namespace mkii

#endif /* MKII_MKII_BUTTON_H */
