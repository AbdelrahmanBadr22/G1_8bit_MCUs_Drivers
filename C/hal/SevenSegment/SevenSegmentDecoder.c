#include "Types.h"
#include "Utils.h"
#include "GPIO.h"
#include "SevenSegmentDecoder.h"


error_t SevenSegmentDecoder_Init(sevenSegDecoder_t * pSevenSeg)
{
    error_t retErrorState = kNoError;
	/* Make sure that the sevenSegDecoder_t is  valid */
	if (pSevenSeg!= NULL)
    {
        for (uint8_t i = 0 ; i < TOTAL_DECODER_PINS ; i++)
        {
           GPIO_SetPinDirection(pSevenSeg->segment[i].port,
                                pSevenSeg->segment[i].pin,
                                kOutput);
        }
    }
    else
    {
      retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}

error_t SevenSegmentDecoder_Set( sevenSegDecoder_t* pSevenSeg, uint8_t number)
{
    error_t retErrorState = kNoError;
    /* Make sure that the sevenSegDecoder_t is  valid  and number is in range*/
	if ((pSevenSeg != NULL) && (number <= MAX_NUM))
    {
        for (uint8_t i =0; i < TOTAL_DECODER_PINS ; i++)
        {
            GPIO_SetPinValue(pSevenSeg->segment[0].port,
                             pSevenSeg->segment[0].pin,
                             GET_BIT(number, i));
        }
    }
    else
    {
     retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
