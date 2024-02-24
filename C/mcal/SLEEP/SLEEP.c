#include "../../common/Config.h"
#include "../../common/Registes.h"
#include "../../common/Types.h"
#include "../../common/Utils.h"
#include "SLEEP.h"

error_t SLEEP(uint8_t mode)
{
    error_t kErrorState = kNoError;
    #if IS_AVR()
    /*Enable Sleeping*/
    SET_BIT(MCUCR_REG, MCUCR_SE);
    /*Set Mode*/
    switch (mode)
    {
        case IDLE_MODE :
        CLR_BIT(MCUCR_REG, MCUCR_SM2);
        CLR_BIT(MCUCR_REG, MCUCR_SM1);
        CLR_BIT(MCUCR_REG, MCUCR_SM0);
        break;
        case ADC_NOISE_REDUCTION_MODE :
        CLR_BIT(MCUCR_REG, MCUCR_SM2);
        CLR_BIT(MCUCR_REG, MCUCR_SM1);
        SET_BIT(MCUCR_REG, MCUCR_SM0);
        break;
        case POWER_DOWN_MODE :
        CLR_BIT(MCUCR_REG, MCUCR_SM2);
        SET_BIT(MCUCR_REG, MCUCR_SM1);
        CLR_BIT(MCUCR_REG, MCUCR_SM0);
        break;
        case POWER_SAVE_MODE :
        CLR_BIT(MCUCR_REG, MCUCR_SM2);
        SET_BIT(MCUCR_REG, MCUCR_SM1);
        SET_BIT(MCUCR_REG, MCUCR_SM0);
        break;
        case STANDBY_MODE :
        SET_BIT(MCUCR_REG, MCUCR_SM2);
        SET_BIT(MCUCR_REG, MCUCR_SM1);
        CLR_BIT(MCUCR_REG, MCUCR_SM0);
        break;
        case EXTENED_STANDBY_MODE :
        SET_BIT(MCUCR_REG, MCUCR_SM2);
        SET_BIT(MCUCR_REG, MCUCR_SM1);
        SET_BIT(MCUCR_REG, MCUCR_SM0);
        break;
        default: kErrorState = kFunctionParameterError;
    }
    #elif IS_PIC()
    switch (mode)
    {
        case SLEEP_MODE :
        CLR_BIT(OSCCON_REG, OSCCON_IDLEN);
        break;
        case PRI_RUN_MODE  :
        CLR_BIT(OSCCON_REG, OSCCON_SCS1);
        CLR_BIT(OSCCON_REG, OSCCON_SCS0);
        break;
        case SEC_RUN_MODE :
        CLR_BIT(OSCCON_REG, OSCCON_SCS1);
        SET_BIT(OSCCON_REG, OSCCON_SCS0);
        break;
        case RC_RUN_MODE :
        SET_BIT(OSCCON_REG, OSCCON_SCS1);
        break;
        case PRI_IDLE_MODE :
        SET_BIT(OSCCON_REG, OSCCON_IDLEN);
        CLR_BIT(OSCCON_REG, OSCCON_SCS1);
        CLR_BIT(OSCCON_REG, OSCCON_SCS0);
        break;
        case SEC_IDLE_MODE :
        SET_BIT(OSCCON_REG, OSCCON_IDLEN);
        CLR_BIT(OSCCON_REG, OSCCON_SCS1);
        SET_BIT(OSCCON_REG, OSCCON_SCS0);
        break;
        case RC_IDLE_MODE :
        SET_BIT(OSCCON_REG, OSCCON_IDLEN);
        SET_BIT(OSCCON_REG, OSCCON_SCS1);
        break;
        default: kErrorState = kFunctionParameterError;
    }
    #endif //MCU TYPE
    return kErrorState;
}
