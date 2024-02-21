#include "../../common/Types.h"
#include "../../common/Utils.h"
#include "../../mcal/GPIO/GPIO.h"
#include "SevenSegment.h"

error_t SevenSegment_Init(sevenSegment_t*pSevenSeg)
{
    error_t retErrorState = kNoError;
	/* Make sure that the sevenSegment_t is  valid */
	if (pSevenSeg!= NULL)
    {
        for (uint8_t i = 0 ; i < TOTAL_PINS  ; i++)
        {
           GPIO_SetPinDirection(pSevenSeg->segment[i].port,
           pSevenSeg->segment[i].pin, kOutput);
        }
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;

}

error_t SevenSegment_Set(sevenSegment_t * pSevenSeg, uint8_t number)
{
    error_t retErrorState = kNoError;
    if (pSevenSeg!= NULL && number<=MAX_NUM)
    {
         switch (number)
        {
            case 0:
                SetNumber(pSevenSeg, ZERO);
                break;
            case 1:
                SetNumber(pSevenSeg, ONE);
                break;
            case 2:
                SetNumber(pSevenSeg, TWO);
                break;
            case 3:
                SetNumber(pSevenSeg, THREE);
                break;
            case 4:
                SetNumber(pSevenSeg, FOUR);
                break;
            case 5:
                SetNumber(pSevenSeg, FIVE);
                break;
            case 6:
                SetNumber(pSevenSeg, SIX);
                break;
            case 7:
                SetNumber(pSevenSeg, SEVEN);
                break;
            case 8:
                SetNumber(pSevenSeg, EIGHT);
                break;
            case 9:
                SetNumber(pSevenSeg, NINE);
                break;
        }
    }
    else
    {
      retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}

static void SetNumber(sevenSegment_t * pSevenSeg, uint8_t number)
{
    for (uint8_t i =0;i<TOTAL_PINS;i++)
    {
        GPIO_SetPinValue(pSevenSeg->segment[i].port,
                         pSevenSeg->segment[i].pin,
                         GET_BIT(number, i));
    }
}
