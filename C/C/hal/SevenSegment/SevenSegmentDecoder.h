#ifndef SEG_H_
#define SEG_H_


#define TOTAL_DECODER_PINS  (4)
#define MAX_NUM (9)

/**
 * A structure to represent seven segment decoder pin
 */
typedef struct
{
    /*@{*/
    port_t port;/**< the port number*/
    pin_t pin;/**< the pin number*/
    /*@}*/
}sevenSegPin_t;

/**
 * A structure to represent seven segment
 */
typedef struct
{
    /*@{*/
     sevenSegPin_t segment[TOTAL_DECODER_PINS];/**< array of sevenSegPin_t*/
    /*@{*/
}sevenSegDecoder_t;

/**
 * @brief This Function is used to initialize the seven segment
 * @param pSevenSeg pointer to the seven segment decoder
 * which is a struct from type sevenSegDecoder_t
 * @return error_t to handle error cases returns kNoError
 *                   if the Parameter is correct
 *                   and returns kFunctionParameterError
 *                   if the Parameter isn't correct
 */
error_t SevenSegmentDecoder_Init(sevenSegDecoder_t * pSevenSeg);

/**
 * @brief This Function is used to set the seven segment to specific number
 * @param pSevenSeg pointer to the seven segment decoder
 * which is a struct from type sevenSegDecoder_t
 * @param number the number you want to set seven segment to
 * @return error_t handle error cases returns kNoError
 *                 if the Parameter is correct
 *                 and returns kFunctionParameterError
 *                 if the Parameter isn't correct
 */
error_t SevenSegmentDecoder_Set( sevenSegDecoder_t * pSevenSeg, uint8_t number);

#endif /* SEG_H_ */
