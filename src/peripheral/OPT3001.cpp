#include "peripheral/OPT3001.hpp"

peripheral::OPT3001::OPT3001() {
	this->m_pI2C = new peripheral::opt3001::I2C();
}

void peripheral::OPT3001::Init() {
	/* Specify slave address for OPT3001 */
	this->m_pI2C->SetSlave(peripheral::opt3001::OPT3001_SLAVE_ADDRESS);

	/* Set Default configuration for OPT3001*/
	this->m_pI2C->Write16(peripheral::opt3001::CONFIG_REG,
	                      peripheral::opt3001::DEFAULT_CONFIG_100);
}

unsigned int peripheral::OPT3001::ReadManufacturerId() {
	/* Specify slave address for OPT3001 */
	this->m_pI2C->SetSlave(peripheral::opt3001::OPT3001_SLAVE_ADDRESS);

	return this->m_pI2C->Read16(peripheral::opt3001::MANUFACTUREID_REG);
}
unsigned int peripheral::OPT3001::ReadDeviceId() {
	/* Specify slave address for OPT3001 */
	this->m_pI2C->SetSlave(peripheral::opt3001::OPT3001_SLAVE_ADDRESS);

	return this->m_pI2C->Read16(peripheral::opt3001::DEVICEID_REG);
}
unsigned int peripheral::OPT3001::ReadConfigReg() {
	/* Specify slave address for OPT3001 */
	this->m_pI2C->SetSlave(peripheral::opt3001::OPT3001_SLAVE_ADDRESS);

	return this->m_pI2C->Read16(peripheral::opt3001::CONFIG_REG);
}
unsigned int peripheral::OPT3001::ReadLowLimitReg() {
	/* Specify slave address for OPT3001 */
	this->m_pI2C->SetSlave(peripheral::opt3001::OPT3001_SLAVE_ADDRESS);

	return this->m_pI2C->Read16(peripheral::opt3001::LOWLIMIT_REG);
}
unsigned int peripheral::OPT3001::ReadHighLimitReg() {
	/* Specify slave address for OPT3001 */
	this->m_pI2C->SetSlave(peripheral::opt3001::OPT3001_SLAVE_ADDRESS);

	return this->m_pI2C->Read16(peripheral::opt3001::HIGHLIMIT_REG);
}
unsigned long int peripheral::OPT3001::GetLux() {
	/* Specify slave address for OPT3001 */
	this->m_pI2C->SetSlave(peripheral::opt3001::OPT3001_SLAVE_ADDRESS);

	uint16_t exponent = 0;
	uint32_t result = 0;
	int16_t raw;
	raw = this->m_pI2C->Read16(peripheral::opt3001::RESULT_REG);
	/*Convert to LUX*/
	// extract result & exponent data from raw readings
	result = raw & 0x0FFF;
	exponent = (raw >> 12) & 0x000F;
	// convert raw readings to LUX
	switch (exponent) {
		case 0:  //*0.015625
			result = result >> 6;
			break;
		case 1:  //*0.03125
			result = result >> 5;
			break;
		case 2:  //*0.0625
			result = result >> 4;
			break;
		case 3:  //*0.125
			result = result >> 3;
			break;
		case 4:  //*0.25
			result = result >> 2;
			break;
		case 5:  //*0.5
			result = result >> 1;
			break;
		case 6:
			result = result;
			break;
		case 7:  //*2
			result = result << 1;
			break;
		case 8:  //*4
			result = result << 2;
			break;
		case 9:  //*8
			result = result << 3;
			break;
		case 10:  //*16
			result = result << 4;
			break;
		case 11:  //*32
			result = result << 5;
			break;
	}
	return result;
}

peripheral::opt3001::I2C* peripheral::OPT3001::GetI2C() { return this->m_pI2C; }
