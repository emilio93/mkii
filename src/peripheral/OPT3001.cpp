#include "peripheral/OPT3001.hpp"

peripheral::OPT3001::OPT3001() {
	this->m_pSlaveI2C = new peripheral::opt3001::I2C();
	this->m_pSlaveI2C->Init();

	this->WriteConfig(peripheral::opt3001::DEFAULT_CONFIG_100);
}

float peripheral::OPT3001::GetLux(void) {
	uint16_t l_u16Exponent = 0;
	uint32_t l_u16Result = 0;
	int16_t l_i16Raw;
	l_i16Raw = this->ReadResult();
	l_u16Result = l_i16Raw & 0x0FFF;
	l_u16Exponent = (l_i16Raw >> 12) & 0x000F;

	// clang-format off
	switch(l_u16Exponent){
		case 0:  l_u16Result = l_u16Result>>6; break; // *0.015625
		case 1:  l_u16Result = l_u16Result>>5; break; // *0.03125
		case 2:  l_u16Result = l_u16Result>>4; break; // *0.0625
		case 3:  l_u16Result = l_u16Result>>3; break; // *0.125
		case 4:  l_u16Result = l_u16Result>>2; break; // *0.25
		case 5:  l_u16Result = l_u16Result>>1; break; // *0.5
		case 6:  l_u16Result = l_u16Result;    break;
		case 7:  l_u16Result = l_u16Result<<1; break; // *2
		case 8:  l_u16Result = l_u16Result<<2; break; // *4
		case 9:  l_u16Result = l_u16Result<<3; break; // *8
		case 10: l_u16Result = l_u16Result<<4; break; // *16
		case 11: l_u16Result = l_u16Result<<5; break; // *32
	}
	// clang-format on

	return l_u16Result;
}

uint16_t peripheral::OPT3001::ReadManufacturerId(void) {
	this->m_pSlaveI2C->SetSlave(peripheral::opt3001::SLAVE_ADDRESS);
	return this->m_pSlaveI2C->Read16(peripheral::opt3001::MANUFACTUREID_REG);
}

uint16_t peripheral::OPT3001::ReadDeviceId(void) {
	this->m_pSlaveI2C->SetSlave(peripheral::opt3001::SLAVE_ADDRESS);
	return this->m_pSlaveI2C->Read16(peripheral::opt3001::DEVICEID_REG);
}

uint16_t peripheral::OPT3001::ReadResult(void) {
	this->m_pSlaveI2C->SetSlave(peripheral::opt3001::SLAVE_ADDRESS);
	return this->m_pSlaveI2C->Read16(peripheral::opt3001::RESULT_REG);
}

uint16_t peripheral::OPT3001::ReadConfig(void) {
	this->m_pSlaveI2C->SetSlave(peripheral::opt3001::SLAVE_ADDRESS);
	return this->m_pSlaveI2C->Read16(peripheral::opt3001::HIGHLIMIT_REG);
}
void peripheral::OPT3001::WriteConfig(uint16_t i_u16Value) {
	this->m_pSlaveI2C->SetSlave(peripheral::opt3001::SLAVE_ADDRESS);
	this->m_pSlaveI2C->Write16(peripheral::opt3001::CONFIG_REG, i_u16Value);
}

uint16_t peripheral::OPT3001::ReadLowLimit(void) {
	this->m_pSlaveI2C->SetSlave(peripheral::opt3001::SLAVE_ADDRESS);
	return this->m_pSlaveI2C->Read16(peripheral::opt3001::LOWLIMIT_REG);
}

uint16_t peripheral::OPT3001::ReadHighLimit(void) {
	this->m_pSlaveI2C->SetSlave(peripheral::opt3001::SLAVE_ADDRESS);
	return this->m_pSlaveI2C->Read16(peripheral::opt3001::LOWLIMIT_REG);
}

peripheral::opt3001::I2C* peripheral::OPT3001::GetI2C() {
	return this->m_pSlaveI2C;
}