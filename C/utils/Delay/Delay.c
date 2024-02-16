#include "../../common/Config.h"
#include "../../common/Registes.h"
#include "../../common/Types.h"
#include "../../common/Utils.h"
#include "../../../C/mcal/TIMER/TIMER_Interface.h"
#include "../../../C/mcal/TIMER/TIMER_Private.h"
#include "Delay.h"

static void Timer_Init()
{
    #if MCU_TYPE == _AVR
    /*timer0 CTC mode*/
    SET_BIT(TCCR0, TCCR0_WGM01);
    /*prescaler 64*/
    CLR_BIT(TCCR0, TCCR0_CS02);
    SET_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS00);
    /*compare match value for 1ms delay at 8MHz*/
    OCR0 = 125;
    #endif
}
void Delay_ms(uint16 delay)
{
    Timer_Init();

    for (uint16 counter =0; counter<delay; counter++)
    {
        #if MCU_TYPE == _AVR
        while (GET_BIT(TIFR, TIFR_OCF0) == 0)
        {

        }
        SET_BIT(TIFR, TIFR_OCF0);
        #endif
    }
}
