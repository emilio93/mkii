#include "Top.hpp"
#include "mkii/Led.hpp"

using namespace mkii{
bool Led::m_bIsBlinking = false;
uint32_t Led::m_u32BlinkCount = 0;
uint32_t Led::m_u32TimerCount = 0;
bool Led::m_bBlinkCountHasToggle = false;

Led::Led() {
  this->m_mkiiLed = new mkii::Led();
}

mkii::Led* Led::GetMkiiLed(void) {
  return this->m_mkiiLed;
}

void Led::Blink(uint32_t i_u32BlinkCount, uint32_t i_u32TimerCount) {
  if (Led::m_bIsBlinking) {
    // Another blink is in course.
    // TODO: define behaviour.
    // Current behaviour is to not execute blink.
    return;
  }
  if (i_u32BlinkCount == 0 || i_u32TimerCount == 0) {
    // Troll detected...
    return;
  }

  // Set interrupt handler
  void (*l_pIRQHandler)() = this->BlinkInterruptHandler;
  Top::GetTop()->GetTimer32()->RegisterInterruption(true, l_pIRQHandler);

  // Set blinking initial settings
  Led::m_u32BlinkCount = i_u32BlinkCount;
  Led::m_bBlinkCountHasToggle = false;
  Led::m_u32TimerCount = i_u32TimerCount;
  Led::m_bIsBlinking = true;

  // First call as soon as posible
  Led::BlinkInterruptHandler();
}

void Led::BlinkInterruptHandler(void) {
  if (Led::m_bIsBlinking) {
    // Always toggle led and clear interrupt flag
    Top::GetTop()->GetLed()->GetMkiiLed()->Toggle();
    Top::GetTop()->GetTimer32()->ClearInterruptionFlag();

    if (Led::m_u32BlinkCount == 0 && Led::m_bBlinkCountHasToggle) {
      // Stop condition: counter has reached 0 and both toggles for last blink
      // have happened.
      // No further interrupt is done and handler is unregistered. Blinking
      // state is turned off.
      Top::GetTop()->GetTimer32()->EnableInterruption(false);
      Top::GetTop()->GetTimer32()->RegisterInterruption(false);
      Led::m_bIsBlinking = false;
      return;
    } else {
      // Regular operation: do both toggles for each count and reset timer and
      // interrupt.
      if (Led::m_bBlinkCountHasToggle) {
        Led::m_u32BlinkCount = Led::m_u32BlinkCount - 1;
      }
      Led::m_bBlinkCountHasToggle = !Led::m_bBlinkCountHasToggle;
      // Reset interrupt
      Top::GetTop()->GetTimer32()->SetCounter(Led::m_u32TimerCount);
      Top::GetTop()->GetTimer32()->EnableInterruption(true);
      return;
    }
  } else {
    // Shouldn't be blinking then
    return;
  }
}


}
