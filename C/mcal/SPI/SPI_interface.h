#ifndef SPI_H
#define SPI_H

#define SSPCON1_SSMP0       (0)
#define SSPCON1_SSMP1       (1)
#define SSPCON1_SSMP2       (2)
#define SSPCON1_SSMP3       (3)
#define SSPCON1_CKP         (4)
#define SSPCON1_SSPEN       (5)

#define SSPSTAT_BF          (0)
#define SSPSTAT_CKE         (6)
#define SSPSTAT_SMP         (7)

#define TRISC_TRISC3        (3)
#define TRISC_TRISC4        (4)
#define TRISC_TRISC5        (5)

#define TRISA_TRISA5        (5)

#define PIR1_SSPIF          (3)

void SPI_MASTER_Init();
void SPI_SLAVE_Init();
void SPI_Write(uint8_t Data);
uint8_t SPI_Read();
#endif
