/**
 * @file I2C_Program.c
 * @author Mohamed Refat
 * @brief
 * @version 0.1
 * @date 2023-12-07
 */

#include "../../common/Config.h"
#include "../../common/Types.h"
#include "../../common/Registes.h"
#include "../../common/Utils.h"
#include "I2C_Interface.h"
#include "I2C_Private.h"
#include "I2C_Config.h"

void I2C_MasterInit(uint32_t iSCL_Clock, uint8_t iMasterAddress)
{
    #if MCU_TYPE == _AVR
    /* Set Prescaler */
    #if I2C_PRESCALER == I2C_PRESCALER_1
        CLR_BIT(TWSR, TWSR_TWPS0);
        CLR_BIT(TWSR, TWSR_TWPS1);
    #elif I2C_PRESCALER == I2C_PRESCALER_4
        SET_BIT(TWSR, TWSR_TWPS0);
        CLR_BIT(TWSR, TWSR_TWPS1);
    #elif I2C_PRESCALER == I2C_PRESCALER_16
        CLR_BIT(TWSR, TWSR_TWPS0);
        SET_BIT(TWSR, TWSR_TWPS1);
    #elif I2C_PRESCALER == I2C_PRESCALER_64
        SET_BIT(TWSR, TWSR_TWPS0);
        SET_BIT(TWSR, TWSR_TWPS1);
    #endif

    /* Set I2C SCL clock rate */
    TWBR = (uint8_t) ((F_CPU/iSCL_Clock)-16)/(2*I2C_PRESCALER);

    /* Set Master Address */
    TWAR = iMasterAddress<<1;

    /* Enable Acknowledge */
    SET_BIT(TWCR, TWCR_TWEA);

    /* Enable TWI module */
    SET_BIT(TWCR, TWCR_TWEN);
    #endif
}

void I2C_SlaveInit(uint8_t iSlaveAddress)
{
    #if MCU_TYPE == _AVR
    /* Set Master Address */
    TWAR = iSlaveAddress<<1;
    CLR_BIT(TWAR, 0);

    /* Enable Acknowledge */
    SET_BIT(TWCR, TWCR_TWEA);

    /* Enable TWI module */
    SET_BIT(TWCR, TWCR_TWEN);
    #endif
}

i2c_error_t I2C_SendStartCondition(void)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if MCU_TYPE == _AVR
    /* Send Start Condition */
    SET_BIT(TWCR, TWCR_TWSTA);

    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);

    /* Wait until the START condition has been transmitted */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};

    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != START_ACK )
    {
        kErrorState = StartCondition_Error;
    }else
    {
        /* Do Nothing */
    }
    #endif
    return kErrorState;
}

i2c_error_t I2C_SendRepeatedStartCondition(void)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if MCU_TYPE == _AVR
    /* Send Repeated Start Condition */
    SET_BIT(TWCR, TWCR_TWSTA);

    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);

    /* Wait until the START condition has been transmitted */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};

    /* Clear Repeated START condition bit */
    CLR_BIT(TWCR, TWCR_TWSTA);

    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != REPEATED_START_ACK )
    {
        kErrorState = RepeatedStartError;
    }else
    {
        /* Do Nothing */
    }
    #endif
    return kErrorState;
}

i2c_error_t I2C_SendSlaveAddressWithRead(uint8_t iSlaveAddress)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if MCU_TYPE == _AVR
    /* Send  Slave address*/
    TWDR = iSlaveAddress<<1;

    /* Send Read Request */
    SET_BIT(TWDR, TWDR_R_W);

    /* Clear START condition bit --> why here not in start condition fun??*/
    CLR_BIT(TWCR, TWCR_TWSTA);

    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);

    /* Wait until the SLA+R has been transmitted */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};

    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != SLAVE_ADDRESS_AND_READ_ACK )
    {
        kErrorState = SlaveAddressWithReadError;
    }else
    {
        /* Do Nothing */
    }
    #endif
    return kErrorState;
}

i2c_error_t I2C_SendSlaveAddressWithWrite(uint8_t iSlaveAddress)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if MCU_TYPE == _AVR
    /* Send  Slave address*/
    TWDR = iSlaveAddress<<1;

    /* Clear START condition bit --> why here not in start condition fun??*/
    CLR_BIT(TWCR, TWCR_TWSTA);
    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);

    /* Wait until the SLA+W has been transmitted */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};

    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != SLAVE_ADDRESS_AND_WRITE_ACK )
    {
        kErrorState = SlaveAddressWithWriteError;
    }else
    {
        /* Do Nothing */
    }
    #endif
    return kErrorState;
}

i2c_error_t I2C_MasterWriteByte(uint8_t iDataByte)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if MCU_TYPE == _AVR
    /* Write Data byte in the buffer*/
    TWDR = iDataByte;

    /* Clear TWI Interrupt Flag */
    SET_BIT(TWCR, TWCR_TWINT);


    /* Wait until the Data has been transmitted */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};

    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != MASTER_WRITE_BYTE_ACK )
    {
        kErrorState = MasterWriteByteError;
    }else
    {
        /* Do Nothing */
    }
    #endif
    return kErrorState;
}

i2c_error_t I2C_MasterReadByte(uint8_t *pDataByte)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if MCU_TYPE == _AVR
    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);

    /* Wait until the Data has been Received */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};

    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != MASTER_READ_BYTE_ACK )
    {
        kErrorState = MasterReadByteError;
    }else
    {
        /* Read Data byte */
        *pDataByte = TWDR;
    }
    #endif
    return kErrorState;
}

i2c_error_t I2C_SlaveWriteByte(uint8_t iDataByte)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if MCU_TYPE == _AVR
    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);
    /* Wait until the SLA+W has been transmitted from master */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};
    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != SLAVE_ADDRESS_RECEIVED_WITH_READ_REQ )
    {
        kErrorState = SlaveAddressWithReadError;
    }else
    {
    		/* Send Data */
    	    TWDR = iDataByte;
    }


    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);

    /* Wait until the Data has been Transmitted */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};

    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != SLAVE_WRITE_BYTE_ACK )
    {
        kErrorState = SlaveWriteByteError;
    }else
    {
        /* Do Nothing */
    }
    #endif
    return kErrorState;
}

i2c_error_t I2C_SlaveReadByte(uint8_t *pDataByte)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if MCU_TYPE == _AVR
    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);
    /* Wait until the SLA+W has been transmitted from master */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};
    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != SLAVE_ADDRESS_RECEIVED_WITH_WRITE_REQ )
    {
        kErrorState = SlaveAddressWithWriteError;
    }else
    {
        /* Do Nothing */
    }

    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);

    /* Wait until the Data has been Received */
    while ( (GET_BIT(TWCR, TWCR_TWINT)) == LOW ){};

    /* Check The status of TWSR */
    if ( ( TWSR & 0xF8 ) != SLAVE_READ_BYTE_ACK )
    {
        kErrorState = SlaveReadByteError;
    }else
    {
        *pDataByte = TWDR;
    }

    #endif

    return kErrorState;
}

i2c_error_t I2C_SendStopCondition(void)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if MCU_TYPE == _AVR

    /* Send Stop Condition */
    SET_BIT(TWCR, TWCR_TWSTO);

    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);

    #endif

    return kErrorState;
}
