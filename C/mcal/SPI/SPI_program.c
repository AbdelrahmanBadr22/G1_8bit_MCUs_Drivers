#include "Config.h"
#include "Types.h"
#include "Utils.h"
#include "Registes.h"
#include "SPI_config.h"
#include "SPI_interface.h"

//-----------------------------------------------------------------------------
///////////////// HELPER FUNCTIONS ////////////////////////////////////////////
//-----------------------------------------------------------------------------
#if IS_PIC()
static void PIC_CLK_MODE()
{
//Set SCK Rate To Fosc/4
#if SPI_CLK_MODE == CLK_4
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP0);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP1);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP2);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP3);
#elif SPI_CLK_MODE == CLK_16
SET_BIT(SSPCON1_REG, SSPCON1_SSMP0);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP1);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP2);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP3);
#elif SPI_CLK_MODE == CLK_64
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP0);
SET_BIT(SSPCON1_REG, SSPCON1_SSMP1);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP2);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP3);
#elif SPI_CLK_MODE == TMR2_OUTPUT_2
SET_BIT(SSPCON1_REG, SSPCON1_SSMP0);
SET_BIT(SSPCON1_REG, SSPCON1_SSMP1);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP2);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP3);
#endif
}
static void PIC_Config_Helper()
{
#if IS_PIC()
//Synchronous Serial Port Enable bit
SET_BIT(SSPCON1_REG, SSPCON1_SSPEN);
//SPI BUS MODES
#if SPI_MODE == MODE_1
CLR_BIT(SSPCON1_REG, SSPCON1_CKP);
SET_BIT(SSPSTAT_REG, SSPSTAT_CKE);
#elif SPI_MODE == MODE_2
CLR_BIT(SSPCON1_REG, SSPCON1_CKP);
CLR_BIT(SSPSTAT_REG, SSPSTAT_CKE);
#elif SPI_MODE == MODE_3
SET_BIT(SSPCON1_REG, SSPCON1_CKP);
SET_BIT(SSPSTAT_REG, SSPSTAT_CKE);
#elif SPI_MODE == MODE_4
SET_BIT(SSPCON1_REG, SSPCON1_CKP);
CLR_BIT(SSPSTAT_REG, SSPSTAT_CKE);
#else
#error "wrong SPI BUS MODE Config"
#endif
//Sample mode
#if SPI_SAMPLE_MODE == END
SET_BIT(SSPSTAT_REG, SSPSTAT_SMP);
#elif SPI_SAMPLE_MODE == MIDDLE
CLR_BIT(SSPSTAT_REG, SSPSTAT_SMP);
#else
#error "wrong SPI Sample mode Config"
#endif
#endif
}

static void PIC_SPI_MASTER_Init()
{
#if IS_PIC()
//set SPI CLK MODE
PIC_CLK_MODE();
//set configuration
PIC_Config_Helper();
//Configure The I/O Pins For SPI Master Mode
CLR_BIT(TRISC_REG, TRISC_TRISC3); //SCK
SET_BIT(TRISC_REG, TRISC_TRISC4); //SDI
CLR_BIT(TRISC_REG, TRISC_TRISC5); //SDO
#endif // MCU_TYPE
}

static void PIC_SPI_SLAVE_Init()
{
#if IS_PIC()
//SS pin control
#if SPI_SS_MODE == ENABLE
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP0);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP1);
SET_BIT(SSPCON1_REG, SSPCON1_SSMP2);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP3);
#elif SPI_SS_MODE == DISABLE
SET_BIT(SSPCON1_REG, SSPCON1_SSMP0);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP1);
SET_BIT(SSPCON1_REG, SSPCON1_SSMP2);
CLR_BIT(SSPCON1_REG, SSPCON1_SSMP3);
#endif
//set configuration
PIC_Config_Helper();
//Configure The I/O Pins For SPI SLAVE Mode
SET_BIT(TRISC_REG, TRISC_TRISC3);//SCK
SET_BIT(TRISC_REG, TRISC_TRISC4);//SDI
CLR_BIT(TRISC_REG, TRISC_TRISC5);//SDO
//SS -> INPUT
SET_BIT(TRISA_REG, TRISA_TRISA5);
#endif
}
#endif

