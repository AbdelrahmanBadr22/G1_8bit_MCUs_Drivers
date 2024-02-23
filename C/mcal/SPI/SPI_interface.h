#ifndef SPI_H
#define SPI_H

#if IS_PIC()

#define CLK_4 (0)
#define CLK_16 (1)
#define CLK_64 (2)
#define TMR2_OUTPUT_2 (3)

#define MODE_1 (0)
#define MODE_2 (1)
#define MODE_3 (2)
#define MODE_4 (3)

#define END (0)
#define MIDDLE (1)

/*bits*/
#define SSPCON1_SSMP0 (0)
#define SSPCON1_SSMP1 (1)
#define SSPCON1_SSMP2 (2)
#define SSPCON1_SSMP3 (3)
#define SSPCON1_CKP (4)
#define SSPCON1_SSPEN (5)

#define SSPSTAT_BF (0)
#define SSPSTAT_CKE (6)
#define SSPSTAT_SMP (7)

#define TRISC_TRISC3 (3)
#define TRISC_TRISC4 (4)
#define TRISC_TRISC5 (5)

#define TRISA_TRISA5 (5)

#define PIR1_SSPIF (3)

#elif IS_AVR()

#define LSB_FIRST (0)
#define MSB_FIRST (1)

#define SAMPLE_FIRST (0)
#define SETUP_FIRST (1)

#define IDLE_LOW (0)
#define IDLE_HIGH (1)
/*bits*/
#define SPCR_SPR0 (0)
#define SPCR_SPR1 (1)
#define SPCR_CPHA (2)
#define SPCR_CPOL (3)
#define SPCR_MSTR (4)
#define SPCR_DORD (5)
#define SPCR_SPE (6)
#define SPCR_SPIE (7)

#define SPSR_SPIF (7)
#define SPSR_SPI2X (0)

#endif

#define ENABLE (0)
#define DISABLE (1)

#define INTERRUPT_DISABLE (0)
#define INTERRUPT_ENABLE (1)

void SPI_MASTER_Init();
void SPI_SLAVE_Init();
error_t SPI_Write(uint8_t data);
error_t SPI_Read(uint8_t* data);

#endif
