#include "mkii/Accelerometer.hpp"

mkii::Accelerometer::Accelerometer() {
	this->m_pAdc14 = new peripheral::Adc14(
	    peripheral::adc14::AnalogInputDevice::ACCELEREROMETER);
	this->m_pAdc14->ConfigureDevice();
}

void mkii::Accelerometer::TriggerConversion(void) {
	this->m_pAdc14->TriggerSignalConversion();
}
