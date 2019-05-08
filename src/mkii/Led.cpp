#include "mkii/Led.hpp"

mkii::Led::Led() {
	this->m_pLedGPIO =
	    new peripheral::gpio::OutputGPIO(mkii::LED_PORT, mkii::LED_PIN);
}

void mkii::Led::SetState(bool i_bState) {
	this->GetOutputGPIO()->SetOutput(i_bState);
}

bool mkii::Led::GetState(void) { return this->GetOutputGPIO()->GetOutput(); }

void mkii::Led::Toggle() { this->GetOutputGPIO()->Toggle(); }

bool mkii::Led::IsBlinking() {
	if (mkii::event::Blink::GetBlink() == NULL) {
		return false;
	} else {
		return mkii::event::Blink::GetBlink()->IsBlinking();
	}
}

void mkii::Led::Blink(uint32_t i_u32BlinkCount, uint32_t i_u32TimerCount,
                      peripheral::Timer32* i_pTimer32) {
	mkii::event::Blink::GetBlink(i_u32BlinkCount, i_u32TimerCount, i_pTimer32,
	                             this)
	    ->Init();
}

peripheral::gpio::OutputGPIO* mkii::Led::GetOutputGPIO() {
	return this->m_pLedGPIO;
}