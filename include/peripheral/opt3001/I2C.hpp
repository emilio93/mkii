#ifndef MKII_PERIPHERAL_OPT3001_I2C_H_
#define MKII_PERIPHERAL_OPT3001_I2C_H_

#include <cstddef>

#include "driverlib.h"

namespace peripheral {

namespace opt3001 {

/* I2C Master Configuration Parameter */
const eUSCI_I2C_MasterConfig i2cConfig = {
    EUSCI_B_I2C_CLOCKSOURCE_SMCLK,      // SMCLK Clock Source
    48000000,                           // SMCLK = 48MHz
    EUSCI_B_I2C_SET_DATA_RATE_400KBPS,  // Desired I2C Clock of 100khz
    0,                                  // No byte counter threshold
    EUSCI_B_I2C_NO_AUTO_STOP            // No Autostop
};

class I2C {
 public:
	I2C();
	void Init_GPIO(void);
	void Init(void);
	int Read16(unsigned char i_cWriteByte);
	void Write16(unsigned char i_cPointer, unsigned int i_uWriteByte);
	void SetSlave(unsigned int i_uSlaveAdr);
};

}  // namespace opt3001

}  // namespace peripheral

#endif /* MKII_PERIPHERAL_OPT3001_I2C_H_ */
