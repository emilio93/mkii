#ifndef MKII_MKII_EVENT_LEDTIMEOUT_H
#define MKII_MKII_EVENT_LEDTIMEOUT_H

#include <cstddef>

#include "mkii/IEvent.hpp"
#include "mkii/Led.hpp"
#include "mkii/Timer.hpp"

namespace mkii {

class Led;

namespace event {

/****************************************************************************
 *                                                                          *
 * LED TIMEOUT EVENT                                                        *
 *                                                                          *
 * The LedTimeoutEvent will turn off a led after a specified period of      *
 * time. If the led is turned off in some other way, this event will end    *
 * it's behaviour.                                                          *
 * The actual event is turned off either when the timer reaches the count   *
 * cycles or when the led changes from on to off.                           *
 * Some examples of the expected behaviour:                                 *
 * 1                                                                        *
 *   - Led is on                                                            *
 *   - timeout event for 30 minutes                                         *
 *   - nothing happens for 30 minutes                                       *
 *   - led is turned off                                                    *
 * 2                                                                        *
 *   - Led is off                                                           *
 *   - timeout event for 30 minutes                                         *
 *   - timeout event isn't triggered because led is already off             *
 * 3                                                                        *
 *   - Led is on                                                            *
 *   - timeout event for 30 minutes                                         *
 *   - Led is turned off via button                                         *
 *   - timeout event is cancelled                                           *
 *                                                                          *
 ****************************************************************************/
class LedTimeout : public mkii::IEvent {
 public:
	/**
	 * Obtain the LedTimeout event or NULL if it hasn't been created.
	 *
	 * @return mkii::event::LedTimeout* The LedTimeout event or NULL.
	 */
	static mkii::event::LedTimeout* GetLedTimeout(void);

	/**
	 * Sets parameters on the LedTimeout event and returns the LedTimeout event.
	 *
	 * @param i_pLed The led to turn off.
	 * @param i_pTimer The timer to use for the timeout.
	 * @param i_u32TimerCount The timer count cycles before the timeout.
	 * @return mkii::event::LedTimeout* The LedTimeout event with new parameters.
	 */
	static mkii::event::LedTimeout* GetLedTimeout(mkii::Led* i_pLed,
	                                              mkii::Timer* i_pTimer,
	                                              uint32_t i_u32TimerCount);

	/**
	 * Set up the Event and enable the interrupt.
	 * Assigns object properties to the static variables.
	 */
	virtual void Init(void);

	/**
	 * Calls the actual handler.
	 */
	static void HandlerCaller(void);

	/**
	 * The led timeout interrupt handler.
	 * This turns off the led.
	 */
	virtual void Handler(void) final override;

	/**
	 * Cleans up Event removing interrupt and setting timeout state to off.
	 */
	virtual void End(void) final override;

	/**
	 * Indicates if a led timeout is ongoing.
	 *
	 * @return true A led timeout is ongoing.
	 * @return false No led timeout ongoing.
	 */
	bool IsTimeoutOn(void);

	/**
	 * Set the Led object.
	 *
	 * @param i_pLed The Led to use in the event.
	 */
	void SetLed(mkii::Led* i_pLed);

	/**
	 * Set the Timer object.
	 *
	 * @param i_pTimer The Timer to use in the event.
	 */
	void SetTimer(mkii::Timer* i_pTimer);

	/**
	 * Set the timer count value to be set on event launch.
	 *
	 * @param i_u32TimerCount The cycle count before the timeout.
	 */
	void SetTimerCount(uint32_t i_u32TimerCount);

	/**
	 * Get the Led object.
	 *
	 * @return mkii::Led* The Led object.
	 */
	mkii::Led* GetLed();

	/**
	 * Get the Timer object.
	 *
	 * @return peripheral::Timer32* The Timer32 object.
	 */
	mkii::Timer* GetTimer();

	/**
	 * Get the value of cycle counts for the timer to trigger the timeout.
	 *
	 * @return uint32_t The value of cycle counts for the timer to trigger the
	 * timeout.
	 */
	uint32_t GetTimerCount();

 private:
	/**
	 * Singleton instance.
	 */
	static mkii::event::LedTimeout* m_pInstance;

	/**
	 * The led to be turned of when the timeout is over.
	 */
	mkii::Led* m_pLed;
	static mkii::Led* m_pStaticLed;

	/**
	 * The timer to be used to set thte timeout.
	 */
	mkii::Timer* m_pTimer;
	static mkii::Timer* m_pStaticTimer;

	/**
	 * The timeout count
	 */
	uint32_t m_u32TimerCount;
	static uint32_t m_u32StaticTimerCount;

	/**
	 * Indicates if timeout is going on.
	 */
	static bool m_bStaticIsTimeoutOn;

	/**
	 * @brief Construct a new LedTimeout object and asign it's parameters.
	 *
	 * @param i_pLed The led to turn off when the timeout is over.
	 * @param i_pTimer The
	 * @param i_u32TimerCount
	 */
	LedTimeout(mkii::Led* i_pLed, mkii::Timer* i_pTimer,
	           uint32_t i_u32TimerCount);
};

}  // namespace event
}  // namespace mkii

#endif
