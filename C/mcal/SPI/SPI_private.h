#ifndef SPI_PRV_H
#define SPI_PRV_H


#define SPCR_SPR0       (0)
#define SPCR_SPR1       (1)
#define SPCR_CPHA       (2)
#define SPCR_CPOL       (3)
#define SPCR_MSTR       (4)
#define SPCR_DORD       (5)
#define SPCR_SPE        (6)
#define SPCR_SPIE       (7)

#define SPSR_SPIF       (7)
#define SPSR_SPI2X      (0)

#define CLK_4           (0)
#define CLK_16          (1)
#define CLK_64          (2)
#define TMR2_OUTPUT_2   (3)

#define MODE_1          (0)
#define MODE_2          (1)
#define MODE_3          (2)
#define MODE_4          (3)

#define END             (0)
#define MIDDLE          (1)

#define ENABLE          (0)
#define DISABLE         (1)

void AVR_Config_Helper();
void PIC_Config_Helper();
#endif
