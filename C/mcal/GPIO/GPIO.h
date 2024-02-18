#ifndef GPIO_H
#define GPIO_H

typedef enum
{
    kPORTA,
    kPORTB,
    kPORTC,
    kPORTD,
    #if IS_PIC()
    kPORTE,
    #endif // MCU_TYPE
}port_t;

typedef enum
{
    kPIN0,
    kPIN1,
    kPIN2,
    kPIN3,
    kPIN4,
    kPIN5,
    kPIN6,
    kPIN7
}pin_t;

typedef enum
{
    kLow,
    kHigh
}state_t;

typedef enum
{
    kInput,
    kOutput
}direction_t;


typedef enum
{
    kOutput_PORT = 0xff,
    kInput_PORT  = 0x00
}port_direction_t;

error_t GPIO_SetPinDirection(port_t pPortNumber,
                             pin_t pin,
                             direction_t direction);

error_t GPIO_SetPinValue(port_t portNumber,
                         pin_t pinNumber,
                         state_t pintVoltageLevel);

error_t GPIO_GetPinValue(port_t portNumber,
                         pin_t pinNumber,
                         state_t * state);

error_t GPIO_SetPortDirection(port_t portNumber, uint8_t portValue);

error_t GPIO_SetPortValue(port_t portNumber,
                          uint8_t pintVoltageLevel);

error_t GPIO_GetPortValue(port_t portNumber,
                          uint8_t * state);

error_t GPIO_SetPinPullup(port_t portNumber,
                          pin_t pinNumber);


error_t GPIO_SetLowNibbleValue(port_t portNumber,
                               uint8_t value);

error_t GPIO_SetHighNibbleValue(port_t portNumber,
                                uint8_t value);

error_t GPIO_SetHighNibbleDirection(port_t portNumber,
                                    uint8_t direction);

error_t GPIO_SetLowNibbleDirection(port_t portNumber,
                                   uint8_t direction);
#endif /* _GPIO_H_ */
