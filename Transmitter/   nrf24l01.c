/*
 * nrf24l01.c
 *
 *  Created on: May 9, 2025
 *      Author: khans
 */
#include "spi.h"
#include "nrf24l01.h"
#include "armcortexm4.h"
void writeRegisterDataNrf24l01(uint8_t registerAddress, uint8_t data )
{
	SPI1_PERIPHERAL_ENABLE();
	NRF24L01_CSN_LOW();

	registerAddress |= W_REGISTER; // set for write operation 0x20 = 0010 0000
	spixSendDataByte(SPI1, &registerAddress , 1); //
	spixSendDataByte(SPI1, &data , 1);

	NRF24L01_CSN_HIGH();
	SPI1_PERIPHERAL_DISABLE();
}

uint8_t readRegisterDataNrf24l01(uint8_t registerAddress )
{
		SPI1_PERIPHERAL_ENABLE();
		NRF24L01_CSN_LOW();

		uint8_t readBuffer = 0;
		uint8_t dummyByte = 0xFF; // I can send the registerAddress twice instead of creating a new variable for this
								  // But to avoid confusion, it is clearer
		registerAddress |= R_REGISTER; // set for read operation

		spixSendDataByte(SPI1, &registerAddress , 1);

		readBuffer = SPI1->SPI_DR;  /*
											flush the register by reading it, otherwise it remains stuck.
											In regardless of register address we send , first data is always STATUS register.
											we clear it here.
									*/

		spixSendDataByte(SPI1,&dummyByte , 1);
		spixReceiveDataByte(SPI1, &readBuffer, 1);

		NRF24L01_CSN_HIGH();
		SPI1_PERIPHERAL_DISABLE();

		return readBuffer;
}

void defineAddressTxNrf24l01(uint8_t* address)
{
		SPI1_PERIPHERAL_ENABLE();
		NRF24L01_CSN_LOW();

		uint8_t registerAddress = NRF24L01_TX_ADDR;
		registerAddress |= W_REGISTER; // set for write operation 0x20 = 0010 0000
		spixSendDataByte(SPI1, &registerAddress , 1); //

		for(int i = 0; i < 5; i++)
		  spixSendDataByte(SPI1, address++ , 1);

		NRF24L01_CSN_HIGH();
		SPI1_PERIPHERAL_DISABLE();
}

void defineAddressRxNrf24l01(uint8_t* address)
{
		SPI1_PERIPHERAL_ENABLE();
		NRF24L01_CSN_LOW();

		uint8_t registerAddress = NRF24L01_RX_ADDR_P0;
		registerAddress |= W_REGISTER; // set for write operation 0x20 = 0010 0000
		spixSendDataByte(SPI1, &registerAddress , 1); //

		for(int i = 0; i < 5; i++)
		  spixSendDataByte(SPI1, address++ , 1);

		NRF24L01_CSN_HIGH();
		SPI1_PERIPHERAL_DISABLE();
}

void readAddressTxNrf24l01(uint8_t* buffer)
{
		SPI1_PERIPHERAL_ENABLE();
		NRF24L01_CSN_LOW();

		uint8_t readBuffer = 0;
		uint8_t dummyByte = 0xFF; // I can send the registerAddress twice instead of creating a new variable for this
								  // But to avoid confusion, it is clearer

		uint8_t registerAddress = NRF24L01_TX_ADDR;
		registerAddress |= R_REGISTER; // set for read operation

		spixSendDataByte(SPI1, &registerAddress , 1);

		readBuffer = SPI1->SPI_DR;  /*
											flush the register by reading it, otherwise it remains stuck.
											In regardless of register address we send , first data is always STATUS register.
											we clear it here.
									*/

		for(int i = 0; i < 5; i++)
		{
			spixSendDataByte(SPI1,&dummyByte , 1);
			spixReceiveDataByte(SPI1, buffer++, 1);
		}


		NRF24L01_CSN_HIGH();
		SPI1_PERIPHERAL_DISABLE();

}

void readAddressRxNrf24l01(uint8_t* buffer)
{
		SPI1_PERIPHERAL_ENABLE();
		NRF24L01_CSN_LOW();

		uint8_t readBuffer = 0;
		uint8_t dummyByte = 0xFF; // I can send the registerAddress twice instead of creating a new variable for this
								  // But to avoid confusion, it is clearer

		uint8_t registerAddress = NRF24L01_RX_ADDR_P0;
		registerAddress |= R_REGISTER; // set for read operation

		spixSendDataByte(SPI1, &registerAddress , 1);

		readBuffer = SPI1->SPI_DR;  /*
											flush the register by reading it, otherwise it remains stuck.
											In regardless of register address we send , first data is always STATUS register.
											we clear it here.
									*/

		for(int i = 0; i < 5; i++)
		{
			spixSendDataByte(SPI1,&dummyByte , 1);
			spixReceiveDataByte(SPI1, buffer++, 1);
		}


		NRF24L01_CSN_HIGH();
		SPI1_PERIPHERAL_DISABLE();
}

void transmitDataNrf24l01(uint8_t payload)
{
		// A high pulse on CE starts the transmission. The minimum pulse width on CE is 10µs
		SPI1_PERIPHERAL_ENABLE();
		NRF24L01_CSN_LOW();

		uint8_t registerAddress = W_TX_PAYLOAD; // set for write operation 0x20 = 0010 0000
		spixSendDataByte(SPI1, &registerAddress , 1); //
		spixSendDataByte(SPI1, &payload , 1);

		NRF24L01_CSN_HIGH();

		NRF24L01_CE_HIGH();
		delay_ms(1); // 1000 us
		NRF24L01_CE_LOW();
		SPI1_PERIPHERAL_DISABLE();


}

uint8_t receiveDataNrf24l01()
{
		SPI1_PERIPHERAL_ENABLE();
		NRF24L01_CSN_LOW();

		uint8_t readBuffer = 0;
		uint8_t dummyByte = 0xFF; // I can send the registerAddress twice instead of creating a new variable for this
								  // But to avoid confusion, it is clearer
		uint8_t registerAddress = R_RX_PAYLOAD; // set for read operation

		spixSendDataByte(SPI1, &registerAddress , 1);

		readBuffer = SPI1->SPI_DR;  /*
											flush the register by reading it, otherwise it remains stuck.
											In regardless of register address we send , first data is always STATUS register.
											we clear it here.
									*/

		spixSendDataByte(SPI1,&dummyByte , 1);
		spixReceiveDataByte(SPI1, &readBuffer, 1);

		NRF24L01_CSN_HIGH();
		SPI1_PERIPHERAL_DISABLE();

		return readBuffer;


}

void flushTxFifo()
{
		SPI1_PERIPHERAL_ENABLE();
		NRF24L01_CSN_LOW();

		uint8_t registerAddress = FLUSH_TX; // set for write operation 0x20 = 0010 0000
		spixSendDataByte(SPI1, &registerAddress , 1); //


		NRF24L01_CSN_HIGH();

		NRF24L01_CE_HIGH();
		delay_ms(1); // 1000 us
		NRF24L01_CE_LOW();
		SPI1_PERIPHERAL_DISABLE();
}
/*
 *
 * Is it possible to create another enum inside an enum ? something like nested structure
 *
 */

