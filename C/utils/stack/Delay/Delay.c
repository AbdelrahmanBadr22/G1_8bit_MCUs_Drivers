#include "../../common/Config.h"
#include "../../common/Registes.h"
#include "../../common/Types.h"
#include "../../common/Utils.h"
#include "../../../mcal/TIMER/TIMER_Interface.h"
#include "../../../mcal/TIMER/TIMER_Private.h"
#include "Delay.h"

void delay10ms()
{
    #if MCU_TYPE == _AVR
    /*prescaler 1024*/
    SET_BIT(TCCR0, TCCR0_CS02);
    CLR_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS00);
    /*10ms*/
    TCNT0 = 0xB2;
    while (GET_BIT(TIFR, TIFR_TV0) == 0);
    TCCR0 = 0;
    SET_BIT(TIFR, TIFR_TV0);
    #endif
}
