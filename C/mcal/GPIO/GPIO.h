#ifndef _GPIO_H_
#define _GPIO_H_

typedef enum  {
    kLow,
    kHigh
}state_t;

typedef enum  {
    kInput,
    kOutput
}direction_t;


error_t GPIO_SetPinDirection(port_t pPortNumber,pin_t pin , direction_t direction);
error_t GPIO_SetPinValue(port_t PortNumber , pin_t PinNumber , state_t PintVoltageLevel);
error_t GPIO_GetPinValue(port_t PortNumber , pin_t PinNumber,state_t * state); 
error_t GPIO_SetPortDirection(port_t PortNumber, uint8_t direction); 
error_t GPIO_SetPortValue(port_t PortNumber, uint8_t PintVoltageLevel); 
error_t GPIO_GetPortValue(port_t PortNumber ,uint8_t * state);

#endif /* _GPIO_H_ */
