#ifndef MKII_MKII_ACCELEROMETER_H
#define MKII_MKII_ACCELEROMETER_H

#include <cstddef>

#include "peripheral/Adc14.hpp"

namespace mkii {

class Accelerometer {
 public:
	Accelerometer();

	void TriggerConversion(void);
	void UpdateResults(void);
 	static uint16_t GetX(void);
	static uint16_t GetY(void);
	static uint16_t GetZ(void);

 private:
 	static uint16_t m_u16X;
	static uint16_t m_u16Y;
	static uint16_t m_u16Z;
 	peripheral::Adc14* m_pAdc14;
};

}  // namespace mkii

#endif /* MKII_MKII_ACCELEROMETER_H */
