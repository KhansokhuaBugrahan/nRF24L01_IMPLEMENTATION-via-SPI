#include <stdint.h>
#include "stm32f4xx.h"
#include <stdbool.h>
#include "gpio.h"
#include "armcortexm4.h"
#include "timer.h"
#include "spi.h"
#include "nrf24l01.h"


#define         LED_ACTIVATE      (0x7B)
#define         BUTTON_PRESSED    (GPIOA->IDR & (1u << 0))
#define			CHECK_ACK_BIT	  (STAT & (1u << 5))
#define			CHECK_RT_BIT	  (STAT & (1u << 4))

int main(void)
{

		sysTickInit();
		 /*
		 *
		 * Configure a built-in button to trigger send function
		 */


	   GPIO_Handle_t SEND_BUTTON_PA0 ={ .PORTNAME = GPIOA,
										.PINCONF.PIN = GPIO_PIN_0,
										.PINCONF.MODE = GPIO_MODE_INPUT,
										.PINCONF.OTYPE = GPIO_OTYPE_PP,
										.PINCONF.OSPEED = GPIO_OSPEED_VHIGH,
										.PINCONF.PUPD = GPIO_PUPD_NO,
										.PINCONF.AF = AFNO
									 };
	   	   	    /*
		 		 * PA5 - PA6 - PA7 pins must be configured in AF mode for SPI1
		 		 */



		GPIO_Handle_t SW_NSS_PA4 = {	 // on nrf24l01 connected to CSN pin
										.PORTNAME = GPIOA,
										.PINCONF.PIN = GPIO_PIN_4,
										.PINCONF.MODE = GPIO_MODE_OUTPUT,
										.PINCONF.OTYPE = GPIO_OTYPE_PP,
										.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
										.PINCONF.PUPD = GPIO_PUPD_NO,
										.PINCONF.AF = AFNO
									};
		GPIO_Handle_t SP1_SCK_PA5 = { 	 // on nrf24l01 connected to SCK pin
										.PORTNAME = GPIOA,
										.PINCONF.PIN = GPIO_PIN_5,
										.PINCONF.MODE = GPIO_MODE_ALTARNATE,
										.PINCONF.OTYPE = GPIO_OTYPE_PP,
										.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
										.PINCONF.PUPD = GPIO_PUPD_NO,
										.PINCONF.AF = AF5
									};
		GPIO_Handle_t SP1_MISO_PA6 = {   // on nrf24l01 connected to MISO pin
										.PORTNAME = GPIOA,
										.PINCONF.PIN = GPIO_PIN_6,
										.PINCONF.MODE = GPIO_MODE_ALTARNATE,
										.PINCONF.OTYPE = GPIO_OTYPE_PP,
										.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
										.PINCONF.PUPD = GPIO_PUPD_PU,
										.PINCONF.AF = AF5
									};
		GPIO_Handle_t SP1_MOSI_PA7 = {   // on nrf24l01 connected to MOSI pin
										.PORTNAME = GPIOA,
										.PINCONF.PIN = GPIO_PIN_7,
										.PINCONF.MODE = GPIO_MODE_ALTARNATE,
										.PINCONF.OTYPE = GPIO_OTYPE_PP,
										.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
										.PINCONF.PUPD = GPIO_PUPD_NO,
										.PINCONF.AF = AF5
									};

		GPIO_Handle_t TX_RX_MODE_CE_PA3 = {   // on nrf24l01 connected to CE pin
										.PORTNAME = GPIOA,
										.PINCONF.PIN = GPIO_PIN_3,
										.PINCONF.MODE = GPIO_MODE_OUTPUT,
										.PINCONF.OTYPE = GPIO_OTYPE_PP,
										.PINCONF.OSPEED = GPIO_OSPEED_HIGH,
										.PINCONF.PUPD = GPIO_PUPD_NO,
										.PINCONF.AF = AFNO
									 };

		gpioInit(&TX_RX_MODE_CE_PA3); // this pin is set manually to decide NRF24L01's operation mdoe.(TX,RX,standby1-2)
		gpioInit(&SW_NSS_PA4);
		gpioInit(&SP1_SCK_PA5);
		gpioInit(&SP1_MISO_PA6);
		gpioInit(&SP1_MOSI_PA7);

		gpioInit(&SEND_BUTTON_PA0);

		NRF24L01_CE_LOW();
		NRF24L01_CSN_HIGH();


		SPI_Handle_t SPI1_NRF24L01 = {  .spiSelect = SPI1,
										.pinConfig.mode = SPI_DEVICE_MASTER,
										.pinConfig.baudRate = SPI_BAUD_RATE_PRESC_8, // 2 MHz clock (max 10Mhz), since main clock 16 Mhz HSI
										.pinConfig.cpol = SPI_CPOL_IDLE_0,
										.pinConfig.cphase = SPI_CPHASE_FIRST_EDGE,
										.pinConfig.dataSize = SPI_DATA_SIZE_8,
										.pinConfig.firstBit = SPI_MSB_FIRST,
										.pinConfig.nss = SPI_SW_MODE
									};

		delay_ms(110);

		spixInit(&SPI1_NRF24L01);
		nrf24l01Init();

		 CLEAR_TX_RT();
		 flushTxFifo();
		 CLEAR_TX_DS();
		 CLEAR_TX_RT();

				while (1)
				{

					uint8_t STAT = readRegisterDataNrf24l01(NRF24L01_STATUS);

						if(BUTTON_PRESSED) // button pressed
						{

							transmitDataNrf24l01(LED_ACTIVATE);
							flushTxFifo();
						}

						if(CHECK_ACK_BIT) // ACK packet has been received
							CLEAR_TX_DS();

						if(CHECK_RT_BIT) // Retransmit reset
							CLEAR_TX_RT();

				}


}
