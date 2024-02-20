/**
 * @file I2C_Config.h
 * @author Mohamed Refat
 * @version 0.1
 * @date 2023-12-07
 */

#ifndef MCAL_I2C_I2C_CONFIG_H_
#define MCAL_I2C_I2C_CONFIG_H_

#if IS_AVR()
/**
 * @brief Set the Prescaler
 *  OPTIONS:
 *          I2C_PRESCALER_1
 *          I2C_PRESCALER_4
 *          I2C_PRESCALER_16
 *          I2C_PRESCALER_64
 */
#define I2C_PRESCALER (I2C_PRESCALER_1)
#if I2C_PRESCALER != I2C_PRESCALER_1
#if I2C_PRESCALER != I2C_PRESCALER_4
#if I2C_PRESCALER != I2C_PRESCALER_16
#if I2C_PRESCALER != I2C_PRESCALER_64
#error  "[I2C_Config]: Invalid value for I2C_PRESCALER macro"
#endif //I2C_PRESCALER != I2C_PRESCALER_64
#endif //I2C_PRESCALER != I2C_PRESCALER_16
#endif //I2C_PRESCALER != I2C_PRESCALER_4
#endif //I2C_PRESCALER != I2C_PRESCALER_1

#elif IS_PIC()
/**
 * @brief  Set SLEW RATE
 * OPTIONS: STANDARD_SPEED_100K_1M
 *          HIGH_SPEED_400K
*/
#define SLEW_RATE  (STANDARD_SPEED_100K_1M )
#if SLEW_RATE != STANDARD_SPEED_100K_1M
#if SLEW_RATE!= HIGH_SPEED_400K
#error  "[I2C_Config]: Invalid value for Selw Rate macro"
#endif //SLEW_RATE != HIGH_SPEED_400K
#endif //SLEW_RATE != STANDARD_SPEED_100K_1M

/**
 * @brief  Set SMBus
 * OPTIONS: ENABLED
 *          DISABLED
*/
#define SMBus  (DISABLED )
#if SMBus != DISABLED
#if SMBus != ENABLED
#error  "[I2C_Config]: Invalid value for SMBus"
#endif //SMBus != ENABLED
#endif //SMBus != DISABLED

#endif /*MCU TYPE*/
#endif /* MCAL_I2C_I2C_CONFIG_H_ */
