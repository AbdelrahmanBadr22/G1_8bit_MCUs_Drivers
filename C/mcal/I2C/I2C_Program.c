/**
 * @file I2C_Program.c
 * @author Mohamed Refat
 * @brief
 * @version 0.1
 * @date 2023-12-07
 */

#include "Config.h"
#include "Types.h"
#include "Registes.h"
#include "Utils.h"
#include "I2C_Config.h"
#include "I2C_Interface.h"

//-----------------------------------------------------------------------------
//                           HELPER FUNCTIONS
//-----------------------------------------------------------------------------
#if IS_AVR()
static void AVR_SET_PRESCALER()
{
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
}
#elif IS_PIC()
static i2c_error_t PIC_SetMode(uint8_t mode)
{
    i2c_error_t kErrorState = I2C_NoError;
    switch (mode)
    {
        case MASTER_MODE: SSPCON1_REG &= (0b11111000);  break;
        case FIRMWARE_MODE: SSPCON1_REG &= (0b11111011); break;
        case SLAVE_7BITS_MODE: SSPCON1_REG &= (0b11110110); break;
        case SLAVE_10BITS_MODE: SSPCON1_REG &= (0b11110111); break;
        default: kErrorState = ModeError;
    }
    return kErrorState;
}
static void PIC_SLEW_RATE()
{
    #if SLEW_RATE == STANDARD_SPEED_100K_1M
    SET_BIT(SSPSTAT_REG, SSPSTAT_SMP);
    #elif SLEW_RATE == HIGH_SPEED_400K
    CLR_BIT(SSPSTAT_REG, SSPSTAT_SMP);
    #endif
}
static void PIC_SMBus()
{
    #if SMBus == ENABLED
    SET_BIT(SSPSTAT_REG, SSPSTAT_CKE);
    #elif SMBus == DISABLED
    CLR_BIT(SSPSTAT_REG, SSPSTAT_CKE);
    #endif
}
#endif //IS_AVR()
//-----------------------------------------------------------------------------
//                           I2C FUNCTIONS
//-----------------------------------------------------------------------------
void I2C_MasterInit(uint32_t iSCL_Clock, uint8_t iMasterCfg)
{
    #if IS_AVR()
    AVR_SET_PRESCALER();
    /* Set I2C SCL clock rate */
    TWBR = (uint8_t) ((CPU_FREQ/iSCL_Clock)-16)/(2*I2C_PRESCALER);
    /* Set Master Address */
    TWAR = iMasterCfg<<1;
    /* Enable Acknowledge */
    SET_BIT(TWCR, TWCR_TWEA);
    /* Enable TWI module */
    SET_BIT(TWCR, TWCR_TWEN);

    #elif IS_PIC()
    /* Set I2C BAUD Rate */
    SSPADD_REG = (uint8_t)(((_XTAL_FREQ / 4.0) /iSCL_Clock) - 1);
    /* Set Mode */
    PIC_SetMode(iMasterCfg);
    /*Set Selw Rate */
    PIC_SLEW_RATE();
    /*Set SMBus*/
    PIC_SMBus();
    /* Enable I2C module */
    SET_BIT(SSPCON1_REG, SSPCON1_SSPEN);
    #endif // MCU_TYPE
}

void I2C_SlaveInit(uint8_t iSlaveAddress, uint8_t iSlaveMode)
{
    #if IS_AVR()
    /* Set Slave Address */
    TWAR = iSlaveAddress<<1;
    CLR_BIT(TWAR, 0);
    /* Enable Acknowledge */
    SET_BIT(TWCR, TWCR_TWEA);
    /* Enable TWI module */
    SET_BIT(TWCR, TWCR_TWEN);

    #elif IS_PIC()
    /* Set Slave Address */
    SSPADD_REG = iSlaveAddress<<1;
    /* Set Mode */
    PIC_SetMode(iSlaveMode);
    /*Set Selw Rate */
    PIC_SLEW_RATE();
    /*Set SMBus*/
    PIC_SMBus();
    /* Clear the Write Collision Detect */
    CLR_BIT(SSPCON1_REG, SSPCON1_WCOL); /* No Collision */
    /* Clear the Receive Overflow Indicator */
    CLR_BIT(SSPCON1_REG, SSPCON1_SSPOV); /* No Overflow */
    /* Release the clock */
    SET_BIT(SSPCON1_REG, SSPCON1_CKP);
    /* Enable I2C module */
    SET_BIT(SSPCON1_REG, SSPCON1_SSPEN);
    #endif //MCU_TYPE
}

