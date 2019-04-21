#ifndef MKII_MKII_EVENT_PUSH_H
#define MKII_MKII_EVENT_PUSH_H

#include "mkii/Button.hpp"
#include "mkii/IEvent.hpp"
#include "mkii/Led.hpp"
#include "peripheral/Timer32.hpp"

namespace mkii {

class Button;

namespace event {

namespace push {
const uint32_t TIMEOUT_COUNT = 500;
}

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
	static mkii::event::Push* GetPush(mkii::Button* i_pButton, mkii::Led* i_pLed,
	                                  peripheral::Timer32* i_pTimer32);
	static mkii::event::Push* GetPush();
	virtual void Init();
	virtual void Handler();
	static void HandlerCaller();
	virtual void End();

 private:
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
	peripheral::Timer32* m_pTimer32;
	static peripheral::Timer32* m_pStaticTimer32;

	/**
	 * Led to be used in the event.
	 */
	mkii::Led* m_pLed;
	static mkii::Led* m_pStaticLed;

	Push(mkii::Button* i_pButton, mkii::Led* i_pLed,
	     peripheral::Timer32* i_pTimer32);

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
	 * Set the Timer32 object.
	 *
	 * @param i_pTimer32 The Timer32.
	 */
	void SetTimer32(peripheral::Timer32* i_pTimer32);
};

}  // namespace event

}  // namespace mkii

#endif /* MKII_MKII_EVENT_PUSH_H */
