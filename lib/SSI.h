#ifndef SPI_SPI_H_
#define SPI_SPI_H_

extern void Configurar_SSI2(void);
extern void SPI_write(uint8_t data);
extern void SPI_write_data(uint8_t reg, uint8_t data);
extern uint8_t SPI_read(void);
extern uint8_t SPI_read_data(uint8_t reg);

#endif /* SPI_SPI_H_ */


