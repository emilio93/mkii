#ifndef MKII_MKII_LIGHTSENSOR_H
#define MKII_MKII_LIGHTSENSOR_H

#include <cstddef>

#include "peripheral/OPT3001.hpp"
#include "peripheral/opt3001/I2C.hpp"

namespace mkii {

class LightSensor {
 public:
	LightSensor();
	float GetLux();

 private:
	peripheral::OPT3001* m_pOPT3001;
	peripheral::OPT3001* GetOPT3001();
};

}  // namespace mkii

#endif /* MKII_MKII_LIGHTSENSOR_H */
