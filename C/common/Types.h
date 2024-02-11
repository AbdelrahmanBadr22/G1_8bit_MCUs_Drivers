#ifndef Types_H_
#define Types_H_

typedef unsigned char uint8_t;                  //IGNORE-STYLE-CHECK[B004]
typedef signed   char sint8_t;                  //IGNORE-STYLE-CHECK[B004]
typedef float f32_t;                            //IGNORE-STYLE-CHECK[B004]
typedef unsigned short int  uint16;
typedef signed short int    sint16;

typedef unsigned long uint32_t;                  //IGNORE-STYLE-CHECK[B004]
typedef signed   long sint32_t;                  //IGNORE-STYLE-CHECK[B004]

#define NULL_PTR ((void*)0)

#ifndef NULL
#define NULL ((void*)0)
#endif

#define HIGH (1)
#define LOW  (0)

// typedef unsigned short uint16_t;
// typedef signed   short sint16_t;

typedef enum
{
	kNoError,
    kFunctionParameterError,
    kTimeoutError
}error_t;

typedef enum
{
	kFALSE,
    kTRUE
}bool_t;


#endif //_types_H_
