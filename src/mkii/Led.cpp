#include "mkii/Led.hpp"

mkii::Led::Led() {
	this->m_pLedGPIO =
	    new peripheral::gpio::OutputGPIO(mkii::LED_PORT, mkii::LED_PIN);
}

void mkii::Led::SetState(bool i_bState, bool i_bSetTimeout) {
	this->GetOutputGPIO()->SetOutput(i_bState);
	if (i_bState && i_bSetTimeout &&
	    mkii::event::LedTimeout::GetLedTimeout() != NULL) {
		mkii::event::LedTimeout::GetLedTimeout()->Init();
	} else if (!i_bState && i_bSetTimeout && mkii::event::LedTimeout::GetLedTimeout() != NULL &&
	           mkii::event::LedTimeout::GetLedTimeout()->IsTimeoutOn()) {
		mkii::event::LedTimeout::GetLedTimeout()->End();
	}
}

bool mkii::Led::GetState(void) { return this->GetOutputGPIO()->GetOutput(); }

void mkii::Led::Toggle(bool i_bSetTimeout) {
	this->SetState(!this->GetState(), i_bSetTimeout);
}

bool mkii::Led::IsBlinking() {
	if (mkii::event::Blink::GetBlink() == NULL) {
		return false;
	} else {
		return mkii::event::Blink::GetBlink()->IsBlinking();
	}
}

void mkii::Led::SetInterruptDirection(peripheral::gpio::Edge i_eEdge) {
	this->GetOutputGPIO()->InterruptEdgeSelect(i_eEdge);
}

void mkii::Led::SetInterrupt(void (*i_funcHandler)(void)) {
	peripheral::GPIO::RegisterInterrupt(this->GetOutputGPIO(), i_funcHandler);
	this->GetOutputGPIO()->EnableInterrupt();
}

void mkii::Led::EndInterrupt() {
	this->GetOutputGPIO()->ClearInterruptFlag();
	peripheral::GPIO::UnregisterInterrupt(this->GetOutputGPIO());
	this->GetOutputGPIO()->DisableInterrupt();
}

void mkii::Led::Blink(uint32_t i_u32BlinkCount, uint32_t i_u32TimerCount,
                      mkii::Timer* i_pTimer) {
	mkii::event::Blink::GetBlink(i_u32BlinkCount, i_u32TimerCount, i_pTimer, this)
	    ->Init();
}

peripheral::gpio::OutputGPIO* mkii::Led::GetOutputGPIO() {
	return this->m_pLedGPIO;
}
