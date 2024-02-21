#ifndef SEVEN_H_
#define SEVEN_H_

#define TOTAL_PINS (7)


#define MAX_NUM (9)


#define ZERO (0x3F)
#define ONE (0x06)
#define TWO (0x5B)
#define THREE (0x4F)
#define FOUR (0x66)
#define FIVE (0x6D)
#define SIX (0x7D)
#define SEVEN (0x07)
#define EIGHT (0x7F)
#define NINE (0x6F)

/**
 * A structure to represent seven segment pin
 */
typedef struct
{
    /*@{*/
    port_t port; /**< the port number*/
    pin_t pin;   /**< the pin number*/
    /*@}*/
}sevenSegPin_t;

/**
 * A structure to represent seven segment
 */
typedef struct
{
/*@{*/
 sevenSegPin_t segment[TOTAL_PINS];/**< the array which contain sevenSegPin_tm*/
 /*@}*/
}sevenSegment_t;

/**
 * @brief This Function is used to initialize the seven segment
 * @param pSevenSeg pointer to the seven segment
 * which is a struct from type sevenSegment_t
 * @return error_t to handle error cases
 */
error_t SevenSegment_Init(sevenSegment_t* pSevenSeg);

/**
 * @brief This Function is used to set the seven segment to specific number
 * @param pSevenSeg pointer to the seven segment
 * which is a struct from type sevenSegment_t
 * @param number the number you want to set seven segment to
 * @return error_t handle error cases
 */
error_t SevenSegment_Set(sevenSegment_t * pSevenSeg, uint8_t number);


static void SetNumber(sevenSegment_t * pSevenSeg, uint8_t number);
#endif /* SEVEN_H_ */
