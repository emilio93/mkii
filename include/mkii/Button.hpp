#ifndef MKII_MKII_BUTTON_H
#define MKII_MKII_BUTTON_H

#include <cstddef>

#include "mkii/Led.hpp"
#include "mkii/event/Push.hpp"
#include "peripheral/GPIO.hpp"
#include "peripheral/Timer32.hpp"
#include "peripheral/gpio/InputGPIO.hpp"

namespace mkii {

namespace button {

/**
 * @brief
 *
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
 * Representation of a Button and useful events to apply on it.
 */
class Button {
 public:
	/**
	 * Class constructor obtains corresponding GPIO.
	 */
	Button(mkii::button::ButtonId i_eButtonId);

	peripheral::gpio::InputGPIO* GetGPIO();

	void SetButtonId(mkii::button::ButtonId i_eButtonId);

	mkii::button::ButtonId GetButtonId();

	void TrackButtonPush(mkii::Led* i_pLed, peripheral::Timer32* i_pTimer32);

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
