/*
 * nrf24l01.h
 *
 *  Created on: May 1, 2025
 *      Author: khans
 */

#ifndef NRF24L01_H_
#define NRF24L01_H_

#include <stdint.h>
#include <gpio.h>


typedef enum {

	NRF24L01_CONFIG = 0x00, 	// Configuration Register
	NRF24L01_EN_AA= 0x01,       // Enable Auto Acknowledgment
	NRF24L01_EN_RXADDR = 0x02,  // Enabled RX Addresses
	NRF24L01_SETUP_AW = 0x03,   // Setup of Address Widths
	NRF24L01_SETUP_RETR = 0x04, // Setup of Automatic Retransmission
	NRF24L01_RF_CH = 0x05,  	// RF Channel
	NRF24L01_RF_SETUP = 0x06,   // RF Setup Register
	NRF24L01_STATUS = 0x07, 	// Status Register
	NRF24L01_OBSERVE_TX = 0x08, // Transmit observe register
	NRF24L01_RPD = 0x09,  		// Enabled RX Addresses
	NRF24L01_RX_ADDR_P0 = 0x0A, // Receive address data pipe 0
	NRF24L01_RX_ADDR_P1 = 0x0B, // Receive address data pipe 1
	NRF24L01_RX_ADDR_P2 = 0x0C, // Receive address data pipe 2
	NRF24L01_RX_ADDR_P3 = 0x0D, // Receive address data pipe 3
	NRF24L01_RX_ADDR_P4 = 0x0E, // Receive address data pipe 4
	NRF24L01_RX_ADDR_P5 = 0x0F, // Receive address data pipe 5
	NRF24L01_TX_ADDR = 0x10,    // Transmit address. Used for a PTX device only.
	NRF24L01_RX_PW_P0 = 0x11, 	// Number of bytes in RX payload in data pipe 0
	NRF24L01_RX_PW_P1 = 0x12, 	// Number of bytes in RX payload in data pipe 1
	NRF24L01_RX_PW_P2 = 0x13,	// Number of bytes in RX payload in data pipe 2
	NRF24L01_RX_PW_P3 = 0x14, 	// Number of bytes in RX payload in data pipe 3
	NRF24L01_RX_PW_P4 = 0x15, 	// Number of bytes in RX payload in data pipe 4
	NRF24L01_RX_PW_P5 = 0x16, 	// Number of bytes in RX payload in data pipe 5
	NRF24L01_FIFO_STATUS = 0x17,//  FIFO Status Register
	NRF24L01_DYNPD = 0x1C, 		//  Enable dynamic payload length
	NRF24L01_FEATURE = 0x1D, 	//   Feature Register


}NRF24L01_RegDef_e;



		/*
		 *  SPI Commands
		 */

#define 	 R_REGISTER				0x00
#define 	 W_REGISTER				0x20
#define		 R_RX_PAYLOAD			0x61
#define		 W_TX_PAYLOAD           0xA0
#define		 FLUSH_TX			    0xE1
#define		 FLUSH_RX				0xE2
#define		 REUSE_TX_PL			0xE3
#define		 R_RX_PL_WID			0x60
#define		 W_ACK_PAYLOAD			0xA8
#define		 W_TX_PAYLOAD_NOACK     0xB0
#define		 NOP					0xFF






#define 	 NRF24L01_CE_HIGH()     gpioWritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET)
#define		 NRF24L01_CE_LOW()      gpioWritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)
#define		 NRF24L01_CSN_HIGH()    gpioWritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define 	 NRF24L01_CSN_LOW()     gpioWritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)

#define      CLEAR_TX_DS()			(writeRegisterDataNrf24l01(NRF24L01_STATUS, (1u << 5 )))
#define		 CLEAR_TX_RT()			(writeRegisterDataNrf24l01(NRF24L01_STATUS, (1u << 4 )))

void writeRegisterDataNrf24l01(uint8_t registerAddress, uint8_t data );
uint8_t readRegisterDataNrf24l01(uint8_t registerAddress );
void transmitDataNrf24l01(uint8_t payload);
void flushTxFifo(void);
void nrf24l01Init(void);

#endif /* NRF24L01_H_ */
