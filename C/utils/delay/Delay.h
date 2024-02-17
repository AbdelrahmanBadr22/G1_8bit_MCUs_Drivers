/*
 * We have three ways to implement the delay :
 * ------------------------------------------
 *    1) Using built-in function: This will done by including the built-in lib
 *       for the target and use the built-in function directly.
 *
 *    2) Using busy wait with assembly instructions: This is the same
 *       implementation as built-in function but without including built-in lib
 *
 *    3) Using timer: We can generate a delay by interfacing with timer and
 *       wait for specific time
 *
 * This infrastructure support three ways according to 'DELAY_METHOD' macro
 * with three appropiate values 'DELAY_BUILTIN, DELAY_BUSYWAIT, DELAY_TIMER'
*/
#ifndef _DELAY_H_
#define _DELAY_H_

#include "Types.h"

#define DELAY_BUILTIN       (1)
#define DELAY_BUSYWAIT      (2)
#define DELAY_TIMER         (3)

#define DELAY_METHOD        (DELAY_BUILTIN)
#if DELAY_METHOD != DELAY_BUILTIN
#if DELAY_METHOD != DELAY_BUSYWAIT
#if DELAY_METHOD != DELAY_TIMER
#error "[Delay]: Invalid value for DELAY_METHOD macro"
#endif   // DELAY_METHOD != DELAY_TIMER
#endif   // DELAY_METHOD != DELAY_BUSYWAIT
#endif   // DELAY_METHOD != DELAY_BUILTIN

void Delay_ms(const uint16 ms);
// TODO(): Support delay_us
#endif  // _DELAY_H_
