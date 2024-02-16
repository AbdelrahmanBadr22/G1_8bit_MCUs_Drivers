#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#define STEPPER_FULLSTEP          (1)
#define STEPPER_HALFSTEP          (0)

#define STEPPER_SPEED             (2)
/**
 * @brief structuer to represent Stepper Motor
 */
typedef struct StepperMotor_t
{
    port_t port;
    pin_t bluePin;
    pin_t pinkPin;
    pin_t yellowPin;
    pin_t orangePin;
}StepperMotor_t;
/**
 * @brief THis Function is initiate StepperMotor
 * @param pStepper Pointer to StepperMotor
 * @return error_t Return 0 if pStepper is Pointer to NULL
 */
error_t Stepper_Init(StepperMotor_t * pStepper);
/**
 * @brief This Function is Make Motor Return ClockWise
 * @param pStepper Pointer to Motor
 *        type options :1-STEPPER_FULLSTEP
 *                      2-STEPPER_HALFSTEP
 * @return error_t  Return 0 if pStepper is Pointer to NULL
 */
void Stepper_ClockWise(StepperMotor_t* pStepper, uint8_t type, uint8_t degree);
/**
 * @brief This Function is Make Motor Return AntiClockWise
 * @param pStepper Pointer to Motor
 *        type options :1-STEPPER_FULLSTEP
 *                      2-STEPPER_HALFSTEP
 * @return  error_t Return 0 if pStepper is Pointer to NULL
 */
void Stepper_AntiClockWise(StepperMotor_t* pStepper,
                           uint8_t type, uint8_t degree);
/**
 * @brief This Function is to TurnOff StepperMotor
 * @param pStepper Pointer to StepperMotor
 * @return error_t Return 0 if pStepper  is Pointer to NULL
 */
error_t Stepper_Stop(StepperMotor_t * pStepper);
void ClockWiseFullStep(StepperMotor_t * pStepper);
void ClockWiseHalfStep(StepperMotor_t * pStepper);
void AntiClockWiseFullStep(StepperMotor_t * pStepper);
void AntiClockWiseHalfStep(StepperMotor_t * pStepper);
#endif
