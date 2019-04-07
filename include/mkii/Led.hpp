#ifndef LUNAV_LED_H
#define LUNAV_LED_H

#include <string>

#include "mkii/Led.hpp"
#include "peripheral/Timer32.hpp"

namespace mkii{
  /**
   * @brief The top module acts as a container which manages and communicates
   * all the components.
   */
  class Led {
  public:


    /**
     * Class constructor.
     */
    Led();

    /**
     * Blink led i_u32BlinkCount times for a timer count i_u32TimerCount.
     * This will cause a timer to count up to i_u32TimerCount for
     * 2*i_u32BlinkCount times, toggling the led's output each time.
     * @param i_u32BlinkCount Quantity of times the led blinks.
     * @param i_u32TimerCount Timer Counter.
     */
    void Blink(uint32_t i_u32BlinkCount, uint32_t i_u32TimerCount);

    /**
     * Obtain Led object.
     */
    mkii::Led* GetMkiiLed(void);

  private:
    /**
     * Initial blink count.
     */
    static uint32_t m_u32BlinkCount;

    /**
     * Initial blink timer count.
     */
    static uint32_t m_u32TimerCount;

    /**
     * Indicates if a blinking is ongoing.
     */
    static bool m_bIsBlinking;

    /**
     * Additional bit on m_u32BlinkCounter enables 2 toggles per count.
     */
    static bool m_bBlinkCountHasToggle;

    /**
     * Mkii led instance.
     */
    mkii::Led* m_mkiiLed;

    /**
     * The blink interrupt handler.
     */
    static void BlinkInterruptHandler(void);
  };
}

#endif /* LUNAV_LED_H */