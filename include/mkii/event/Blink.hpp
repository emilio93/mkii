#ifndef MKII_MKII_EVENT_BLINK_H
#define MKII_MKII_EVENT_BLINK_H

#include <cstddef>

#include "mkii/IEvent.hpp"
#include "mkii/Led.hpp"
#include "peripheral/Timer32.hpp"

namespace mkii {

class Led;

namespace event {

/******************************************************************************
 *                                                                            *
 * BLINKING EVENT                                                             *
 *                                                                            *
 * Toggles on and off the LED for a specified quantity of times and period    *
 * A single blinking can be happening at every moment for the LED class.      *
 * The blinking event disables writes to the LED state.                       *
 * The state of the led after the blinking is done will be the same as it     *
 *   was before the blinking started.                                         *
 * Requires a timer with enabled interrupts                                   *
 *                                                                            *
 ******************************************************************************/
class Blink : public mkii::IEvent {
 public:
	/**
	 * Returns Blink Event.
	 *
	 * @return Blink* the blink Event with previous parameters or NULL if not set.
	 */
	static mkii::event::Blink* GetBlink();

	/**
	 * Get the Blink event with new parameters.
	 *
	 * @param i_u32BlinkCount The quantity of times to blink.
	 * @param i_u32TimerCount Counts the timer has to do before triggering a
	 * toggle.
	 * @param i_pBlinkTimer32 The timer to be used for the blinking.
	 * @param i_pBlinkLed The led to be used for the blinking.
	 * @return Blink* The Blink event with new parameters.
	 */
	static mkii::event::Blink* GetBlink(uint32_t i_u32BlinkCount,
	                                    uint32_t i_u32TimerCount,
	                                    peripheral::Timer32* i_pBlinkTimer32,
	                                    mkii::Led* i_pBlinkLed);

	/**
	 * Set up the Event and enable the interruption.
	 * Assigns object properties to the static variables.
	 */
	virtual void Init(void);

	/**
	 * The blink interrupt handler.
	 * This counts down to 0 for each pair of toggles the m_u32BlinkCount,
	 * toggling every m_u32TimerCount cicles counts for the used timer.
	 * On the last call, the interrupt is unregistered and disabled, the
	 * m_bIsBlinking variable is set to false, enabling a new blinking to start.
	 */
	virtual void Handler(void) final override;

	/**
	 * Calls the actual handler.
	 */
	static void HandlerCaller(void);

	/**
	 * Cleans up Event removing interrupt and setting blinking state to false.
	 */
	virtual void End(void) final override;

	/**
	 * Indicates if a blinking is ongoing.
	 *
	 * @return true A blinking is ongoing.
	 * @return false No blinking ongoing.
	 */
	bool IsBlinking(void);

 private:
	/**
	 * Singleton instance.
	 */
	static mkii::event::Blink* m_pInstance;

	/**
	 * Initial blink count.
	 * This is the quantity of times the led will do two toggles(on->off->on or
	 * off->on->off). For example given a value of 3, the led will toggle six
	 * times.
	 */
	uint32_t m_u32BlinkCount;
	static uint32_t m_u32StaticBlinkCount;

	/**
	 * Initial blink timer count.
	 * This is the quantity of counts the timer has to do before toggling the LED.
	 * Note that this is related to half the period of the blinking.
	 */
	uint32_t m_u32TimerCount;
	static uint32_t m_u32StaticTimerCount;

	/**
	 * Indicates if a blinking is ongoing.
	 * This is set to true on blinking event start and set to false on the end.
	 */
	static bool m_bStaticIsBlinking;

	/**
	 * Additional bit on m_u32BlinkCounter enables 2 toggles per count.
	 * This value must be set to false as initial condition for the blinking
	 * event.
	 */
	static bool m_bStaticBlinkCountHasToggle;

	/**
	 * Timer used for the blinking event.
	 */
	peripheral::Timer32* m_pBlinkTimer32;
	static peripheral::Timer32* m_pStaticBlinkTimer32;

	/**
	 * Led used for the blinking event.
	 */
	mkii::Led* m_pBlinkLed;
	static mkii::Led* m_pStaticBlinkLed;

	/**
	 * Construct a new Blink object with the given properties.
	 *
	 * @param i_u32BlinkCount The quantity of times to blink.
	 * @param i_u32TimerCount Counts the timer has to do before triggering a
	 * toggle.
	 * @param i_pBlinkTimer32 The timer to be used for the blinking.
	 * @param i_pBlinkLed The led to be used for the blinking.
	 */
	Blink(uint32_t i_u32BlinkCount, uint32_t i_u32TimerCount,
	      peripheral::Timer32* i_pBlinkTimer32, mkii::Led* i_pBlinkLed);

	/**
	 * Set the blink count.
	 *
	 * @param i_u32BlinkCount The quantity of times to blink.
	 */
	void SetBlinkCount(uint32_t i_u32BlinkCount);

	/**
	 * Set the timer count.
	 *
	 * @param i_u32TimerCount Counts the timer has to do before triggering a
	 * toggle.
	 */
	void SetTimerCount(uint32_t i_u32TimerCount);

	/**
	 * Set the Timer32 object.
	 *
	 * @param i_pTimer32 The timer to be used for the blinking.
	 */
	void SetTimer32(peripheral::Timer32* i_pTimer32);

	/**
	 * Set the Led object.
	 *
	 * @param i_pLed The led to be used for the blinking.
	 */
	void SetLed(mkii::Led* i_pLed);
};

}  // namespace event

}  // namespace mkii

#endif /* MKII_MKII_EVENT_BLINK_H */
