#include "mkii/Accelerometer.hpp"
uint16_t mkii::Accelerometer::m_u16X = 0;
uint16_t mkii::Accelerometer::m_u16Y = 0;
uint16_t mkii::Accelerometer::m_u16Z = 0;

mkii::Accelerometer::Accelerometer() {
	this->m_pAdc14 = new peripheral::Adc14(
	    peripheral::adc14::AnalogInputDevice::ACCELEREROMETER);
	this->m_pAdc14->ConfigureDevice();
}

void mkii::Accelerometer::TriggerConversion(void) {
	this->m_pAdc14->TriggerSignalConversion();
}

void mkii::Accelerometer::UpdateResults(void) {
	this->setX(ADC14_getResult(ADC_MEM0));
	this->setY(ADC14_getResult(ADC_MEM1));
	this->setZ(ADC14_getResult(ADC_MEM2));
}

uint16_t mkii::Accelerometer::GetX(void) { return mkii::Accelerometer::m_u16X; }
uint16_t mkii::Accelerometer::GetY(void) { return mkii::Accelerometer::m_u16Y; }
uint16_t mkii::Accelerometer::GetZ(void) { return mkii::Accelerometer::m_u16Z; }


void mkii::Accelerometer::setX(uint16_t i_u16X) {
	mkii::Accelerometer::m_u16X = i_u16X;
}
void mkii::Accelerometer::setY(uint16_t i_u16Y) {
	mkii::Accelerometer::m_u16Y = i_u16Y;
}
void mkii::Accelerometer::setZ(uint16_t i_u16Z) {
	mkii::Accelerometer::m_u16Z = i_u16Z;
}
