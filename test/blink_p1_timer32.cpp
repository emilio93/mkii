
#include <stdint.h>
#include <stdbool.h>

#include "driverlib.h"

#include <peripheral/Timer32.hpp>

#define LUNAV_LED_TIMER_COUNT 128000
#define LUNAV_LED_PIN GPIO_PIN0
#define LUNAV_LED_PORT GPIO_PORT_P1

peripheral::Timer32 timer(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_16BIT, TIMER32_PERIODIC_MODE);

void initLed(void) {
    MAP_GPIO_setAsOutputPin((uint_fast8_t) LUNAV_LED_PORT, (uint_fast16_t) LUNAV_LED_PIN);
}
void setLedHigh(void) {
    MAP_GPIO_setOutputLowOnPin(LUNAV_LED_PORT, LUNAV_LED_PIN);
}
void setLedLow(void) {
    MAP_GPIO_setOutputLowOnPin(LUNAV_LED_PORT, LUNAV_LED_PIN);
}
void toggleLed(void) {
    MAP_GPIO_toggleOutputOnPin(LUNAV_LED_PORT, LUNAV_LED_PIN);
}
void T32_INT1_IRQHandler(void)
{
    timer.ClearInterruptFlag();
    toggleLed();
}
void main(void)
{
	MAP_WDT_A_holdTimer();
	initLed();
	setLedHigh();

	timer.SetCounter(LUNAV_LED_TIMER_COUNT);
	timer.EnableInterrupt(true);
	timer.RegisterInterrupt(true, T32_INT1_IRQHandler);
	while(true){
	};
}
