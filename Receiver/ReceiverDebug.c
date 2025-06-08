#include <18F46K22.h>      
 

#FUSES NOWDT, NOBROWNOUT, NOLVP, NOXINST, NOPUT, NOPROTECT, NOCPD, NOWRT, NODEBUG, HSM  // last  change DEBUG
#use delay(clock=16MHz, internal)
//#fuses WDT1024                            
 
                                                                                  
#include "spi.h"      
#include "nrf24l01.h"  
   
#include "spi.c"                                                       
#include "nrf24l01.c"                                                                                              
                                     

#define         LED_ACTIVATE      (0x7B)        

void main() {                                                             
                                              
    set_tris_d(0x00);                                                                                
    output_d(0x00); // Pattern to check if code runs
                                                                                                                                                                                                                                                                                                                                                                                                   
    delay_ms(110);  // you need to wait at least 100 ms to have stabilized power supply for nRF    after Vdd > 1.9V                                                                                                                                                                  
    spi_init();              
                                                                                      
                                                                                    
    write_register_nrf24l01(NRF24L01_CONFIG, 0x0B);  // set for RX mode
                                                                  
    unsigned int8 CONFIG = read_register_nrf24l01(NRF24L01_CONFIG);                      
                            
    write_register_nrf24l01(NRF24L01_EN_AA, 0x01); // open  auto ack for only pipe0     
                                                               
    unsigned int8 EN_AA = read_register_nrf24l01(NRF24L01_EN_AA);     
                                                                           
    write_register_nrf24l01(NRF24L01_EN_RXADDR, 0x01);  // enable data pipe0
                                                         
    unsigned int8 EN_RXADDR = read_register_nrf24l01(NRF24L01_EN_RXADDR);                                                                         
                                                                                                          
    write_register_nrf24l01(NRF24L01_RF_CH, 0x64); // set 2.5 GHz frequency band    
                                                                          
    unsigned int8 RF_CH = read_register_nrf24l01(NRF24L01_RF_CH);                                            
                                                                                
     write_register_nrf24l01(NRF24L01_RF_SETUP, 0x06); //   set 0 dBm, 1mbps     
                                               
    unsigned int8 RF_SETUP = read_register_nrf24l01(NRF24L01_RF_SETUP);                                                 
                                                                                                                            
     write_register_nrf24l01(NRF24L01_SETUP_AW, 0x03); //    set address width to 5 byte        
                                                                                     
    unsigned int8 SETUP_AW = read_register_nrf24l01(NRF24L01_SETUP_AW);        
                                                                      
                                                                                                 
      unsigned int8 address[5] = {0xE1, 0x42, 0x93, 0xB8, 0x15};    
                                                                                                   
      unsigned int8 buffer_tx [5], buffer_rx[5];                       
                                
     define_address_tx_nrf24l01(address);      // set TX address 
                                                                                               
     read_address_tx_nrf24l01(buffer_tx);                       
      
     define_address_rx_nrf24l01(address);      // set RX address   
                                               
     read_address_rx_nrf24l01(buffer_rx);        
                                                                                                                  
     write_register_nrf24l01(NRF24L01_RX_PW_P0, 0x01); // set payload to 1 byte in pipe0 

     unsigned int8 RX_PW_P0 = read_register_nrf24l01(NRF24L01_RX_PW_P0);                                
                                                                                                          
                                                                              
     
     /*                                                                                                                          
                                                                
       Check the registers using watch window, do they correctly get set?          
       
     
     
     */
                                                                                            
  /*                                                 
    Now, you have successfully completed acting on registers in nRF module.
    
    Following steps need to be handled;                             
                                                                                                   
    1-) Set the nRF as receiver.
        set PRIM_RX bit as high in CONFIG reg, PWR_UP '1', and   CE pin high                          
             
    2-)                    F0 = 2400 + RF_CH [MHz]  RF Channel frequency formula                        
                           set RF_CH 2400 + 100 for both TX and RX.             
                                       
                          1 mbps, 0 dBm     set  TX and RX with the same parameters                                   
                            SETUP_AW  5byte      set  TX and RX with the same parameters                         
                                                        
                           RX_ADDR_P0 = same 5-byte address
                           RX_PW_P0 = size of expected payload (1–32)
                                                        
                                              
  */                
                  CLEAR_RX_DR();        
                  rx_flush_fifo();                                     
                  unsigned int8 incoming_data;      
                  CE_HIGH();                                                        
     while(1)                                                                                                                                          
      {                            
            unsigned int8 stat2 = read_register_nrf24l01(NRF24L01_STATUS);

            if(stat2 & (1u << 6)) // RX buffer fulled
            {
                      incoming_data = receive_data_nrf24l01();      
                 if(LED_ACTIVATE == incoming_data)
                 {
                            output_toggle(pin_d1);                                                                      
                            delay_ms(700);         
                 }                                       
                       CLEAR_RX_DR(); 
                       rx_flush_fifo();     
                       //CE_LOW();                                            
            }                                                   
           
       }                                            
/*         The MSSPx module has five registers for SPI mode
          operation. These are:
         • MSSPx STATUS register (SSPxSTAT)      ---
         • MSSPx Control register 1 (SSPxCON1)   ---
         • MSSPx Control register 3 (SSPxCON3)   
         • MSSPx Data Buffer register (SSPxBUF)   
         • MSSPx Address register (SSPxADD)
         • MSSPx Shift register (SSPxSR) 
         (Not directly accessible)                     



*/                           
}         
                                
/*
   I can communicate while in both debuggig mode or programming mode. However, when I directly program the pic and remove the pickit3 device
   it does not communicate anymore. What is the reason for this? Above you can see the RX code for PIC18F46K22, in below transmitter code, 


*/


