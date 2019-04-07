
#include "driverlib.h"
#include "mkii_tim32.hpp"
#include <stdint.h>
#include <stdbool.h>

#define LUNAV_LED_TIMER_COUNT 128000
#define LUNAV_LED_PIN GPIO_PIN0
#define LUNAV_LED_PORT GPIO_PORT_P1

Timer32 timer(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_16BIT, TIMER32_PERIODIC_MODE);

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
    timer.ClearInterruptionFlag();
    toggleLed();
}
void main(void)
{
	MAP_WDT_A_holdTimer();
	initLed();
	setLedHigh();

	timer.SetCounter(LUNAV_LED_TIMER_COUNT);
	timer.EnableInterruption(true);
	timer.RegisterInterruption(true, T32_INT1_IRQHandler);
	while(true){
	};
}
