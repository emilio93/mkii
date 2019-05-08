#ifndef MKII_MKII_EVENT_PUSH_H
#define MKII_MKII_EVENT_PUSH_H

#include "mkii/Button.hpp"
#include "mkii/IEvent.hpp"
#include "mkii/Led.hpp"
#include "mkii/Timer.hpp"

namespace mkii {

class Button;

namespace event {

namespace push {
/**
 * The counts the timer does as guard before another button push triggers the
 * event.
 */
const uint32_t TIMEOUT_COUNT = 500;
}  // namespace push

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
 * Toggles led state independently of it's current state. If state is on,   *
 * the Led will turn off until a on condition or a button push. If state is *
 * off, the Led will turn on for 30 minutes or until the buton is pushed.   *
 *                                                                          *
 ****************************************************************************/
class Push : public mkii::IEvent {
 public:
	/**
	 * Assign values and obtain instance of Push Event.
	 *
	 * @param i_pButton The button to track.
	 * @param i_pLed The led to toggle.
	 * @param i_pTimer The timer to use.
	 * @return mkii::event::Push* The Push Event.
	 */
	static mkii::event::Push* GetPush(mkii::Button* i_pButton, mkii::Led* i_pLed,
	                                  mkii::Timer* i_pTimer);

	/**
	 * Obtain Push Event with previously set  properties, or NULL if class has not
	 * been instanciated.
	 *
	 * @return mkii::event::Push* The Push Event.
	 */
	static mkii::event::Push* GetPush();

	/**
	 * Initializes the variables for the handler and sets up the interrupt. Tracks
	 * a push on the button.
	 */
	virtual void Init();

	/**
	 * Manages an interruption. Toggles the Led.
	 */
	virtual void Handler();

	/**
	 * Calls the actual handler.
	 */
	static void HandlerCaller();

	/**
	 * Stop tracking a push in the button and reset variables to initial state.
	 */
	virtual void End();

 private:
	/**
	 * Singleton instance of the Push Event.
	 */
	static mkii::event::Push* m_pInstance;

	/**
	 * Indicates if the button push tracking is on.
	 */
	static bool m_bStaticIsTracking;

	/**
	 * Indicates a button push has just happened avoiding multiple unwanted fast
	 * interrupts.
	 */
	static bool m_bStaticIsActive;

	/**
	 * Count to wait before listening to another event.
	 */
	static const uint32_t m_u32StaticTimeoutCount;

	/**
	 * Indicates if a safe wait has been done after push.
	 */
	static bool m_bStaticHasTimeout;

	/**
	 * Button used in the event.
	 */
	mkii::Button* m_pButton;
	static mkii::Button* m_pStaticButton;

	/**
	 * Timer used to time the event.
	 */
	mkii::Timer* m_pTimer;
	static mkii::Timer* m_pStaticTimer;

	/**
	 * Led to be used in the event.
	 */
	mkii::Led* m_pLed;
	static mkii::Led* m_pStaticLed;

	/**
	 * Construct a new Push object with given properties.
	 *
	 * @param i_pButton The button to use.
	 * @param i_pLed The led to use.
	 * @param i_pTimer The timer to use.
	 */
	Push(mkii::Button* i_pButton, mkii::Led* i_pLed,
	     mkii::Timer* i_pTimer);

	/**
	 * Set the Button object.
	 *
	 * @param i_pButton The Button.
	 */
	void SetButton(mkii::Button* i_pButton);

	/**
	 * Set the Led object.
	 *
	 * @param i_pLed The Led.
	 */
	void SetLed(mkii::Led* i_pLed);

	/**
	 * Set the Timer object.
	 *
	 * @param i_pTimer The Timer.
	 */
	void SetTimer(mkii::Timer* i_pTimer);
};

}  // namespace event

}  // namespace mkii

#endif /* MKII_MKII_EVENT_PUSH_H */
