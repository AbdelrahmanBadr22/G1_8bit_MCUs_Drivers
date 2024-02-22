/**
 * @file WDT.h
 * @author Mohamed Refat
 * @brief
 * @version 0.1
 * @date 2024-02-22
 *
 */
#ifndef MCAL_WDT_WDT_H_
#define MCAL_WDT_WDT_H_

/* Time Out available on WDT */
typedef enum
{
    /* 16.3 ms */
    WDT_16ms3,
    /* 32.5 ms */
    WDT_32ms5,
    /* 65 ms */
    WDT_65ms,
    /* 0.13 s */
    WDT_0s13,
    /* 0.26 s */
    WDT_0s26,
    /* 0.52 s */
    WDT_0s52,
    /* 1.0 s */
    WDT_1s0,
    /* 2.1 s */
    WDT_2s1

}WDT_TimeOut;

#define WDTCR_WDTOE		(4)
#define WDTCR_WDE 		(3)
#define WDTCR_WDP2 		(2)
#define WDTCR_WDP1 		(1)
#define WDTCR_WDP0		(0)

/**
 * @brief This function is used to enable WDT
 * @note  Call it at after setting the timeout
 *
 */
void WDT_Enable(void);

/**
 * @brief   This function is used to set the time out before the WDT
 *              reset the controller
 *
 * @param timeOut OPTIONS:
 *                      WDT_16ms3
 *                      WDT_32ms5
 *                      WDT_65ms
 *                      WDT_0s13
 *                      WDT_0s26
 *                      WDT_0s52
 *                      WDT_1s0
 *                      WDT_2s1
 *
 * @return error_t
 */

error_t WDT_SetTimeOut(WDT_TimeOut timeOut);

/**
 * @brief This function is used to disable the WDT
 *
 */
void WDT_Disable(void);

#endif /* MCAL_WDT_WDT_H_MCAL_WDT_WDT_H_ */
