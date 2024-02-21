/**
 * @file DC_Motor.h
 * @author Manar(manar.abdelraouf24@gmail.com)
 * @brief DC Motor Driver
 * @version 0.1
 * @date 2023-08-09
 */
#ifndef DC_MOTOR_H
#define DC_MOTOR_H

/**
 * @brief structuer to represent DC Motor
 */
typedef struct
{
    port_t port; /**< the port of DC Motor        */
    pin_t pin1;  /**< the pin1 indicates IN1  pin */
    pin_t pin2;  /**< the pin1 indicates IN2  pin */
}DcMotor_t;
/**
 * @brief THis Function is Set Motor Pin as output Pin
 * @param DcMotor Pointer to Motor Which is initialized
 * @return error_t Return 0 if DcMotor is Point to NULL
 */
error_t DcMotor_Init(DcMotor_t * DcMotor);
/**
 * @brief This Function is Make Motor Return ClockWise
 * @param DcMotor Pointer to Motor Which is initialized
 * @return error_t error_t Return 0 if DcMotor is Point to NULL
 */
error_t DcMotor_ClockWise(DcMotor_t * DcMotor);
/**
 * @brief This Function is Make Motor Return AntiClockWise
 * @param DcMotor Pointer to Motor Which is initialized
 * @return error_t error_t Return 0 if DcMotor is Point to NULL
 */
error_t DcMotor_AntiClockWise(DcMotor_t * DcMotor);
/**
 * @brief This Function is Make Motor Stop
 * @param DcMotor Pointer to Motor Which is initialized
 * @return error_t error_t Return 0 if DcMotor is Point to NULL
 */
error_t DcMotor_Stop(DcMotor_t * DcMotor);

#endif
