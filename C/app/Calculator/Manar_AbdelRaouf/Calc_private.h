#ifndef CALCULATOR_PRIVATE_H
#define CALCULATOR_PRIVATE_H

#define NOT (0)
typedef enum
{
    kFALSE,
    kTRUE
}bool_t;

typedef enum
{
    kNoERROR,
    kSYNTAX_ERROR,
    kMATH_ERROR
}calc_error_t;

#endif
