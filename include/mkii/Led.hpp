#ifndef MKII_MKII_LED_H
#define MKII_MKII_LED_H

#include <cstddef>

#include "mkii/event/Blink.hpp"
#include "peripheral/Timer32.hpp"
#include "peripheral/gpio/OutputGPIO.hpp"

namespace mkii {

/**
 * Default LED gpio port.
 */
const peripheral::gpio::Port LED_PORT = peripheral::gpio::Port::PORT1;

/**
 * Default LED gpio pin.
 */
const peripheral::gpio::Pin LED_PIN = peripheral::gpio::Pin::PIN0;

/**
 * Representation of a LED and useful events to apply on it.
 */
class Led {
 public:
	/**
	 * Class constructor obtains corresponding GPIO.
	 */
	Led();

	/**
	 * Set led output.
	 */
	void SetState(bool i_bState);

	/**
	 * Obtain current led output.
	 */
	bool GetState();

	/**
	 * Toggle output of led. If out value is 0, sets it to 1, else sets it to 0.
	 */
	void Toggle();

	/**
	 * Blink led i_u32BlinkCount times for a timer count i_u32TimerCount.
	 * This will cause a timer to count up to i_u32TimerCount for
	 * 2*i_u32BlinkCount times, toggling the led's output each time.
	 * The blinking event will be launched upon calling this function.
	 * @param i_u32BlinkCount Quantity of times the led blinks.
	 * @param i_u32TimerCount Timer Count.
	 */
	void Blink(uint32_t i_u32BlinkCount, uint32_t i_u32TimerCount,
	           peripheral::Timer32* i_pTimer32);

	/**
	 * Indicates if there is an ongoing blinking event.
	 *
	 * @return true A blinking envent is ongoing.
	 * @return false No blinking envent is ongoing.
	 */
	bool IsBlinking();

 private:
	/**
	 * GPIO of the Led.
	 */
	peripheral::gpio::OutputGPIO* m_pLedGPIO;

	/**
	 * Indicates wheter the LED is set to not writable.
	 * Initialized as true. An event can disable the writing to the state of the
	 * led in order to avoid unexpected behaviours on the output.
	 */
	static bool m_bIsWritable;
};
}  // namespace mkii

#endif /* MKII_MKII_LED_H */
