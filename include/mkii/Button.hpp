#ifndef MKII_MKII_BUTTON_H
#define MKII_MKII_BUTTON_H

#include <cstddef>

#include "mkii/Led.hpp"
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

	/**
	 * Enables interrupts on button push.
	 *
	 * @param i_pTimer32 Timer used for the push event.
	 */
	void StartTrackPush(peripheral::Timer32* i_pTimer32, mkii::Led* i_pLed);

	/**
	 * Disables interrupts on button push.
	 */
	void StopTrackPush();

	peripheral::gpio::InputGPIO* GetGPIO();

	void SetButtonId(mkii::button::ButtonId i_eButtonId);

	mkii::button::ButtonId GetButtonId();

 private:
	/**
	 * GPIO of the Button.
	 */
	peripheral::gpio::InputGPIO* m_pButtonGPIO;

	/**
	 * Id of the limited buttons available.
	 */
	mkii::button::ButtonId m_eButtonId;

	/****************************************************************************
	 *                                                                          *
	 * PUSH EVENT                                                               *
	 *                                                                          *
	 * As many buttons, push events can exist and its variables and handlers    *
	 * are identified  by its ID(S1, S2, ...) at the end of the name.           *
	 * Diferent handlers mught need extra variables which should be named       *
	 * properly as well.                                                        *
	 * Requires a timer with enabled interrupts                                 *
	 *                                                                          *
	 * S1                                                                       *
	 * Toggles led state independently of it's current state. If state is on,   *
	 * the Led will turn off until a on condition or a button push. If state is *
	 * off, the Led will turn on for 30 minutes or until the buton is pushed.   *
	 *                                                                          *
	 * S2                                                                       *
	 * Not in use.                                                              *
	 *                                                                          *
	 ****************************************************************************/

	/**
	 * Indicates if the button push tracking is on.
	 */
	static bool m_bIsTrackingS1;

	/**
	 * Indicates a button push has just happened avoiding multiple unwanted fast
	 * interrupts.
	 */
	static bool m_bIsPushActiveS1;

	/**
	 * Button used to trigger the event.
	 */
	static mkii::Button* m_pPushButtonS1;

	/**
	 * Count to wait before listening to another event.
	 */
	static const uint32_t m_u32PushTimeoutCountS1;

	/**
	 * Indicates if a safe wait has been done after push.
	 */
	static bool m_bPushHasTimeoutS1;

	/**
	 * Timer used to time the event.
	 */
	static peripheral::Timer32* m_pTimer32S1;

	static mkii::Led* m_pLed;

	/**
	 * Handler for the event occurrance.
	 */
	static void PushInterruptHandlerS1(void);
	// static void pushInterruptHandlerS2(void);
};
}  // namespace mkii

#endif /* MKII_MKII_BUTTON_H */
