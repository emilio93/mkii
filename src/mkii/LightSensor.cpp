#include "mkii/LightSensor.hpp"

mkii::LightSensor::LightSensor() {
	this->m_pOPT3001 = new peripheral::OPT3001();
}

float mkii::LightSensor::GetLux() { return this->m_pOPT3001->GetLux(); }

peripheral::OPT3001* mkii::LightSensor::GetOPT3001() {
	return this->m_pOPT3001;
}
