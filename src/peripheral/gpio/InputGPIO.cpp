#include <iostream>

#include "driverlib.h"

#include "peripheral/gpio/InputGPIO.hpp"

peripheral::gpio::InputGPIO::InputGPIO(uint8_t i_u8Port, uint32_t i_u32Pin)
    : peripheral::GPIO(i_u8Port, i_u32Pin) {
      this->SetAsInput();
}

bool peripheral::gpio::InputGPIO::ReadValue() {
  GPIO_getInputPinValue(this->GetPort(), this->GetPin());
}