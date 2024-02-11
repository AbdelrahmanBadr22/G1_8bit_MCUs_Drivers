/**
 * @file I2C_Private.h
 * @author Mohamed Refat
 * @brief
 * @version 0.1
 * @date 2023-12-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef MCAL_I2C_I2C_PRIVATE_H_
#define MCAL_I2C_I2C_PRIVATE_H_


/* BIT Macros */
#define TWCR_TWINT (7) /* TWI Interrupt Flag */
#define TWCR_TWEA  (6) /* TWI Enable Acknowledge Bit */
#define TWCR_TWSTA (5) /* TWI START Condition Bit */
#define TWCR_TWSTO (4) /* TWI STOP Condition Bit */
#define TWCR_TWEN  (2) /* TWI Enable Bit */
#define TWCR_TWIE  (0) /* TWI Interrupt Enable */

#define TWSR_TWPS1 (1) /* TWI Prescaler Bit 1 */
#define TWSR_TWPS0 (0) /* TWI Prescaler Bit 0 */

#define TWAR_TWGCE (0) /* TWI General Call Recognition Enable Bit */

#define TWDR_R_W   (0) /* TWI Read Write Bit */

#define I2C_PRESCALER_1  (1)
#define I2C_PRESCALER_4  (4)
#define I2C_PRESCALER_16 (16)
#define I2C_PRESCALER_64 (64)

/* I2C Status Macros   */

/* A START condition has been transmitted */
#define START_ACK                             (0x08)
/* A repeated START condition has been transmitted */
#define REPEATED_START_ACK                    (0x10)
/*A STOP condition or repeated START condition has been received*/
#define STOP_OR_REPEATED_STOP_RECEIVED_ACK    (0x98)
/* Master transmit SLA+W  and an ACK has been received */
#define SLAVE_ADDRESS_AND_WRITE_ACK           (0x18)
/* Master transmit SLA+R  and an ACK has been received */
#define SLAVE_ADDRESS_AND_READ_ACK            (0x40)
/* Data byte has been transmitted ACK has been received */
#define MASTER_WRITE_BYTE_ACK                 (0x28)
/* Data byte has been received ACK has been returned */
#define MASTER_READ_BYTE_ACK                  (0x50)
/* means that slave address is received with write request */
#define SLAVE_ADDRESS_RECEIVED_WITH_WRITE_REQ (0x60)
/* means that slave address is received with read request */
#define SLAVE_ADDRESS_RECEIVED_WITH_READ_REQ  (0xA8)
/* Data byte has been transmitted ACK has been received */
#define SLAVE_WRITE_BYTE_ACK                  (0xB8)
/* Data byte has been received ACK has been returned */
#define SLAVE_READ_BYTE_ACK                   (0x80)


#endif /* MCAL_I2C_I2C_PRIVATE_H_ */
