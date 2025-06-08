#include "spi.h"

void spi_init()  
{                           

  set_tris_a(0x00);     // A0(CSN)   A1(CE)    output                                            
  set_tris_c(0x10);     // C4 (MISO) input ,  C5 (MOSI)  C3 (SCK)  output  
                                                                                          
   SPI1->SSP1CON1 |= (1u << 5);  // SPI peripheral enable                                                              
   SPI1->SSP1CON1 &= ~(0x0F); // set for 4 MHz speed SPI Master mode          
   SPI1->SSP1CON1 &= ~(1u << 4);    // set idle state LOW          
   SPI1->SSP1STAT |= (1u << 6); // set for rising edge CKE                   
   SPI1->SSP1STAT &= ~(1u << 7); // set SMP                                                
                                                            
   CSN_HIGH();                       
   CE_LOW();  
  
}             
                                                          
void spi_send_data(unsigned int8 data)               
{                                            
       while(SPI1->SSP1STAT & (1u << 0)); // wait for buffer flushed                 
        SPI1->SSP1BUF = data;                 
       while(!(SPI1->SSP1STAT & (1u << 0))); // wait for buffer full 
                                                                                                               
}                                                                                                                                                        
/*unsigned int8 spi_send_data(unsigned int8 data)
{
    SPI1->SSP1BUF = data;

    // Wait until transmission is complete
    while (!bit_test(SPI1->SSP1STAT, 0));  // Wait until BF (bit 0) is set

    return SPI1->SSP1BUF;  // Return received data (what slave sent)
}             */
                                                                                                                                                          
unsigned int8 spi_receive_data(unsigned int8 data)               
{                                             
       while(!(SPI1->SSP1STAT & (1u << 0))); // wait for buffer full                 
        data = SPI1->SSP1BUF;                 
       while(SPI1->SSP1STAT & (1u << 0)); // wait for buffer flush 
        return data;
                                      
}  
