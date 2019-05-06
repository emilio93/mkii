#include "peripheral/opt3001/I2C.hpp"

peripheral::opt3001::I2C::I2C() { ; }

void peripheral::opt3001::I2C::Init_GPIO() {
	/* Select I2C function for I2C_SCL(P6.5) & I2C_SDA(P6.4) */
	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN5,
	                                                GPIO_PRIMARY_MODULE_FUNCTION);

	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN4,
	                                                GPIO_PRIMARY_MODULE_FUNCTION);
}

/***************************************************************************/ /**
                                                                               * @brief  Configures I2C
                                                                               * @param  none
                                                                               * @return none
                                                                               ******************************************************************************/

void peripheral::opt3001::I2C::Init(void) {
	/* Initialize USCI_B0 and I2C Master to communicate with slave devices*/
	MAP_I2C_initMaster(EUSCI_B1_BASE, &peripheral::opt3001::i2cConfig);

	/* Disable I2C module to make changes */
	MAP_I2C_disableModule(EUSCI_B1_BASE);

	/* Enable I2C Module to start operations */
	MAP_I2C_enableModule(EUSCI_B1_BASE);

	return;
}

/***************************************************************************/ /**
                                                                               * @brief  Reads data from the sensor
                                                                               * @param  i_cWriteByte Address of register to read from
                                                                               * @return Register contents
                                                                               ******************************************************************************/

int peripheral::opt3001::I2C::Read16(unsigned char i_cWriteByte) {
	int val = 0;
	int valScratch = 0;

	/* Set master to transmit mode PL */
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);

	/* Clear any existing interrupt flag PL */
	MAP_I2C_clearInterruptFlag(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0);

	/* Wait until ready to write PL */
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE))
		;

	/* Initiate start and send first character */
	MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE, i_cWriteByte);

	/* Wait for TX to finish */
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B1_BASE,
	                                    EUSCI_B_I2C_TRANSMIT_INTERRUPT0)))
		;

	/* Initiate stop only */
	MAP_I2C_masterSendMultiByteStop(EUSCI_B1_BASE);

	/* Wait for Stop to finish */
	while (!MAP_I2C_getInterruptStatus(EUSCI_B1_BASE, EUSCI_B_I2C_STOP_INTERRUPT))
		;

	/*
	 * Generate Start condition and set it to receive mode.
	 * This sends out the slave address and continues to read
	 * until you issue a STOP
	 */
	MAP_I2C_masterReceiveStart(EUSCI_B1_BASE);

	/* Wait for RX buffer to fill */
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B1_BASE,
	                                    EUSCI_B_I2C_RECEIVE_INTERRUPT0)))
		;

	/* Read from I2C RX register */
	val = MAP_I2C_masterReceiveMultiByteNext(EUSCI_B1_BASE);

	/* Receive second byte then send STOP condition */
	valScratch = MAP_I2C_masterReceiveMultiByteFinish(EUSCI_B1_BASE);

	/* Shift val to top MSB */
	val = (val << 8);

	/* Read from I2C RX Register and write to LSB of val */
	val |= valScratch;

	/* Return temperature value */
	return (int16_t)val;
}

/***************************************************************************/ /**
                                                                               * @brief  Writes data to the sensor
                                                                               * @param  i_cPointer  Address of register you want to modify
                                                                               * @param  i_uWriteByte Data to be written to the specified register
                                                                               * @return none
                                                                               ******************************************************************************/

void peripheral::opt3001::I2C::Write16(unsigned char i_cPointer,
                                       unsigned int i_uWriteByte) {
	/* Set master to transmit mode PL */
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);

	/* Clear any existing interrupt flag PL */
	MAP_I2C_clearInterruptFlag(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0);

	/* Wait until ready to write PL */
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE))
		;

	/* Initiate start and send first character */
	MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE, i_cPointer);

	/* Send the MSB to SENSOR */
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE,
	                                (unsigned char)(i_uWriteByte >> 8));

	MAP_I2C_masterSendMultiByteFinish(EUSCI_B1_BASE,
	                                  (unsigned char)(i_uWriteByte & 0xFF));
}

void peripheral::opt3001::I2C::SetSlave(unsigned int i_uSlaveAdr) {
	/* Specify slave address for I2C */
	MAP_I2C_setSlaveAddress(EUSCI_B1_BASE, i_uSlaveAdr);

	/* Enable and clear the interrupt flag */
	MAP_I2C_clearInterruptFlag(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 +
	                                              EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	return;
}
