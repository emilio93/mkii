
#include <stdbool.h>
#include <stdint.h>

#include "driverlib.h"

#include <peripheral/Adc14.hpp>

peripheral::Adc14 converter(ADC_CLOCKSOURCE_ADCOSC,
							ADC_PREDIVIDER_1,
							ADC_DIVIDER_1,
							ADC_MAPINTCH0);

void main(void) {
	MAP_WDT_A_holdTimer();
	while (true) {
	};
}
