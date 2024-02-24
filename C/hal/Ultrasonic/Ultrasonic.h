#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

typedef struct
{
    port_t port;
    pin_t triggerPin;
    pin_t echoPin;
}Ultrasonic_t;

error_t Ultrasonic_Init(Ultrasonic_t * pUSConfig);
float Ultrasonic_GetDistance(Ultrasonic_t * pUSConfig);
#endif //ULTRASONIC_H_
