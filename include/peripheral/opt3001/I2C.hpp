#ifndef MKII_PERIPHERAL_I2C_H
#define MKII_PERIPHERAL_I2C_H

#include "driverlib.h"

#include "peripheral/GPIO.hpp"
#include "peripheral/OPT3001.hpp"

namespace peripheral {

namespace opt3001 {

namespace i2c {

const eUSCI_I2C_MasterConfig i2cConfig = {
    EUSCI_B_I2C_CLOCKSOURCE_SMCLK,      // SMCLK Clock Source
    3000000,                            // SMCLK
    EUSCI_B_I2C_SET_DATA_RATE_400KBPS,  // Desired I2C Clock of 100khz
    0,                                  // No byte counter threshold
    EUSCI_B_I2C_NO_AUTO_STOP            // No Autostop
};

}  // namespace i2c

class I2C {
 public:
	/**
	 * Initialize gpios.
	 *
	 */
	I2C();
	void Init(void);
	uint16_t Read16(uint8_t i_u8Byte);
	void Write16(uint8_t i_u8Pointer, uint16_t i_iWriteByte);
	void SetSlave(unsigned int slaveAdr);
	bool IsBusy(void);

 private:
	peripheral::GPIO* m_pSCLGPIO;
	peripheral::GPIO* m_pSDAGPIO;
	peripheral::GPIO* m_pINTGPIO;

	uint32_t m_u32EusciBase;
};

}  // namespace opt3001

}  // namespace peripheral
#endif
