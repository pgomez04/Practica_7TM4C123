
#include "lib/include.h"
extern void Configurar_SSI2(void)
{
    
    SYSCTL->RCGCSSI |= (1<<2); //se activa el Modulo 2 SSI2
    SYSCTL->RCGCGPIO |= (1<<3);//Puerto D
    GPIOD_AHB->DIR |= (0<<3) | (1<<2) | (1<<1) | (0<<0); //selector es salida = 1
    GPIOD_AHB->AFSEL = (1<<3)|(1<<2)|(1<<1)|(1<<0); //antes del 4 al 7
    GPIOD_AHB->PCTL = (GPIOD_AHB->PCTL&0xFFFF0000) | 0x0000FFFF; // tabla p.688
    //GPIOD_AHB->PCTL &= 0xFFFF0000;
    //GPIOD_AHB->PCTL |= 0x0000FFFF; // tabla p.688
    GPIOD_AHB->DEN |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
    //                MISO    MOSI    CS    SCLK

   // GPIOD_AHB->DATA |= (1<<5); //registrar CS
    //GPIOB->PUR |= (0<<7)|(0<<6)|(0<<5)|(0<<4);
    //GPIOB->PDR |= (0<<7)|(0<<6)|(0<<5)|(0<<4);
    //GPIOB->AMSEL |= (0<<7)|(0<<6)|(0<<5)|(0<<4);
    
    SSI2->CR1 = (0<<1); //SSE=0 deshabilitar modulo
    SSI2->CR1 = (0<<2); //MS = 0 modo maestro
    SSI2->CC = (0x0<<0); //system clock = 50MHz
    //SSInClk = SysClk / (CPSDVSR * (1 + SCR))
    //2 500 000 = 50 000 000/(2*(1+SCR))
    // SCR = (50 000 000/2 500 000*2) - 1 = 9
    SSI2->CPSR =0x2; // 2.5 MHZ
    SSI2->CR0 = (0x9<<8) | 0x07; // datos de 8 bits
    SSI2->CR1 |= (1<<1); //SSE=1 habilitar modoulo p.961 (0x02)
}

extern void SPI_write(uint8_t data)
{
    while (SSI2->SR & 0x2)
    {
        SSI2->DR = (uint16_t)data;
    }
    
}

extern void SPI_write_data(uint8_t reg, uint8_t data)
{
    GPIOD_AHB->DATA &= ~(1<<3); // CS = 0 se niega
    SPI_write(reg & ~0x80); //escribir registro + MSB igualado a cero
    SPI_write(data);
    GPIOD_AHB->DATA |= (1<<3); //CS = 1
}

extern uint8_t SPI_read(void)
{
    uint8_t data = 0;
    while ((SSI2->SR & 0x10) == 0x10); // espera por busy bit
    data = SSI2->DR;
    return data;
}

extern uint8_t SPI_read_data(uint8_t reg)
{
    uint8_t data = 0;
    GPIOD_AHB->DATA &= ~(1<<3); // CS = 0
    SPI_write(reg | 0x80); // escribe registro + MSB
    SPI_write(0x00); //escribir dato para generar señal de reloj
    data = SPI_read(); //leer dato
    GPIOD_AHB->DATA |= (1<<3); //CS = 1
    return data;
}
