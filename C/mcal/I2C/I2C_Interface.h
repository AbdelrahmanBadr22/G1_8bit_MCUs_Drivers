/**
* @file I2C_Interface.h
* @author Mohamed Refat
* @version 0.1
* @date 2023-12-07
*
*/

#ifndef MCAL_I2C_I2C_INTERFACE_H_
#define MCAL_I2C_I2C_INTERFACE_H_

/* BIT Macros */
#define TWCR_TWINT (7) /* TWI Interrupt Flag */
#define TWCR_TWEA (6) /* TWI Enable Acknowledge Bit */
#define TWCR_TWSTA (5) /* TWI START Condition Bit */
#define TWCR_TWSTO (4) /* TWI STOP Condition Bit */
#define TWCR_TWEN (2) /* TWI Enable Bit */
#define TWCR_TWIE (0) /* TWI Interrupt Enable */

#define TWSR_TWPS1 (1) /* TWI Prescaler Bit 1 */
#define TWSR_TWPS0 (0) /* TWI Prescaler Bit 0 */

#define TWAR_TWGCE (0) /* TWI General Call Recognition Enable Bit */

#define TWDR_R_W (0) /* TWI Read Write Bit */

#define I2C_PRESCALER_1 (1)
#define I2C_PRESCALER_4 (4)
#define I2C_PRESCALER_16 (16)
#define I2C_PRESCALER_64 (64)
/* I2C Status Macros */

/* A START condition has been transmitted */
#define START_ACK (0x08)
/* A repeated START condition has been transmitted */
#define REPEATED_START_ACK (0x10)
/*A STOP condition or repeated START condition has been received*/
#define STOP_OR_REPEATED_STOP_RECEIVED_ACK (0x98)
/* Master transmit SLA+W and an ACK has been received */
#define SLAVE_ADDRESS_AND_WRITE_ACK (0x18)
/* Master transmit SLA+R and an ACK has been received */
#define SLAVE_ADDRESS_AND_READ_ACK (0x40)
/* Data byte has been transmitted ACK has been received */
#define MASTER_WRITE_BYTE_ACK (0x28)
/* Data byte has been received ACK has been returned */
#define MASTER_READ_BYTE_ACK (0x50)
/* means that slave address is received with write request */
#define SLAVE_ADDRESS_RECEIVED_WITH_WRITE_REQ (0x60)
/* means that slave address is received with read request */
#define SLAVE_ADDRESS_RECEIVED_WITH_READ_REQ (0xA8)
/* Data byte has been transmitted ACK has been received */
#define SLAVE_WRITE_BYTE_ACK (0xB8)
/* Data byte has been received ACK has been returned */
#define SLAVE_READ_BYTE_ACK (0x80)

/**
* @brief I2C Error Types
*
*/
typedef enum
{
StartCondition_Error,
RepeatedStartError,
StopCondition_Error,
SlaveAddressWithReadError,
SlaveAddressWithWriteError,
MasterWriteByteError,
MasterReadByteError,
SlaveWriteByteError,
SlaveReadByteError,
I2C_NoError
}i2c_error_t;

/**
* @brief This function is Used to Initialize I2C in Master Mode
*
* @param iSCL_Clock I2C SLC Clock Rate [MAX: 400kHz --> Fast Mode Speed]
* @param iMasterAddress Address of the master 7 Bits [1 --> 120]
* Note that : Addresses 0 & [121-->127] are reserved
*
* @return None
*/
void I2C_MasterInit(uint32_t iSCL_Clock, uint8_t iMasterAddress);

/**
* @brief This function is Used to Initialize I2C in Slave Mode
*
* @param iSlaveAddress Address of the Slave 7 Bits [1 --> 120]
* Note that : Addresses 0 & [121-->127] are reserved
*
* @return None
*/
void I2C_SlaveInit(uint8_t iSlaveAddress);

/**
* @brief This function is used to send a start condition to the slave
*
* @return i2c_error_t: I2C_NoError
* StartCondition_Error
*/
i2c_error_t I2C_SendStartCondition(void);

/**
* @brief This function is used to send a repeated start condition to the slave
*
* @return i2c_error_t: I2C_NoError
* RepeatedStartError
*/
i2c_error_t I2C_SendRepeatedStartCondition(void);

/**
* @brief This function is used to send Slave Address with Read request
*
* @param iSlaveAddress Copy from target slave address
* @return i2c_error_t: I2C_NoError
* SlaveAddressWithReadError
*/
i2c_error_t I2C_SendSlaveAddressWithRead(uint8_t iSlaveAddress);

/**
* @brief This function is used to send Slave Address with Write request
*
* @param iSlaveAddress Copy from target slave address
* @return i2c_error_t: I2C_NoError
* SlaveAddressWithWriteError
*/
i2c_error_t I2C_SendSlaveAddressWithWrite(uint8_t iSlaveAddress);

/**
* @brief This function is used by the master to transmit[write] data
* to the slave
*
* @param iDataByte Copy From data [1 byte]
* @return i2c_error_t: I2C_NoError
* MasterWriteByteError
*/
i2c_error_t I2C_MasterWriteByte(uint8_t iDataByte);

/**
* @brief This function is used by the master to Receive[Read] data
* From the slave
*
* @param iDataByte Pointer to the data [1 byte]
* @return i2c_error_t: I2C_NoError
* MasterReadByteError
*/
i2c_error_t I2C_MasterReadByte(uint8_t *pDataByte);

/**
* @brief This function is used by the Slave to transmit[write] data
* to the Maser
*
* @param iDataByte Copy From data [1 byte]
* @return i2c_error_t: I2C_NoError
* SlaveWriteByteError
*/
i2c_error_t I2C_SlaveWriteByte(uint8_t iDataByte);

/**
* @brief This function is used by the Slave to Receive[Read] data
* From the Master
*
* @param iDataByte Pointer to the data [1 byte]
* @return i2c_error_t: I2C_NoError
* SlaveReadByteError
*/
i2c_error_t I2C_SlaveReadByte(uint8_t *pDataByte);

/**
* @brief This function is used to send a Stop condition to the slave
*
* @return i2c_error_t: I2C_NoError
* StartCondition_Error
*/
i2c_error_t I2C_SendStopCondition(void);

#endif /* MCAL_I2C_I2C_INTERFACE_H_ */
