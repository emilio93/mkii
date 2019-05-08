#ifndef MKII_MKII_LIGHTSENSOR_H
#define MKII_MKII_LIGHTSENSOR_H

#include <cstddef>

#include "peripheral/OPT3001.hpp"
#include "peripheral/opt3001/I2C.hpp"

namespace mkii {

/**
 * A light sensor can read its measurement in lux units.
 *
 */
class LightSensor {
 public:
	/**
	 * @brief Construct a new Light Sensor object initializing the OPT3001 object.
	 *
	 */
	LightSensor();

	/**
	 * Sets up the i2c communication scheme.
	 *
	 */
	void Init();

	/**
	 * Obtain the measurement in lux units.
	 *
	 * @return float Th measurement in lux units.
	 */
	float GetLux();

 private:
	/**
	 * The OPT3001 device used in the implementation.
	 *
	 */
	peripheral::OPT3001* m_pOPT3001;

	/**
	 * Opbtain the OPT3001 device object.
	 *
	 * @return peripheral::OPT3001* The device object.
	 */
	peripheral::OPT3001* GetOPT3001();
};

}  // namespace mkii

#endif /* MKII_MKII_LIGHTSENSOR_H */
