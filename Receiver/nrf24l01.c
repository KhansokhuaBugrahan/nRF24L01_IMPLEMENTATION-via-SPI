#include "spi.h"
#include "nrf24l01.h"  

void write_register_nrf24l01(unsigned int8 register_address, unsigned int8 data)
{
     CSN_LOW();
                                                     
     unsigned int8 read_buffer = 0;             
                                
     register_address |= W_REGISTER; // set for write operation 0x20 = 0010 0000
     spi_send_data(register_address);                                    
                                                                        
     read_buffer =  SPI1->SSP1BUF;  // flush STATUS register              
                                                            
     spi_send_data(data);       
     read_buffer =  SPI1->SSP1BUF; 
                     
     CSN_HIGH();                          
     
}                              
unsigned int8 read_register_nrf24l01(unsigned int8 register_address)
{

         CSN_LOW();             
                                                                                                                                                        
      unsigned int8 read_buffer = 0;             
      unsigned int8 dummy_byte = 0xFF; // I can send the registerAddress twice instead of creating a new variable for this
                                // But to avoid confusion, it is clearer
      register_address |= R_REGISTER; // set for read operation      
      spi_send_data(register_address);                                                                                                                     
                                                              
      read_buffer =  SPI1->SSP1BUF;  // flush STATUS register
                                                
      spi_send_data(dummy_byte);        
      read_buffer = spi_receive_data(register_address);
                                                                                                                                                                       
        CSN_HIGH();       
                                                                                                                                                               
        return read_buffer;                                                                                                                                                  

}                          
                                                    
void define_address_tx_nrf24l01(unsigned int8* address)      
{                                                                    
   CSN_LOW();
                                                     
     unsigned int8 read_buffer = 0;             
                                               
   unsigned int8 register_address = NRF24L01_TX_ADDR; 
                                                      
   register_address |= W_REGISTER; // set for write operation 0x20 = 0010 0000     
   spi_send_data(register_address);                                                            
   read_buffer =  SPI1->SSP1BUF;  // flush STATUS register          
                                 
   
       int i;  
      for(i = 0; i < 5; i++)         
      {                                                       
          spi_send_data(*address++);       
          read_buffer =  SPI1->SSP1BUF;    
      }
                             
   CSN_HIGH();                          
     
}
void define_address_rx_nrf24l01(unsigned int8* address)    
{                                                                    
   CSN_LOW();
                                                     
     unsigned int8 read_buffer = 0;             
                                                  
   unsigned int8 register_address = NRF24L01_RX_ADDR_P0;              
                                                                      
   register_address |= W_REGISTER; // set for write operation 0x20 = 0010 0000     
   spi_send_data(register_address);                                                            
   read_buffer =  SPI1->SSP1BUF;  // flush STATUS register          
                                 
   
       int i;  
      for(i = 0; i < 5; i++)         
      {                                                       
          spi_send_data(*address++);       
          read_buffer =  SPI1->SSP1BUF;    
      }
                             
   CSN_HIGH();                          
     
} 
void read_address_tx_nrf24l01(unsigned int8* buffer)      
{                                                                     
        CSN_LOW();             
                                                                                                                                                        
      unsigned int8 read_buffer = 0;             
      unsigned int8 dummy_byte = 0xFF; // I can send the registerAddress twice instead of creating a new variable for this
                                // But to avoid confusion, it is clearer   
                                
      unsigned int8 register_address = NRF24L01_TX_ADDR;                          
      register_address |= R_REGISTER; // set for read operation      
      spi_send_data(register_address);                                                                                                                                                                                 
      read_buffer =  SPI1->SSP1BUF;  // flush STATUS register
      
       int i;
       for(i = 0; i < 5; i++)
       {       
             spi_send_data(dummy_byte);        
             *buffer++ = spi_receive_data(register_address);          
       }
      
                                                                                                                                                                       
        CSN_HIGH();                          
                                                                                                                                                                                     
}   

void read_address_rx_nrf24l01(unsigned int8* buffer)      
{                                                                     
        CSN_LOW();             
                                                                                                                                                        
      unsigned int8 read_buffer = 0;             
      unsigned int8 dummy_byte = 0xFF; // I can send the registerAddress twice instead of creating a new variable for this
                                // But to avoid confusion, it is clearer   
                                
      unsigned int8 register_address = NRF24L01_RX_ADDR_P0;                          
      register_address |= R_REGISTER; // set for read operation      
      spi_send_data(register_address);                                                                                                                                                                                 
      read_buffer =  SPI1->SSP1BUF;  // flush STATUS register
      
       int i;
       for(i = 0; i < 5; i++)
       {       
             spi_send_data(dummy_byte);        
             *buffer++ = spi_receive_data(register_address);          
       }
      
                                                                                                                                                                       
        CSN_HIGH();       
                                                                                                                                                                                     
}         

unsigned int8 receive_data_nrf24l01(void)   
{
      CSN_LOW();             
                                                                                                                                                        
      unsigned int8 read_buffer = 0;             
      unsigned int8 dummy_byte = 0xFF; // I can send the registerAddress twice instead of creating a new variable for this
                                // But to avoid confusion, it is clearer
      unsigned int8 register_address = R_RX_PAYLOAD; // set for read operation      
      spi_send_data(register_address);                                                                                                                     
                                                              
      read_buffer =  SPI1->SSP1BUF;  // flush STATUS register
                                                
      spi_send_data(dummy_byte);        
      read_buffer = spi_receive_data(register_address);
                                                                                                                                                                       
        CSN_HIGH();       
                                                                                                                                                               
        return read_buffer; 
                 
}        
void rx_flush_fifo(void)   
{
       CSN_LOW();
                                                     
     unsigned int8 read_buffer = 0;             
                                
     unsigned int8 register_address = FLUSH_RX; // set for write operation 0x20 = 0010 0000
     spi_send_data(register_address);                                    
                                                                        
     read_buffer =  SPI1->SSP1BUF;  // flush STATUS register              
                      
     CSN_HIGH();            
}
  /*      
unsigned int8 read_register_nrf24l01(unsigned int8 register_address)
{
    unsigned int8 value;
                                                                          
    CSN_LOW();

    register_address |= R_REGISTER;  // Set for read operation (bitwise OR with 0x00)

    spi_send_data(register_address); // Send register address, receive status (discard)
    value = spi_send_data(0xFF);     // Send dummy byte, receive register value
    
                   
    CSN_HIGH();

    return value;
}      */
                                                                                                           
