

                                               


#ifndef spi_h_
#define spi_h_                        

                                                        
                                                   

#define        SPI1_BASE_ADDRESS        (0xFC5)
                                                       

                                               
  

typedef struct{

   volatile unsigned int8 SSP1CON2; 
   volatile unsigned int8 SSP1CON1; 
   volatile unsigned int8 SSP1STAT; 
   volatile unsigned int8 SSP1ADD; 
   volatile unsigned int8 SSP1BUF;                                    
   volatile unsigned int8 SSP1MSK; 
   volatile unsigned int8 SSP1CON3; 


}SPI_MODE_Reg_t;       
                                                
#define     SPI1        ((SPI_MODE_Reg_t*)SPI1_BASE_ADDRESS)  
                                                           
                                                           
#define CSN_PIN  PIN_A0
#define CE_PIN   PIN_A1

#define CSN_HIGH() output_high(CSN_PIN)
#define CSN_LOW()  output_low(CSN_PIN)

#define CE_HIGH()  output_high(CE_PIN)
#define CE_LOW()   output_low(CE_PIN)
   
void spi_init();

#endif                                                                                       
