
#include "lib/include.h"
extern void Configurar_SSI2(void)
{
    
    SYSCTL->RCGCSSI |= (1<<2); //se activa el Modulo 2 SSI2
    SYSCTL->RCGCGPIO |= (1<<1);//Puerto b
    GPIOB->DIR |= (0<<4) | (1<<5) | (0<<6) | (1<<7); //selector es salida = 1
    GPIOB->AFSEL = (1<<4)|(1<<5)|(1<<6)|(1<<7); //antes del 4 al 7
    GPIOB->PCTL = (GPIOB->PCTL&0xFF0000FF) | 0x00222200; // tabla p.688
    //GPIOD_AHB->PCTL &= 0xFFFF0000;
    //GPIOD_AHB->PCTL |= 0x0000FFFF; // tabla p.688
    GPIOA->DEN |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
    //             CLK    CS    MISO    MOSI

   // GPIOD_AHB->DATA |= (1<<5); //registrar CS
    //GPIOB->PUR |= (0<<7)|(0<<6)|(0<<5)|(0<<4);
    //GPIOB->PDR |= (0<<7)|(0<<6)|(0<<5)|(0<<4);
    //GPIOB->AMSEL |= (0<<7)|(0<<6)|(0<<5)|(0<<4);
    
    SSI2->CR1 = (0<<1); //SSE=0 deshabilitar 
    SSI2->CR1 = (0<<2); //MS = 0 modo maestro
    SSI2->CC = (0x09<<0); //system clock = 16 o 20 MHz "DUDA EXISTENCIAL"
    //SSInClk = SysClk / (CPSDVSR * (1 + SCR)) //VALORES PROPUESTOS
    //4 MHZ = 20MHZ/(1*(1+4))
    // SCR = (50 000 000/2 500 000*2) - 1 = 4
    SSI2->CPSR =0x1; //VALOR DE CPSDVSR
    SSI2->CR0 = (0x4<<8) | (0x01<<6) | (0x01<<4) | (0x0B<<0) ; // datos de 12 bits //EL VALOR DE SCR = 0X04 y 0x01 es por la polaridad 1
    SSI2->CR1 |= (1<<1); //SSE=1 habilitar modoulo p.961 (0x02)
}

extern void WriteSPI(uint16_t dato) //16 o 12 bits DUDAAA
{
    SSI2->DR = (uint16_t)dato;
    while (SSI2->SR & (1<<0) == 0); //pila vacia, hasta que dato sea enviado
}


extern void SPI_write(uint8_t data)
{
    while (SSI2->SR & (1<<0) == 0); //pila vacia, hasta que dato sea enviado
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
