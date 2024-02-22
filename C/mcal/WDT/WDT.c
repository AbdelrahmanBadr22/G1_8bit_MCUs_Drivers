/**
 * @file WDT.c
 * @author Mohamed Refat
 * @brief
 * @version 0.1
 * @date 2024-02-22
 *
 */

#include "../../common/Config.h"
#include "../../common/Registes.h"
#include "../../common/Types.h"
#include "../../common/Utils.h"
#include "WDT.h"


/* Helper Function Like Macros */
#define Enable_WDT() (SET_BIT(WDTCR, WDTCR_WDE))

#define Disable_WDT() (WDTCR = 0b00011000);\
                      (WDTCR = 0)


/* Static Function To Set the time out value of WDT */
static error_t helper_SetTimeOut(WDT_TimeOut timeOut);

/* WDT Function Implementation */
void WDT_Enable(void)
{
    #if IS_AVR()
    Enable_WDT();
    #endif
}
error_t WDT_SetTimeOut(WDT_TimeOut timeOut)
{
    error_t kErrorState = kNoError;
    #if IS_AVR()
    kErrorState = helper_SetTimeOut(timeOut);
    #endif
    return kErrorState;

}

void WDT_Disable(void)
{
    #if IS_AVR()
    Disable_WDT();
    #endif
}


/********* STATIC FUNCTION **********/
static error_t helper_SetTimeOut(WDT_TimeOut timeOut)
{
    error_t kErrorState = kNoError;
    switch (timeOut)
    {
        case WDT_16ms3:
        CLR_BIT(WDTCR, WDTCR_WDP0);
        CLR_BIT(WDTCR, WDTCR_WDP1);
        CLR_BIT(WDTCR, WDTCR_WDP2);
        break;

        case WDT_32ms5:
        SET_BIT(WDTCR, WDTCR_WDP0);
        CLR_BIT(WDTCR, WDTCR_WDP1);
        CLR_BIT(WDTCR, WDTCR_WDP2);
        break;

        case WDT_65ms:
        CLR_BIT(WDTCR, WDTCR_WDP0);
        SET_BIT(WDTCR, WDTCR_WDP1);
        CLR_BIT(WDTCR, WDTCR_WDP2);
        break;

        case WDT_0s13:
        SET_BIT(WDTCR, WDTCR_WDP0);
        SET_BIT(WDTCR, WDTCR_WDP1);
        CLR_BIT(WDTCR, WDTCR_WDP2);
        break;

        case WDT_0s26:
        CLR_BIT(WDTCR, WDTCR_WDP0);
        CLR_BIT(WDTCR, WDTCR_WDP1);
        SET_BIT(WDTCR, WDTCR_WDP2);
        break;

        case WDT_0s52:
        SET_BIT(WDTCR, WDTCR_WDP0);
        CLR_BIT(WDTCR, WDTCR_WDP1);
        SET_BIT(WDTCR, WDTCR_WDP2);
        break;

        case WDT_1s0:
        CLR_BIT(WDTCR, WDTCR_WDP0);
        SET_BIT(WDTCR, WDTCR_WDP1);
        SET_BIT(WDTCR, WDTCR_WDP2);
        break;

        case WDT_2s1:
        SET_BIT(WDTCR, WDTCR_WDP0);
        SET_BIT(WDTCR, WDTCR_WDP1);
        SET_BIT(WDTCR, WDTCR_WDP2);
        break;

        default: kErrorState = kFunctionParameterError;
    }
    return kErrorState;
}
