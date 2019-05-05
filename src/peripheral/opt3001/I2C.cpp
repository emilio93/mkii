#include "peripheral/opt3001/I2C.hpp"

peripheral::opt3001::I2C::I2C() {
	this->m_pSCLGPIO = new peripheral::GPIO(
	    peripheral::opt3001::SCL_PORT, peripheral::opt3001::SCL_PIN,
	    peripheral::gpio::Mode::PERIPHERAL_MODULE_FUNCTION_OUTPUT,
	    peripheral::gpio::ModuleFunction::PRIMARY);
	this->m_pSDAGPIO = new peripheral::GPIO(
	    peripheral::opt3001::SDA_PORT, peripheral::opt3001::SDA_PIN,
	    peripheral::gpio::Mode::PERIPHERAL_MODULE_FUNCTION_OUTPUT,
	    peripheral::gpio::ModuleFunction::PRIMARY);
	this->m_pINTGPIO = new peripheral::GPIO(peripheral::opt3001::INT_PORT,
	                                        peripheral::opt3001::INT_PIN);

	this->m_u32EusciBase = EUSCI_B1_BASE;
}

void peripheral::opt3001::I2C::Init(void) {
	I2C_initMaster(this->m_u32EusciBase, &peripheral::opt3001::i2c::i2cConfig);
	I2C_disableModule(this->m_u32EusciBase);
	I2C_enableModule(this->m_u32EusciBase);
	return;
}

uint16_t peripheral::opt3001::I2C::Read16(uint8_t i_u8Byte) {
	int l_iVal = 0;
	int l_iValScratch = 0;
	bool l_bContinueFlag = false;
	I2C_setMode(this->m_u32EusciBase, EUSCI_B_I2C_TRANSMIT_MODE);
	I2C_clearInterruptFlag(this->m_u32EusciBase, EUSCI_B_I2C_TRANSMIT_INTERRUPT0);
	while (I2C_isBusBusy(this->m_u32EusciBase)) {
		;
	}
	I2C_masterSendMultiByteStart(this->m_u32EusciBase, i_u8Byte);
	l_bContinueFlag = false;
	while (!l_bContinueFlag) {
		l_bContinueFlag = I2C_getInterruptStatus(this->m_u32EusciBase,
		                                         EUSCI_B_I2C_TRANSMIT_INTERRUPT0);
	}
	I2C_masterSendMultiByteStop(this->m_u32EusciBase);
	while (!I2C_getInterruptStatus(this->m_u32EusciBase,
	                               EUSCI_B_I2C_STOP_INTERRUPT)) {
		;
	}
	I2C_masterReceiveStart(this->m_u32EusciBase);
	l_bContinueFlag = false;
	while (!l_bContinueFlag) {
		l_bContinueFlag = I2C_getInterruptStatus(this->m_u32EusciBase,
		                                         EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	}
	l_iVal = I2C_masterReceiveMultiByteNext(this->m_u32EusciBase);
	l_iValScratch = I2C_masterReceiveMultiByteFinish(this->m_u32EusciBase);
	l_iVal = (l_iVal << 8);
	l_iVal |= l_iValScratch;
	return (int16_t)l_iVal;
}

void peripheral::opt3001::I2C::Write16(uint8_t i_u8Pointer,
                                       uint16_t i_u16WriteByte) {
	I2C_setMode(this->m_u32EusciBase, EUSCI_B_I2C_TRANSMIT_MODE);
	I2C_clearInterruptFlag(this->m_u32EusciBase, EUSCI_B_I2C_TRANSMIT_INTERRUPT0);
	while (this->IsBusy()) {
		;
	}
	I2C_masterSendMultiByteStart(this->m_u32EusciBase, i_u8Pointer);
	I2C_masterSendMultiByteNext(this->m_u32EusciBase,
	                            (unsigned char)(i_u16WriteByte >> 8));
	I2C_masterSendMultiByteFinish(this->m_u32EusciBase,
	                              (unsigned char)(i_u16WriteByte & 0xFF));
}

void peripheral::opt3001::I2C::SetSlave(unsigned int i_iSlaveAdr) {
	I2C_setSlaveAddress(this->m_u32EusciBase, i_iSlaveAdr);
	I2C_clearInterruptFlag(
	    this->m_u32EusciBase,
	    EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	return;
}

bool peripheral::opt3001::I2C::IsBusy() {
	return I2C_isBusBusy(this->m_u32EusciBase);
}
