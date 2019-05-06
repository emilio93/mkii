#ifndef MKII_PERIPHERAL_OPT3001_H_
#define MKII_PERIPHERAL_OPT3001_H_

#include <cstddef>

#include "driverlib.h"

#include "peripheral/opt3001/I2C.hpp"

namespace peripheral {

namespace opt3001 {
const uint16_t OPT3001_SLAVE_ADDRESS = 0x44;

const uint16_t OPT_INTERRUPT_PIN = 11;
const uint16_t RESULT_REG = 0x00;
const uint16_t CONFIG_REG = 0x01;
const uint16_t LOWLIMIT_REG = 0x02;
const uint16_t HIGHLIMIT_REG = 0x03;
const uint16_t MANUFACTUREID_REG = 0x7E;
const uint16_t DEVICEID_REG = 0x7F;

const uint32_t DEFAULT_CONFIG = 0xCC10;      // 800ms
const uint32_t DEFAULT_CONFIG_100 = 0xC410;  // 100ms
}  // namespace opt3001

class OPT3001 {
 public:
	OPT3001(void);
	void Init(void);
	unsigned long int GetLux(void);
	unsigned int ReadManufacturerId(void);
	unsigned int ReadDeviceId(void);
	unsigned int ReadConfigReg(void);
	unsigned int ReadLowLimitReg(void);
	unsigned int ReadHighLimitReg(void);

	peripheral::opt3001::I2C* GetI2C();

 private:
	peripheral::opt3001::I2C* m_pI2C;
};

}  // namespace peripheral

#endif /* MKII_PERIPHERAL_OPT3001_H_ */
