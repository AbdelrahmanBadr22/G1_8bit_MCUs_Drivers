#include "Config.h"
#include "Types.h"
#include "Delay.h"
#include "TIMER_Interface.h"

// Include built-in library only if needed
#if DELAY_METHOD == DELAY_BUILTIN
#if IS_AVR()
#include <util/delay.h>
#define BUILTIN_DELAY_MS(ms_)       _delay_ms(ms_);
#define DEC_INST                    "1: sbiw %0,1"     
#define RETURN_BACK_INST            "brne 1b"           
#elif IS_PIC()
#include <builtins.h>
#define BUILTIN_DELAY_MS(ms_)       __delay_ms(ms_);
#define DEC_INST                    "1: decfsz %0,1"
#define RETURN_BACK_INST            "goto 1b"
#endif // IS_AVR()
#endif // DELAY_METHOD

static void delay_dump_asm(uint16 __count) 
{
    __asm__ volatile (
    	DEC_INST "\n\t"
    	RETURN_BACK_INST
    	: "=w" (__count)
    	: "0" (__count)
    );
}
static void delay_busywait_(uint16 ms_) 
{
    uint16 __ticks = 0;
    uint16 __count = 0;
    // As we have 4 cycles in one millisecond then we have to find the number 
    // of clock cycles required.
    // MS = (C/F) ∗ 1000
    // MS: is the time in milliseconds (ms)         
    // C : is the number of cycles
    // F : is the frequency of the CPU in Hertz (Hz)
    // See https://calculator.academy/cycles-to-ms-calculator/ 
	double __tmp = ((F_CPU) / 4e3) * ms_;
	
	if (__tmp > 65535)
	{
		//	__ticks = requested delay in 1/10 ms
		__ticks = (uint16_t) (ms_ * 10.0);
		while(__ticks)
		{
			// wait 1/10 ms
			__count = ((F_CPU) / 4e3) / 10;
            delay_dump_asm(__count);
			__ticks --;
		}
		return;     // EXIT
	}
    // If the number of required clock cycles is less than one cycle then
    // consider it as one cycle
    __ticks = __tmp < 1.0 ? 1 : (uint16_t)__tmp;
    delay_dump_asm(__ticks);
}

static void delay_timer_(uint16 ms_) 
{
    TIMER0_Init(TIMER_CTC_MODE, F_CPU);
    TIMER0_SetPreScalar();
    TIMER0_SetCTC(125);
}
void Delay_ms(uint16 ms) 
{
    #if DELAY_METHOD == DELAY_BUILTIN
    BUILTIN_DELAY_MS(ms);
    #elif DELAY_METHOD == DELAY_BUSYWAIT
    delay_busywait_(ms);
    #elif DELAY_METHOD == DELAY_TIMER
    delay_timer_(ms);
    #else
    #error "[Delay]: Unreachable code
    #endif 
}