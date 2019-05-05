
#ifndef MKII_PERIPHERAL_OPT3001_H
#define MKII_PERIPHERAL_OPT3001_H

#include "driverlib.h"

#include "peripheral/GPIO.hpp"
#include "peripheral/opt3001/I2C.hpp"

namespace peripheral {

namespace opt3001 {

const uint8_t SCL_PORT = peripheral::gpio::PORT6;
const uint16_t SCL_PIN = peripheral::gpio::PIN5;

const uint8_t SDA_PORT = peripheral::gpio::PORT6;
const uint16_t SDA_PIN = peripheral::gpio::PIN4;

const uint8_t INT_PORT = peripheral::gpio::PORT4;
const uint16_t INT_PIN = peripheral::gpio::PIN6;

const uint8_t SLAVE_ADDRESS = 0x44;

const uint8_t OPT_INTERRUPT_PIN = 11;
const uint8_t RESULT_REG = 0x00;
const uint8_t CONFIG_REG = 0x01;
const uint8_t LOWLIMIT_REG = 0x02;
const uint8_t HIGHLIMIT_REG = 0x03;
const uint8_t MANUFACTUREID_REG = 0x7E;
const uint8_t DEVICEID_REG = 0x7F;

const uint16_t DEFAULT_CONFIG_800 = 0xCC10;  // 800ms
const uint16_t DEFAULT_CONFIG_100 = 0xC410;  // 100ms

class I2C;

}  // namespace opt3001

class OPT3001 {
 public:
	OPT3001();
	float GetLux(void);

	uint16_t ReadManufacturerId(void);

	uint16_t ReadDeviceId(void);

	uint16_t ReadResult(void);

	uint16_t ReadConfig(void);
	void WriteConfig(uint16_t i_u16Value);

	uint16_t ReadLowLimit(void);

	uint16_t ReadHighLimit(void);

	peripheral::opt3001::I2C* GetI2C();

 private:
	peripheral::opt3001::I2C* m_pSlaveI2C;
};

}  // namespace peripheral
#endif /* MKII_PERIPHERAL_OPT3001_H */
