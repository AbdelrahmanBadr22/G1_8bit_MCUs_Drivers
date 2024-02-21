#ifndef PIR_H_
#define PIR_H
/**
 *  A structure to represent PIR
 */
typedef struct
{
    /*@{*/
    port_t port;/**< the port number */
    pin_t pin; /**< the pin number*/
    /*@}*/
}PIR_t;


/**
 * @brief this function is used to initialize PIR sensor
 * @param pPIR pointer to the PIRwhich is a struct from type PIR_t
 * @return error_t to handle error cases
 */
error_t PIR_Init(PIR_t* pPIR);

/**
 * @brief this function is used to know the state of  PIR sensor
 * @param pPIR pointer to the PIRwhich is a struct from type PIR_t
 * @param state could be klow or khigh
 * @return error_t error_t to handle error cases
 */
error_t PIR_GetVal(PIR_t* pPIR, state_t * state);
#endif
