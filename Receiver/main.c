#include <18F46K22.h>      
 

#FUSES NOWDT, NOBROWNOUT, NOLVP, NOXINST, NOPUT, NOPROTECT, NOCPD, NOWRT, NODEBUG, HSM  // last  change DEBUG
#use delay(clock=16MHz, internal)
                       
                                                                                  
#include "spi.h"      
#include "nrf24l01.h"  
   
#include "spi.c"                                                       
#include "nrf24l01.c"                                                                                              
                                     

#define         LED_ACTIVATE      (0x7B)        
#define         CHECK_RX_BUFFER   (stat2 & (1u << 6))

void main() {                                                             
                                              
    set_tris_d(0x00);                                                                                
    output_d(0x00); // Pattern to check if code runs
                                                                                                                                                                                                                                                                                                                                                                                                   
    delay_ms(110);  // you need to wait at least 100 ms to have stabilized power supply for nRF    after Vdd > 1.9V                                                                                                                                                                  
    spi_init();                                                                                                                                                                                     
    nrf24l01_init();                                                                                                               
                                                                
    CLEAR_RX_DR();        
    rx_flush_fifo();                                     
    unsigned int8 incoming_data;      
    CE_HIGH();          
                                              
     while(1)                                                                                                                                          
      {                            
            unsigned int8 stat2 = read_register_nrf24l01(NRF24L01_STATUS);

            if(CHECK_RX_BUFFER) // RX buffer fulled
            {
                      incoming_data = receive_data_nrf24l01();      
                 if(LED_ACTIVATE == incoming_data)
                 {
                            output_toggle(pin_d1);                                                                      
                            delay_ms(700);         
                 }                                       
                       CLEAR_RX_DR(); 
                       rx_flush_fifo();                                               
            }                                                   
           
       }      
}                                    
