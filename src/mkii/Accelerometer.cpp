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
	mkii::Accelerometer::m_u16X = ADC14_getResult(ADC_MEM0);
	mkii::Accelerometer::m_u16Y = ADC14_getResult(ADC_MEM1);
	mkii::Accelerometer::m_u16Z = ADC14_getResult(ADC_MEM2);
}

uint16_t mkii::Accelerometer::GetX(void) {
	return mkii::Accelerometer::m_u16X;
}
uint16_t mkii::Accelerometer::GetY(void) {
	return mkii::Accelerometer::m_u16Y;
}
uint16_t mkii::Accelerometer::GetZ(void) {
	return mkii::Accelerometer::m_u16Z;
}