#include "peripheral/OPT3001.hpp"

peripheral::OPT3001::OPT3001() {
	this->m_pI2C = new peripheral::opt3001::I2C();
}

void peripheral::OPT3001::Init() {
	this->GetI2C()->Init_GPIO();
	this->GetI2C()->Init();

	this->WriteReg(peripheral::opt3001::CONFIG_REG,
	               peripheral::opt3001::DEFAULT_CONFIG_100);
}

unsigned int peripheral::OPT3001::ReadManufacturerId() {
	return this->ReadReg(peripheral::opt3001::MANUFACTUREID_REG);
}

unsigned int peripheral::OPT3001::ReadDeviceId() {
	return this->ReadReg(peripheral::opt3001::DEVICEID_REG);
}

unsigned int peripheral::OPT3001::ReadConfigReg() {
	return this->ReadReg(peripheral::opt3001::CONFIG_REG);
}

unsigned int peripheral::OPT3001::ReadLowLimitReg() {
	return this->ReadReg(peripheral::opt3001::LOWLIMIT_REG);
}

unsigned int peripheral::OPT3001::ReadHighLimitReg() {
	return this->ReadReg(peripheral::opt3001::HIGHLIMIT_REG);
}

unsigned long int peripheral::OPT3001::GetLux() {
	uint16_t exponent = 0;
	uint32_t result = 0;
	int16_t raw;
	raw = this->ReadReg(peripheral::opt3001::RESULT_REG);
	/*Convert to LUX*/
	// extract result & exponent data from raw readings
	result = raw & 0x0FFF;
	exponent = (raw >> 12) & 0x000F;
	// convert raw readings to LUX
	// clang-format off
	switch (exponent) {
		case 0:  result = result >> 6; break; // *0.015625
		case 1:  result = result >> 5; break; // *0.03125
		case 2:  result = result >> 4; break; // *0.0625
		case 3:  result = result >> 3; break; // *0.125
		case 4:  result = result >> 2; break; //*0.25
		case 5:  result = result >> 1; break; // *0.5
		case 6:  result = result; break;
		case 7:  result = result << 1; break; // *2
		case 8:  result = result << 2; break; // *4
		case 9:  result = result << 3; break; // *8
		case 10: result = result << 4; break; // *16
		case 11: result = result << 5; break; // *32
	}
	// clang-format on
	return result;
}

peripheral::opt3001::I2C* peripheral::OPT3001::GetI2C() { return this->m_pI2C; }

unsigned int peripheral::OPT3001::ReadReg(uint16_t i_u16Reg) {
	this->GetI2C()->SetSlave(peripheral::opt3001::OPT3001_SLAVE_ADDRESS);
	return this->GetI2C()->Read16(i_u16Reg);
}

void peripheral::OPT3001::WriteReg(uint16_t i_u16Reg, unsigned int i_uValue) {
	this->GetI2C()->SetSlave(peripheral::opt3001::OPT3001_SLAVE_ADDRESS);
	this->GetI2C()->Write16(i_u16Reg, i_uValue);
}
