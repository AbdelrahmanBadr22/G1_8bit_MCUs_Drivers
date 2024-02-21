#include "../../common/Types.h"
#include "../../mcal/GPIO/GPIO.h"
#include "PushButton.h"

void PushButton_Init(PushButton_t* pPB)
{
    GPIO_SetPinDirection(pPB->port, pPB->pin, pPB->state);
}

PressedState_t PushButton_GetValue(PushButton_t* pPB)
{
    state_t pinValue = 0;
  PressedState_t pressState = 0;
  if ((pPB->state == kIntPullUp)|| (pPB->state == kExtPullUp))
  {
    GPIO_GetPinValue(pPB->port, pPB->pin, &pinValue);
    pressState = pinValue == kHigh ? kNotPressed : kPressed;
  }
  else if (pPB->state == kPullDown)
  {
    GPIO_GetPinValue(pPB->port, pPB->pin, &pinValue);
    pressState = pinValue == kHigh ? kPressed : kNotPressed;
  }
  return pressState;
}
