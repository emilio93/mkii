#ifndef MKII_MKII_LED_H
#define MKII_MKII_LED_H

#include <string>

#include "peripheral/GPIO.hpp"
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
	peripheral::gpio::OutputGPIO* m_LedGPIO;

	/**
	 * Indicates wheter the LED is set to not writable.
	 * Initialized as true. An event can disable the writing to the state of the
	 * led in order to avoid unexpected behaviours on the output.
	 */
	static bool m_bIsWritable;

	/****************************************************************************
	 *                                                                          *
	 * BLINKING EVENT                                                           *
	 *                                                                          *
	 * Toggles on and off the LED for a specified quantity of times and period  *
	 * A single blinking can be happening at every moment for the LED class.    *
	 * The blinking event disables writes to the LED state.                     *
	 * The state of the led after the blinking is done will be the same as it   *
	 *   was before the blinking started.                                       *
	 * Requires a timer with enabled interrupts                                 *
	 *                                                                          *
	 ****************************************************************************/

	/**
	 * Initial blink count.
	 * This is the quantity of times the led will do two toggles(on->off->on or
	 * off->on->off). For example given a value of 3, the led will toggle six
	 * times.
	 */
	static uint32_t m_u32BlinkCount;

	/**
	 * Initial blink timer count.
	 * This is the quantity of counts the timer has to do before toggling the LED.
	 * Note that this is related to half the period of the blinking.
	 */
	static uint32_t m_u32TimerCount;

	/**
	 * Indicates if a blinking is ongoing.
	 * This is set to true on blinking event start and set to false on the end.
	 */
	static bool m_bIsBlinking;

	/**
	 * Additional bit on m_u32BlinkCounter enables 2 toggles per count.
	 * This value must be set to false as initial condition for the blinking
	 * event.
	 */
	static bool m_bBlinkCountHasToggle;

	/**
	 * Timer used for the blinking event.
	 */
	static peripheral::Timer32* m_pBlinkTimer32;

	/**
	 * Led used for the blinking event.
	 */
	static mkii::Led* m_pBlinkLed;

	/**
	 * The blink interrupt handler.
	 * This counts down to 0 for each pair of toggles the m_u32BlinkCount,
	 * toggling every m_u32TimerCount cicles counts for the used timer.
	 * On the last call, the interrupt is unregistered and disabled, the
	 * m_bIsBlinking variable is set to false, enabling a new blinking to start.
	 */
	static void BlinkInterruptHandler(void);
};
}  // namespace mkii

#endif /* MKII_MKII_LED_H */
