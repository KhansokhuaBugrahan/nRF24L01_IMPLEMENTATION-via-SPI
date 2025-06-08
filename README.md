# nRF24L01_IMPLEMENTATION-via-SPI-
In this application, we control a single LED  remotely using nRF24L01 module.


Transmitter side MCU STM32F407G-DISC   ----------->                            STMCubeIDE                                                                    
Receiver side MCU PIC18F46K22     ---->                               PIC C Compiler - MPLABIDE               

I have tested the module in several rooms of my flat without using antenna in both side receiver and transmitter.                                     
You can have more than 100 meter range with different setups by mounting antenna.

I especially chose the PIC18F46K22 due to its power supply matchig  with nRF module. (3.3V)   
Therefore, we did not need to use a logic translator.                             
I powered transmitter's module using Vdd pin.

Since PIC18F46K22 has an internal oscillator. I did not use any external crystal.

In the video below, I powered STM using a USB cable, and PIC18F46K22 was powered by an external adjustable(to 3.3V) adapter.               

main.c files are last organized codes, and you can examine the debug C files


Click the icon to redirect YouTube and watch the showcase video.                                           
[![Custom Thumbnail](https://github.com/KhansokhuaBugrahan/ADXL345_IMPLEMENTATION-via-SPI/blob/main/gif.gif)](https://youtu.be/KmmfmDtCy3U)