i2c_error_t I2C_SendStartCondition(void)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if IS_AVR()
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

    #elif IS_PIC()
    /* Send Start Condition */
    SET_BIT(SSPCON2_REG, SSPCON2_SEN);
    /* Wait for the completion of the Start condition */
    while ( (GET_BIT(SSPCON2_REG, SSPCON2_SEN)) == HIGH){};
    /* Clear The MSSP Interrupt Flag bit -> SSPIF */
    CLR_BIT(PIR1_REG, PIR1_SSPIF);
    if (GET_BIT(SSPSTAT_REG, SSPSTAT_S) != HIGH)
    {
        kErrorState = StartCondition_Error;
    }
    #endif //MCU_TYPE
    return kErrorState;
}

i2c_error_t I2C_SendRepeatedStartCondition(void)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if IS_AVR()
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
    #elif IS_PIC()
    /* Send Repeated Start Condition */
    SET_BIT(SSPCON2_REG, SSPCON2_RSEN);
    /* Wait for the completion of the Repeat Start condition */
    while ( (GET_BIT(SSPCON2_REG, SSPCON2_RSEN)) == HIGH){};
    /* Clear The MSSP Interrupt Flag bit -> SSPIF */
    CLR_BIT(PIR1_REG, PIR1_SSPIF);
    #endif //MCU_TYPE
    return kErrorState;
}

i2c_error_t I2C_SendSlaveAddressWithRead(uint8_t iSlaveAddress)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if IS_AVR()
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
    #endif //IS_AVR()
    return kErrorState;
}

i2c_error_t I2C_SendSlaveAddressWithWrite(uint8_t iSlaveAddress)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if IS_AVR()
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
    #endif //IS_AVR()
    return kErrorState;
}

i2c_error_t I2C_MasterWriteByte(uint8_t iDataByte)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if IS_AVR()
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
    #elif IS_PIC()
    /* Write Data to the Data register */
    SSPBUF_REG = iDataByte;

    /* Wait The transmission to be completed */
    while ( (GET_BIT(SSPSTAT_REG, SSPSTAT_BF)) == HIGH){};

    /* Clear The MSSP Interrupt Flag bit -> SSPIF */
    CLR_BIT(PIR1_REG, PIR1_SSPIF);
    /*Check the acknowledge received from the slave */
    if ( (GET_BIT(SSPCON2_REG, SSPCON2_ACKSTAT)) != LOW)
    {
        kErrorState = MasterWriteByteError;
    }else
    {
        /* Do Nothing */
    }
    #endif //MCU_TYPE
    return kErrorState;
}

i2c_error_t I2C_MasterReadByte(uint8_t *pDataByte)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if IS_AVR()
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
    #elif IS_PIC()
    /* Master Mode Receive Enable */
    SET_BIT(SSPCON2_REG, SSPCON2_RCEN);
    /* Wait for buffer full flag : A complete byte received */
    while ((GET_BIT(SSPSTAT_REG, SSPSTAT_BF)) == LOW){};
    /* Copy The data registers to buffer variable */
    *pDataByte = SSPBUF_REG;
    /* Acknowledge */
    CLR_BIT(SSPCON2_REG, SSPCON2_ACKDT);
    /*Set Acknowledge sequence on SDA and SCL and transmit ACKDT data bit*/
    SET_BIT(SSPCON2_REG, SSPCON2_ACKEN);
    /* Automatically cleared by hardware */
    while ( (GET_BIT(SSPCON2_REG, SSPCON2_ACKEN))== HIGH){};
    #endif //MCU_TYPE
    return kErrorState;
}

i2c_error_t I2C_SlaveWriteByte(uint8_t iDataByte)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if IS_AVR()
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
    #endif //IS_AVR()
    return kErrorState;
}

i2c_error_t I2C_SlaveReadByte(uint8_t *pDataByte)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if IS_AVR()
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

    #endif //IS_AVR()

    return kErrorState;
}

i2c_error_t I2C_SendStopCondition(void)
{
    i2c_error_t kErrorState = I2C_NoError;

    #if IS_AVR()

    /* Send Stop Condition */
    SET_BIT(TWCR, TWCR_TWSTO);

    /* Clear TWI Interrupt Flag*/
    SET_BIT(TWCR, TWCR_TWINT);

    #elif IS_PIC()
    /* Initiates Stop condition on SDA and SCL pins */
    SET_BIT(SSPCON2_REG, SSPCON2_PEN);

    /* Wait for the completion of the Stop condition */
    while ( (GET_BIT(SSPCON2_REG, SSPCON2_PEN)) == HIGH){};

    /* Clear The MSSP Interrupt Flag bit -> SSPIF */
    CLR_BIT(PIR1_REG, PIR1_SSPIF);

    /* Check The Stop Condition Detection */
    if (GET_BIT(SSPSTAT_REG, SSPSTAT_P) != HIGH)
    {
        kErrorState = StopCondition_Error;
    }
    #endif //IS_AVR()

    return kErrorState;
}
