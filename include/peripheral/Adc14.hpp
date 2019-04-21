
#ifndef MKII_PERIPHERAL_ADC14_H
#define MKII_PERIPHERAL_ADC14_H

#include "driverlib.h"

namespace peripheral {

typedef uint32_t mkii_adc14;

enum MaxConvertionValue = {SingleEndedMode = 16384, DifferentialMode = 8192};

enum AnalogInputDevice = {
    JOYSTICK_HOR_X,    JOYSTICK_VER_Y, ACCELEREROMETER_X, ACCELEREROMETER_Y,
    ACCELEREROMETER_Z, MICROPHONE,     TEMP_SENSOR,       AMBIENT_LIGHT};

class Adc14 {
 public:
	Adc14(uint32_t i_u32ClockSource, uint32_t i_u32ClockPredivider,
	      uint32_t i_u32ClockDivider, uint32_t i_u32InternalChannelMask);
	~Adc14();

	void SetResolution(uint32_t i_u32Resolution);
	uint_fast32_t GetResolution(void);
	void waitForAdcModule(void);
	void SetInterruptMask(uint_fast64_t i_uf64InterruptMask);
	void EnableAndRegisterInterrupt(void (*i_funcInterruptHandler)(void) = 0);
	void ClearInterruptMask(void);

 private:
	bool m_bHasInterrupt;
	uint_fast64_t m_uf64InterruptMask;
};

}  // namespace peripheral

#endif /* MKII_PERIPHERAL_ADC14_H */
