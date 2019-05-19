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
	/**
	 * Construct the object with default values.
	 *
	 */
	Spi();

	/**
	 * Constructs the object with given parameters.
	 *
	 * @param i_pSckGPIO GPIO for the Sck.
	 * @param i_pMosiGPIO GPIO for the Mosi.
	 * @param i_pRstGPIO GPIO for the Rst.
	 * @param i_pCsGPIO GPIO for the Cs.
	 * @param i_pDcGPIO GPIO for the Dc.
	 */
	Spi(peripheral::GPIO* i_pSckGPIO, peripheral::GPIO* i_pMosiGPIO,
	    peripheral::gpio::OutputGPIO* i_pRstGPIO,
	    peripheral::gpio::OutputGPIO* i_pCsGPIO,
	    peripheral::gpio::OutputGPIO* i_pDcGPIO);

	void WriteCommand(uint8_t i_u8Command);
	void WriteData(uint8_t i_u8Data);
	void PortInit(void);
	void SpiInit(void);

	/**
	 * @brief Set the SckGPIO object.
	 *
	 * @param i_pSckGPIO The SckGPIO object.
	 */
	void SetSckGPIO(peripheral::GPIO* i_pSckGPIO);

	/**
	 * @brief Set the MosiGPIO object.
	 *
	 * @param i_pMosiGPIO The MosiGPIO object.
	 */
	void SetMosiGPIO(peripheral::GPIO* i_pMosiGPIO);

	/**
	 * @brief Set the RstGPIO object.
	 *
	 * @param i_pRstGPIO The RstGPIO object.
	 */
	void SetRstGPIO(peripheral::gpio::OutputGPIO* i_pRstGPIO);

	/**
	 * @brief Set the CsGPIO object.
	 *
	 * @param i_pCsGPIO The CsGPIO object.
	 */
	void SetCsGPIO(peripheral::gpio::OutputGPIO* i_pCsGPIO);

	/**
	 * @brief Set the DcGPIO object.
	 *
	 * @param i_pDcGPIO The DcGPIO object.
	 */
	void SetDcGPIO(peripheral::gpio::OutputGPIO* i_pDcGPIO);

	/**
	 * @brief Get the SckGPIO object.
	 *
	 * @return peripheral::GPIO* The SckGPIO object.
	 */
	peripheral::GPIO* GetSckGPIO(void);

	/**
	 * @brief Get the MosiGPIO object.
	 *
	 * @return peripheral::GPIO* The MosiGPIO object.
	 */
	peripheral::GPIO* GetMosiGPIO(void);

	/**
	 * @brief Get the RstGPIO object.
	 *
	 * @return peripheral::gpio::OutputGPIO* The RstGPIO object.
	 */
	peripheral::gpio::OutputGPIO* GetRstGPIO(void);

	/**
	 * @brief Get the CsGPIO object.
	 *
	 * @return peripheral::gpio::OutputGPIO* The CsGPIO object.
	 */
	peripheral::gpio::OutputGPIO* GetCsGPIO(void);

	/**
	 * @brief Get the DcGPIO object.
	 *
	 * @return peripheral::gpio::OutputGPIO* The DcGPIO object.
	 */
	peripheral::gpio::OutputGPIO* GetDcGPIO(void);

 private:
	/**
	 * @brief GPIO for the Sck.
	 *
	 */
	peripheral::GPIO* m_pSckGPIO;

	/**
	 * @brief GPIO for the Mosi.
	 *
	 */
	peripheral::GPIO* m_pMosiGPIO;

	/**
	 * @brief GPIO for the Rst.
	 *
	 */
	peripheral::gpio::OutputGPIO* m_pRstGPIO;

	/**
	 * @brief GPIO for the Cs.
	 *
	 */
	peripheral::gpio::OutputGPIO* m_pCsGPIO;

	/**
	 * @brief GPIO for the Dc.
	 *
	 */
	peripheral::gpio::OutputGPIO* m_pDcGPIO;
};

}  // namespace lcdScreen

}  // namespace peripheral

#endif /* MKII_PERIPHERAL_LCDSCREEN_SPI_H_ */
