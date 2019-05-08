#ifndef MKII_MKII_TIMER_H
#define MKII_MKII_TIMER_H

#include <cstddef>

#include "peripheral/Timer32.hpp"

namespace mkii {

namespace timer {
  enum TimerTypes {
    TIMER_32
  };
}

/**
 * A timer with defined functionality.
 * Access to a timer is such that it has to be asked for, if there is an
 * available timer, it is given, if there is no available timer, no timer is
 * given(returns NULL).
 */
class Timer {
 public:

  /**
   * Finds an available timer on the specified
   *
   * @param i_eTimerType
   * @return mkii::Timer*
   */
  static mkii::Timer* GetTimer(mkii::timer::TimerTypes i_eTimerType);

  /**
   * Set the timer counter.
   */
  void SetCounter(uint32_t i_u32TimerCount);

  /**
   * Set and enable an interrupt handler and start timer.
   */
  void SetInterrupt(void (*i_funcHandler)(void));

  /**
   * Clear flag
   */
  void EndInterrupt();


 private:

  /**
   * The Timer32 if set or NULL.
   */
  peripheral::Timer32* m_pTimer32;

  /**
   * Creates a timer of the given type.
   *
   * @param i_eTimerType The type of timer to create.
   */
  Timer(peripheral::Timer32* i_pTimer32);

  void SetTimer32(peripheral::Timer32* i_pTimer32);

  peripheral::Timer32* GetTimer32();

  /**
   * Available Timers.
   * It is not expected to have a huge amount of timers so it is possible to
   * manage individually.
   */
  static peripheral::Timer32* m_pStaticTimer32_0;
  static peripheral::Timer32* m_pStaticTimer32_1;


};

}  // namespace mkii

#endif /* MKII_MKII_TIMER_H */
