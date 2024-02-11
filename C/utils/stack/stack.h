#ifndef _STACK_H_
#define _STACK_H_

#include "stack_macros.h"

// --------------------
// Define Stack type
// --------------------

Stack_t(char)
Stack_t(uint32_t)
Stack_t(sint32_t)
Stack_t(f32_t)

// --------------------
// Functions prototype
// --------------------
DEC_Stack_Init(char)
DEC_Stack_Push(char)
DEC_Stack_Pop(char)
DEC_Stack_GetSize(char)
DEC_Stack_GetTop(char)
DEC_Stack_Clear(char)

DEC_Stack_Init(uint32_t)
DEC_Stack_Push(uint32_t)
DEC_Stack_Pop(uint32_t)
DEC_Stack_GetSize(uint32_t)
DEC_Stack_GetTop(uint32_t)
DEC_Stack_Clear(uint32_t)

DEC_Stack_Init(sint32_t)
DEC_Stack_Push(sint32_t)
DEC_Stack_Pop(sint32_t)
DEC_Stack_GetSize(sint32_t)
DEC_Stack_GetTop(sint32_t)
DEC_Stack_Clear(sint32_t)

DEC_Stack_Init(f32_t)
DEC_Stack_Push(f32_t)
DEC_Stack_Pop(f32_t)
DEC_Stack_GetSize(f32_t)
DEC_Stack_GetTop(f32_t)
DEC_Stack_Clear(f32_t)

#endif /*_STACK_H_*/
