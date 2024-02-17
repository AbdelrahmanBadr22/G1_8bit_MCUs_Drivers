/**
 * @file SERVO_Interface.h
 * @author Mohamed Refat
 * @brief
 * @version 0.1
 * @date 2024-02-11
 *
 */

#ifndef HAL_08_SERVO_SERVO_INTERFACE_H_
#define HAL_08_SERVO_SERVO_INTERFACE_H_

#define SERVO_OC1A_PIN (0)
#define SERVO_OC1B_PIN (1)

/**
 * @brief This function is used to init the Servo Motor
 *
 * @param kChannel OPTIONS: [ SERVO_OC1A_PIN , SERVO_OC1B_PIN ]
 * @return error_t
 * @note : Ther servo is implemented to work only on PORTD Pin[4,5] PWM Pins
 *
 */
error_t Servo_Init(uint8_t kChannel);
/**
 * @brief This function is used to set the Servo Motor angle
 *
 * @param copyAngle [ 0 : 180 ]
 * @param kChannel  OPTIONS: [ SERVO_OC1A_PIN , SERVO_OC1B_PIN ]
 * @return error_t
 */
error_t Servo_SetAngle(uint8_t copyAngle, uint8_t kChannel);
#endif /* HAL_08_SERVO_SERVO_INTERFACE_H_ */
