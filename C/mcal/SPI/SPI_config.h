#ifndef SPI_CONF_H
#define SPI_CONF_H

#define SPI_TIMEOUT             (1000)
/**
 * options:         1-MSB_FIRST
 *                  2-LSB_FIRST
*/
#define SPI_DATA_ORDER         (MSB_FIRST)
/**
 * options:         1-IDLE_LOW
 *                  2-IDLE_HIGH
*/
#define SPI_CLK_POLARITY         (IDLE_LOW)
/**
 * options:         1-SAMPLE_FIRST
 *                  2-SETUP_FIRST
*/
#define SPI_CLK_PHASE         (SAMPLE_FIRST)
/**
 * options:         1-INTERRUBT_ENABLE
 *                  2-INTERRUBT_DISABLE
*/
#define SPI_INTERRUBT         (INTERRUBT_DISABLE)
/**
 * options:         1-CLK_4
 *                  2-CLK_16
 *                  3-CLK_64
 *                  4-TMR2_output_2
*/
#define SPI_CLK_MODE            (CLK_4)
/**
 * options:         1-ENABLE
 *                  2-DISABLE
*/
#define SPI_SS_MODE             (ENABLE)
/**
 * options:         1-MODE_1
 *                  2-MODE_2
 *                  3-MODE_3
 *                  4-MODE_4
*/
#define SPI_MODE                (MODE_1)
/**
 * options:         1-END
 *                  2-MIDDLE
*/
#define SAMPLE_MODE             (MIDDLE)
#endif
