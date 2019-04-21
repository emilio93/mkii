
#ifndef MKII_PERIPHERAL_ADC14_H
#define MKII_PERIPHERAL_ADC14_H

#include "driverlib.h"

namespace peripheral {

enum MaxConvertionValue { SingleEndedMode = 16384, DifferentialMode = 8192 };

enum AnalogInputDevice {
	NONE,
	JOYSTICK_HOR_X,
	JOYSTICK_VER_Y,
	ACCELEREROMETER_X,
	ACCELEREROMETER_Y,
	ACCELEREROMETER_Z,
	MICROPHONE,
	TEMP_SENSOR,
	AMBIENT_LIGHT
};

class Adc14 {
 public:
	uint_fast64_t m_uf64InterruptMask;

	Adc14(uint32_t i_u32ClockSource, uint32_t i_u32ClockPredivider,
	      uint32_t i_u32ClockDivider, uint32_t i_u32InternalChannelMask);
	~Adc14();

	void waitForAdcModule(void);
	void SetResolution(const uint32_t i_u32Resolution);
	void SetSimpleSampleMode(const bool i_bRepeat);
	uint_fast16_t GetSimpleSampleModeResult(void);
	void SetAnalogMeasureDevice(
	    const peripheral::AnalogInputDevice i_eAnalogMeasure);

	// Return true if the memory configuration is success
	bool ConfigureDeviceMemory(const uint32_t i_u32VoltageRef);
	void SetSampleManualTimer(void);
	void SetSampleAutmaticTimer(void);
	void JustTriggerConvertion(void);
	void EnableAndTriggerConvertion(void);
	uint_fast32_t GetResolution(void);
	void EnableAndRegisterInterrupt(void (*i_funcInterruptHandler)(void) = 0);
	void ClearInterruptMask(void);
	uint_fast64_t GetInterruptStatus(void);

 private:
	bool m_bHasInterrupt;
	uint32_t m_u32SimpleMemoryMap;
	peripheral::AnalogInputDevice m_u32AnalogMeasureDevice;

	void SetMemoryMap(const uint32_t i_u32MemoryMap);
	void SetInterruptMask(const uint_fast64_t i_uf64InterruptMask);
};

}  // namespace peripheral

#endif /* MKII_PERIPHERAL_ADC14_H */
