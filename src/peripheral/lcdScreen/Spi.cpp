#include "peripheral/lcdScreen/Spi.hpp"

peripheral::lcdScreen::Spi::Spi() {
	this->SetSckGPIO(new peripheral::GPIO(peripheral::lcdScreen::spi::SCK_PORT,
	                                      peripheral::lcdScreen::spi::SCK_PIN));
	this->SetMosiGPIO(new peripheral::GPIO(peripheral::lcdScreen::spi::MOSI_PORT,
	                                       peripheral::lcdScreen::spi::MOSI_PIN));
	this->SetRstGPIO(
	    new peripheral::gpio::OutputGPIO(peripheral::lcdScreen::spi::RST_PORT,
	                                     peripheral::lcdScreen::spi::RST_PIN));
	this->SetCsGPIO(new peripheral::gpio::OutputGPIO(
	    peripheral::lcdScreen::spi::CS_PORT, peripheral::lcdScreen::spi::CS_PIN));
	this->SetDcGPIO(new peripheral::gpio::OutputGPIO(
	    peripheral::lcdScreen::spi::DC_PORT, peripheral::lcdScreen::spi::DC_PIN));
}

peripheral::lcdScreen::Spi::Spi(peripheral::GPIO* i_pSckGPIO,
                                peripheral::GPIO* i_pMosiGPIO,
                                peripheral::gpio::OutputGPIO* i_pRstGPIO,
                                peripheral::gpio::OutputGPIO* i_pCsGPIO,
                                peripheral::gpio::OutputGPIO* i_pDcGPIO) {
	this->SetSckGPIO(i_pRstGPIO);
	this->SetMosiGPIO(i_pMosiGPIO);
	this->SetRstGPIO(i_pRstGPIO);
	this->SetCsGPIO(i_pCsGPIO);
	this->SetDcGPIO(i_pDcGPIO);
}

void peripheral::lcdScreen::Spi::WriteCommand(uint8_t i_u8Command) {
	// Set to command mode
	this->GetDcGPIO()->SetOutput(false);

	// USCI_B0 Busy? //
	while (UCB0STATW & UCBUSY)
		;

	// Transmit data
	UCB0TXBUF = i_u8Command;

	// USCI_B0 Busy? //
	while (UCB0STATW & UCBUSY)
		;

	// Set back to data mode
	this->GetDcGPIO()->SetOutput(true);
}

void peripheral::lcdScreen::Spi::WriteData(uint8_t i_u8Data) {
	// USCI_B0 Busy? //
	while (UCB0STATW & UCBUSY)
		;

	// Transmit data
	UCB0TXBUF = i_u8Data;

	// USCI_B0 Busy? //
	while (UCB0STATW & UCBUSY)
		;
}

void peripheral::lcdScreen::Spi::PortInit(void) {
	// LCD_SCK
	this->GetSckGPIO()->SetAsPeripheralModuleFunctionOutput(
	    peripheral::lcdScreen::spi::SCK_PIN_FUNCTION);
	// LCD_MOSI
	this->GetMosiGPIO()->SetAsPeripheralModuleFunctionOutput(
	    peripheral::lcdScreen::spi::MOSI_PIN_FUNCTION);
}

void peripheral::lcdScreen::Spi::SpiInit(void) {
	eUSCI_SPI_MasterConfig config = {
	    EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
	    peripheral::lcdScreen::spi::SYSTEM_CLOCK_SPEED,
	    peripheral::lcdScreen::spi::SPI_CLOCK_SPEED,
	    EUSCI_B_SPI_MSB_FIRST,
	    EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
	    EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW,
	    EUSCI_B_SPI_3PIN};
	SPI_initMaster(peripheral::lcdScreen::spi::EUSCI_BASE, &config);
	SPI_enableModule(peripheral::lcdScreen::spi::EUSCI_BASE);

	this->GetCsGPIO()->SetOutput(false);
	this->GetDcGPIO()->SetOutput(true);
}

void peripheral::lcdScreen::Spi::SetSckGPIO(peripheral::GPIO* i_pSckGPIO) {
	this->m_pSckGPIO = i_pSckGPIO;
}
void peripheral::lcdScreen::Spi::SetMosiGPIO(peripheral::GPIO* i_pMosiGPIO) {
	this->m_pMosiGPIO = i_pMosiGPIO;
}
void peripheral::lcdScreen::Spi::SetRstGPIO(
    peripheral::gpio::OutputGPIO* i_pRstGPIO) {
	this->m_pRstGPIO = i_pRstGPIO;
}
void peripheral::lcdScreen::Spi::SetCsGPIO(
    peripheral::gpio::OutputGPIO* i_pCsGPIO) {
	this->m_pCsGPIO = i_pCsGPIO;
}
void peripheral::lcdScreen::Spi::SetDcGPIO(
    peripheral::gpio::OutputGPIO* i_pDcGPIO) {
	this->m_pDcGPIO = i_pDcGPIO;
}

peripheral::GPIO* peripheral::lcdScreen::Spi::GetSckGPIO(void) {
	return this->m_pSckGPIO;
}
peripheral::GPIO* peripheral::lcdScreen::Spi::GetMosiGPIO(void) {
	return this->m_pMosiGPIO;
}
peripheral::gpio::OutputGPIO* peripheral::lcdScreen::Spi::GetRstGPIO(void) {
	return this->m_pRstGPIO;
}
peripheral::gpio::OutputGPIO* peripheral::lcdScreen::Spi::GetCsGPIO(void) {
	return this->m_pCsGPIO;
}
peripheral::gpio::OutputGPIO* peripheral::lcdScreen::Spi::GetDcGPIO(void) {
	return this->m_pDcGPIO;
}
