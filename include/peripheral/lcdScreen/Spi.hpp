#ifndef MKII_PERIPHERAL_LCDSCREEN_SPI_H_
#define MKII_PERIPHERAL_LCDSCREEN_SPI_H_

#include <cstddef>

#include "driverlib.h"

#include "peripheral/GPIO.hpp"
#include "peripheral/gpio/OutputGPIO.hpp"

// Custom __delay_cycles() for non CCS Compiler
#if !defined(__TI_ARM__)
#undef __delay_cycles
#define __delay_cycles(x) SysCtlDelay(x)
void SysCtlDelay(uint32_t);
#endif

#define delay(x) __delay_cycles(x * 48)

namespace peripheral {

namespace lcdScreen {

namespace spi {
// System clock speed (in Hz)
const uint32_t SYSTEM_CLOCK_SPEED = 48e6;
// SPI clock speed (in Hz)
const uint32_t SPI_CLOCK_SPEED = 16e6;

// Ports from MSP432 connected to LCD
const uint8_t SCK_PORT = peripheral::gpio::Port::PORT1;
const uint8_t SCK_PIN_FUNCTION = peripheral::gpio::ModuleFunction::PRIMARY;
const uint8_t MOSI_PORT = peripheral::gpio::Port::PORT1;
const uint8_t MOSI_PIN_FUNCTION = peripheral::gpio::ModuleFunction::PRIMARY;
const uint8_t RST_PORT = peripheral::gpio::Port::PORT5;
const uint8_t CS_PORT = peripheral::gpio::Port::PORT5;
const uint8_t DC_PORT = peripheral::gpio::Port::PORT3;

// Pins from MSP432 connected to LCD
const uint32_t SCK_PIN = peripheral::gpio::Pin::PIN5;
const uint32_t MOSI_PIN = peripheral::gpio::Pin::PIN6;
const uint32_t RST_PIN = peripheral::gpio::Pin::PIN7;
const uint32_t CS_PIN = peripheral::gpio::Pin::PIN0;
const uint32_t DC_PIN = peripheral::gpio::Pin::PIN7;
;

// Definition of USCI base address to be used for SPI communication
const uint32_t EUSCI_BASE = EUSCI_B0_BASE;
}  // namespace spi

class Spi {
 public:
	Spi();
	Spi(peripheral::GPIO* i_pSckGPIO, peripheral::GPIO* i_pMosiGPIO,
	    peripheral::gpio::OutputGPIO* i_pRstGPIO,
	    peripheral::gpio::OutputGPIO* i_pCsGPIO,
	    peripheral::gpio::OutputGPIO* i_pDcGPIO);

	void WriteCommand(uint8_t i_u8Command);
	void WriteData(uint8_t i_u8Data);
	void PortInit(void);
	void SpiInit(void);

	void SetSckGPIO(peripheral::GPIO* i_pSckGPIO);
	void SetMosiGPIO(peripheral::GPIO* i_pMosiGPIO);
	void SetRstGPIO(peripheral::gpio::OutputGPIO* i_pRstGPIO);
	void SetCsGPIO(peripheral::gpio::OutputGPIO* i_pCsGPIO);
	void SetDcGPIO(peripheral::gpio::OutputGPIO* i_pDcGPIO);

	peripheral::GPIO* GetSckGPIO(void);
	peripheral::GPIO* GetMosiGPIO(void);
	peripheral::gpio::OutputGPIO* GetRstGPIO(void);
	peripheral::gpio::OutputGPIO* GetCsGPIO(void);
	peripheral::gpio::OutputGPIO* GetDcGPIO(void);

 private:
	peripheral::GPIO* m_pSckGPIO;
	peripheral::GPIO* m_pMosiGPIO;
	peripheral::gpio::OutputGPIO* m_pRstGPIO;
	peripheral::gpio::OutputGPIO* m_pCsGPIO;
	peripheral::gpio::OutputGPIO* m_pDcGPIO;
};

}  // namespace lcdScreen

}  // namespace peripheral

#endif /* MKII_PERIPHERAL_LCDSCREEN_SPI_H_ */
