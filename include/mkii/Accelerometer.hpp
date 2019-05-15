#ifndef MKII_MKII_ACCELEROMETER_H
#define MKII_MKII_ACCELEROMETER_H

#include <cstddef>

#include "peripheral/Adc14.hpp"

namespace mkii {

class Accelerometer {
 public:
	Accelerometer();

	void TriggerConversion(void);

 private:
	peripheral::Adc14* m_pAdc14;
};

}  // namespace mkii

#endif /* MKII_MKII_ACCELEROMETER_H */
