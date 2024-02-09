#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

typedef struct ultrasonic
{
    port_t port;
    pin_t triggerPin;
    pin_t echoPin;
}Ultrasonic_t;

error_t UltrasonicInit(Ultrasonic_t * pUS, uint8_t kMode, uint8_t kClock, uint8_t kInterruptSource);
error_t UltrasonicTrigger(Ultrasonic_t * pUS);
//error_t UltrasonicDistance(Ultrasonic_t * pUS);
#endif
