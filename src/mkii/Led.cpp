#include <string>

#include "Top.hpp"
#include "mkii/Led.hpp"
#include "peripheral/Timer32.hpp"

bool mkii::Led::m_bIsBlinking = false;
uint32_t mkii::Led::m_u32BlinkCount = 0;
uint32_t mkii::Led::m_u32TimerCount = 0;
bool mkii::Led::m_bBlinkCountHasToggle = false;

mkii::Led::Led(uint32_t i_u32Port, uint32_t i_u32Pin) {
  this->m_u32Port = i_u32Port;
  this->m_u32Pin = i_u32Pin;
}

void mkii::Led::SetState(bool i_bState) {
  // TODO [emilio]
  ;
}

bool mkii::Led::GetState(void) {
  // TODO [emilio]
  return true;
}

void mkii::Led::Toggle() {
  // TODO [emilio]
  this->SetState(!this->GetState());
}

void mkii::Led::Blink(uint32_t i_u32BlinkCount, uint32_t i_u32TimerCount) {
  if (mkii::Led::m_bIsBlinking) {
    // Another blink is in course.
    // TODO: define behaviour.
    // Current behaviour is to not execute blink.
    return;
  }
  if (i_u32BlinkCount == 0 || i_u32TimerCount == 0) {
    // Troll detected...
    return;
  }

  // Set blinking initial settings
  mkii::Led::m_bIsBlinking = true;
  mkii::Led::m_bBlinkCountHasToggle = false;
  mkii::Led::m_u32BlinkCount = i_u32BlinkCount;
  mkii::Led::m_u32TimerCount = i_u32TimerCount;

  // Set interrupt handler
  Top::GetTop()->GetTimer32()->RegisterInterrupt(true, this->BlinkInterruptHandler);

  // First call as soon as posible
  mkii::Led::BlinkInterruptHandler();
}

void mkii::Led::BlinkInterruptHandler(void) {
  if (mkii::Led::m_bIsBlinking) {
    // Always toggle led and clear interrupt flag
    Top::GetTop()->GetLed()->Toggle();
    Top::GetTop()->GetTimer32()->ClearInterruptFlag();

    if (mkii::Led::m_u32BlinkCount == 0 && mkii::Led::m_bBlinkCountHasToggle) {
      // Stop condition: counter has reached 0 and both toggles for last blink
      // have happened.
      // No further interrupt is done and handler is unregistered. Blinking
      // state is turned off.
      Top::GetTop()->GetTimer32()->EnableInterrupt(false);
      Top::GetTop()->GetTimer32()->RegisterInterrupt(false);
      mkii::Led::m_bIsBlinking = false;
      return;
    } else {
      // Regular operation: do both toggles for each count and reset timer and
      // interrupt.
      if (mkii::Led::m_bBlinkCountHasToggle) {
        mkii::Led::m_u32BlinkCount = mkii::Led::m_u32BlinkCount - 1;
      }
      mkii::Led::m_bBlinkCountHasToggle = !mkii::Led::m_bBlinkCountHasToggle;
      // Reset interrupt
      Top::GetTop()->GetTimer32()->SetCounter(mkii::Led::m_u32TimerCount);
      Top::GetTop()->GetTimer32()->EnableInterrupt(true);
      return;
    }
  } else {
    // Shouldn't be blinking then
    return;
  }

}
