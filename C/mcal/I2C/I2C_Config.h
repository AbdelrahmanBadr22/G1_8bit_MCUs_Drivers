/**
 * @file I2C_Config.h
 * @author Mohamed Refat
 * @version 0.1
 * @date 2023-12-07
 */

#ifndef MCAL_I2C_I2C_CONFIG_H_
#define MCAL_I2C_I2C_CONFIG_H_

#ifndef F_CPU
#define F_CPU (8000000UL)
#endif

/**
 * @brief Set the Prescaler
 *  Options:
 *          I2C_PRESCALER_1
 *          I2C_PRESCALER_4
 *          I2C_PRESCALER_16
 *          I2C_PRESCALER_64
 */
#define I2C_PRESCALER (I2C_PRESCALER_1)
#endif /* MCAL_I2C_I2C_CONFIG_H_ */
