#ifndef SPI_H
#define SPI_H

void SPI_MASTER_Init();
void SPI_SLAVE_Init();
error_t SPI_Write(uint8_t data);
error_t SPI_Read(uint8_t* data);

#endif
