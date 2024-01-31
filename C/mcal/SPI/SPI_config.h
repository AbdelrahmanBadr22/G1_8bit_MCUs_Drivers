#ifndef SPI_CONF_H
#define SPI_CONF_H
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
