#include "mkii/LightSensor.hpp"

mkii::LightSensor::LightSensor() {
	this->m_pOPT3001 = new peripheral::OPT3001();
}

void mkii::LightSensor::Init() {
	this->GetOPT3001()->GetI2C()->Init_GPIO();
	this->GetOPT3001()->GetI2C()->Init();
	this->GetOPT3001()->Init();
	__delay_cycles(100000);
}

float mkii::LightSensor::GetLux() { return this->m_pOPT3001->GetLux(); }

peripheral::OPT3001* mkii::LightSensor::GetOPT3001() {
	return this->m_pOPT3001;
}