#if IS_AVR()
static void AVR_Config_Helper()
{
#if IS_AVR()
//DATA ORDER
#if SPI_DATA_ORDER == MSB_FIRST
CLR_BIT(SPCR, SPCR_DORD);
#elif SPI_DATA_ORDER == LSB_FIRST
SET_BIT(SPCR, SPCR_DORD);
#else
#error "wrong SPI_DATA_ORDER_config"
#endif
//CLOCK POLARITY
#if SPI_CLK_POLARITY== IDLE_LOW
CLR_BIT(SPCR, SPCR_CPOL);
#elif SPI_CLK_POLARITY == IDLE_HIGH
SET_BIT(SPCR, SPCR_CPOL);
#else
#error "wrong SPI_CLOCK_Polarity_config"
#endif
//CLOCK PHASE
#if SPI_CLK_PHASE== SAMPLE_FIRST
CLR_BIT(SPCR, SPCR_CPHA);
#elif SPI_CLK_PHASE == SETUP_FIRST
SET_BIT(SPCR, SPCR_CPHA);
#else
#error "wrong SPI_CLOCK_PHASE config"
#endif
//SPI ENABLE
SET_BIT(SPCR, SPCR_SPE);
//INTERRUBT
#if SPI_INTERRUPT== INTERRUPT_ENABLE
SET_BIT(SPCR, SPCR_SPIE);
#elif SPI_INTERRUPT== INTERRUPT_DISABLE
CLR_BIT(SPCR, SPCR_SPIE);
#else
#error "wrong SPI_INTERRUBT_config"
#endif
#endif
}

static void AVR_SPI_MASTER_Init()
{
#if IS_AVR()
//initialize it as master
SET_BIT(SPCR, SPCR_MSTR);
//set configuration
AVR_Config_Helper();
//CLK FOR MASTER 128
SET_BIT(SPCR, SPCR_SPR0);
SET_BIT(SPCR, SPCR_SPR1);
CLR_BIT(SPSR, SPSR_SPI2X);
#endif // MCU_TYPE
}

static void AVR_SPI_SLAVE_Init()
{
#if IS_AVR()
//initialize it as slave
CLR_BIT(SPCR, SPCR_MSTR);
//set configuration
AVR_Config_Helper();
#endif // MCU_TYPE
}
#endif

//-----------------------------------------------------------------------------
///////////////// SPI FUNCTIONS ///////////////////////////////////////////////
//-----------------------------------------------------------------------------

void SPI_MASTER_Init()
{
#if IS_AVR()
AVR_SPI_MASTER_Init();
#elif IS_PIC()
PIC_SPI_MASTER_Init();
#else
#error "Unkown MCU"
#endif
}

void SPI_SLAVE_Init()
{
#if IS_AVR()
AVR_SPI_SLAVE_Init();
#elif IS_PIC()
PIC_SPI_SLAVE_Init();
#else
#error "Unkown MCU"
#endif
}
error_t SPI_Write(uint8_t data)
{
error_t kErrorState = kNoError;
uint8_t counter = 0;

#if IS_AVR()
#define SPI_WRITE_REG (SPDR)
#define SPI_GET_TRANSFER_STATUS() (GET_BIT(SPSR, SPSR_SPIF))
#elif IS_PIC()
#define SPI_WRITE_REG (SSPBUF_REG)
#define SPI_GET_TRANSFER_STATUS() (GET_BIT(SSPSTAT_REG, SSPSTAT_BF))
#else
#error "Unkown MCU"
#endif

SPI_WRITE_REG = data;

while ((SPI_GET_TRANSFER_STATUS() == 0) && (counter < SPI_TIMEOUT))
{
counter++;
}

if (counter == SPI_TIMEOUT)
{
kErrorState = kTimeoutError;
}

return kErrorState;
}

error_t SPI_Read(uint8_t* data)
{
error_t kErrorState = kNoError;
uint16 counter = 0;

#if IS_AVR()
#define SPI_WRITE_REG (SPDR)
#define SPI_GET_READ_STATUS_FINISHED() (GET_BIT(SPSR, SPSR_SPIF) == 0)
#elif IS_PIC()
#define SPI_WRITE_REG (SSPBUF_REG)
#define SPI_GET_READ_STATUS_FINISHED() (GET_BIT(SSPSTAT_REG, SSPSTAT_BF) == 1) && (GET_BIT(PIR1_REG, PIR1_SSPIF) == 1) //IGNORE-STYLE-CHECK[L004]
#else
#error "Unkown MCU"
#endif

while (SPI_GET_READ_STATUS_FINISHED() && counter < SPI_TIMEOUT)
{
counter++;
}
if (counter == SPI_TIMEOUT)
{
kErrorState = kTimeoutError;
}
else
{
*data = SPI_WRITE_REG;
}
#if IS_PIC() // EXTRA STUFF SHOULD BE HANDLED FOR PIC
CLR_BIT(SSPSTAT_REG, SSPSTAT_BF);
CLR_BIT(PIR1_REG, PIR1_SSPIF);
#endif
return kErrorState;
}
