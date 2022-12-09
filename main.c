#include "lib/include.h"


int main(void)
{   
    int8_t word[2];
    uint16_t count = 0;
    Configurar_PLL();  //Confiuracion de velocidad de reloj 50MHZ
    Configurar_GPIO();
    Configurar_UART0();
    Configurar_SSI2();
    while(1)
    {
        //word[0] = readChar();
        //word[1] = readChar();
        count += 1; 
        //count = 1;
        SPI_write((uint8_t)count); 
        SysTick_1ms(50000);
        SysTick_1ms(50000);
        SysTick_1ms(50000);
        SysTick_1ms(50000);
        SysTick_1ms(50000);
        SysTick_1ms(50000);
        SysTick_1ms(50000);
        SysTick_1ms(50000);
        SysTick_1ms(50000);
        SysTick_1ms(50000);
        /*
                count = 2;
        SPI_write((uint8_t)count);
        SysTick_1ms(50000);
        count = 3;
        SPI_write((uint8_t)count); 
        SysTick_1ms(50000);
        count = 4;
        SPI_write((uint8_t)count);
        SysTick_1ms(50000);
        count = 5;
        SPI_write((uint8_t)count); 
        SysTick_1ms(50000);
        count = 6;
        SPI_write((uint8_t)count);
        SysTick_1ms(50000);
        count = 7;
        SPI_write((uint8_t)count); 
        SysTick_1ms(50000);
        count = 8;
        SPI_write((uint8_t)count);
        SysTick_1ms(50000);
        
        */

        //printChar('\n');

        //SPI_write(word[1]);
    }

}
