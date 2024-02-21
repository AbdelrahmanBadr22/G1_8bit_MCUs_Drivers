#ifndef PushButton_H
#define PushButton_H

typedef enum
{
    kNotPressed,
    kPressed,
}PressedState_t;

typedef enum
{
    kIntPullUp,
    kExtPullUp,
    kPullDown,
}PullState_t;

/**
 * @brief PushButton_t : is the data type to define the Push Button
 *        port  : for avr [kPORTA ... kPORTD], for pic [kPORTA ... kPORTE]
 *        pin   : [kPIN0 ... kPIN7]
 *        state : [kIntPullUp, KExtPullUp, kPullDown]
 */
typedef struct
{
    port_t port;
    pin_t pin;
    PullState_t state;
}PushButton_t;
/**
 * @brief This Function is used to initialize the Push Button
 *
 * @param pPB :pointer to the PB which is a struct from type @PushButton_t
 */
void PushButton_Init(PushButton_t* pPB);
/**
 * @brief This Function is used to get wether the Push Button is pressed or not
 *
 * @param pPB :pointer to the PB which is a struct from type @PushButton_t
 * @return PressedState_t : could be kNotPressed or kPressed
 */
PressedState_t PushButton_GetValue(PushButton_t* pPB);
#endif
