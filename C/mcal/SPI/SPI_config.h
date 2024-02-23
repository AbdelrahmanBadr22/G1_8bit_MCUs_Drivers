#ifndef SPI_CONF_H
#define SPI_CONF_H

#define SPI_TIMEOUT (1000)
/**
* options: 1-MSB_FIRST
* 2-LSB_FIRST
*/
#define SPI_DATA_ORDER (MSB_FIRST)

/**
* options: 1-IDLE_LOW
* 2-IDLE_HIGH
*/
#define SPI_CLK_POLARITY (IDLE_LOW)
/**
* options: 1-SAMPLE_FIRST
* 2-SETUP_FIRST
*/
#define SPI_CLK_PHASE (SAMPLE_FIRST)
/**
* options: 1-INTERRUPT_ENABLE
* 2-INTERRUPT_DISABLE
*/
#define SPI_INTERRUPT (INTERRUPT_DISABLE)
/**
* options: 1-CLK_4
* 2-CLK_16
* 3-CLK_64
* 4-TMR2_output_2
*/
#define SPI_CLK_MODE (CLK_4)
/**
* options: 1-ENABLE
* 2-DISABLE
*/
#define SPI_SS_MODE (ENABLE)
/**
* options: 1-MODE_1
* 2-MODE_2
* 3-MODE_3
* 4-MODE_4
*/
#define SPI_MODE (MODE_1)
/**
* options: 1-END
* 2-MIDDLE
*/
#define SPI_SAMPLE_MODE (MIDDLE)

#if SPI_DATA_ORDER != MSB_FIRST
#if SPI_DATA_ORDER != LSB_FIRST
#error "[SPI_config]: Invalid data order"
#endif
#endif

#if SPI_CLK_POLARITY != IDLE_LOW
#if SPI_CLK_POLARITY != IDLE_HIGH
#error "[SPI_config]: Invalid clock polarity"
#endif
#endif

#if SPI_CLK_PHASE != SAMPLE_FIRST
#if SPI_CLK_PHASE != SETUP_FIRST
#error "[SPI_config]: Invalid clock phase"
#endif
#endif

#if SPI_INTERRUPT != MSB_FIRST
#if SPI_INTERRUPT != LSB_FIRST
#error "[SPI_config]: Invalid data order"
#endif
#endif

#if SPI_CLK_MODE != CLK_4
#if SPI_CLK_MODE != CLK_16
#if SPI_CLK_MODE != CLK_64
#if SPI_CLK_MODE != TMR2_output_2
#error "[SPI_config]: Invalid clock mode"
#endif
#endif
#endif
#endif

#if SPI_SS_MODE != ENABLE
#if SPI_SS_MODE != DISABLE
#error "[SPI_config]: Invalid SS Mode"
#endif
#endif

#if SPI_MODE != MODE_1
#if SPI_MODE != MODE_2
#if SPI_MODE != MODE_3
#if SPI_MODE != MODE_4
#error "[SPI_config]: Invalid spi mode"
#endif
#endif
#endif

#if SPI_SAMPLE_MODE != END
#if SPI_SAMPLE_MODE != MIDDLE
#error "[SPI_config]: Invalid sample mode"
#endif
#endif

#endif
#endif
