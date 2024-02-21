#ifndef HAL_LCD_INTERFACE_H_
#define HAL_LCD_INTERFACE_H_

#define LCD_8Bit        (8)
#define LCD_4Bit        (4)

#define LCD_HIGH_NIBBLE (0xF)
#define LCD_LOW_NIBBLE  (0x0)


#define LCD_ROW_1  (1)
#define LCD_ROW_2  (2)

#define LCD_COL_1  (1)
#define LCD_COL_2  (2)
#define LCD_COL_3  (3)
#define LCD_COL_4  (4)
#define LCD_COL_5  (5)
#define LCD_COL_6  (6)
#define LCD_COL_7  (7)
#define LCD_COL_8  (8)
#define LCD_COL_9  (9)
#define LCD_COL_10 (10)
#define LCD_COL_11 (11)
#define LCD_COL_12 (12)
#define LCD_COL_13 (13)
#define LCD_COL_14 (14)
#define LCD_COL_15 (15)
#define LCD_COL_16 (16)

/**
 * @brief                  : This Data Type To Configure LCD[Port ,Pins ,Mode]
 * @param  kLcdMode        : [LCD_8Bit , LCD_4Bit]
 * @param  kLcdDataPort    : [kPORTA --> kPORTD]
 * @param  kLcdControlPort : [kPORTA --> kPORTD]
 * @param  kRS_PinNum      : [kPIN0  --> kPIN7]
 * @param  kRW_PinNum      : [kPIN0  --> kPIN7]
 * @param  kEN_PinNum      : [kPIN0  --> kPIN7]
 * @param kLcd_4bitDataPin : [LCD_HIGH_NIBBLE , LCD_LOW_NIBBLE]
 */
typedef struct {

    uint8_t kLcdMode;
    port_t  kLcdDataPort;
    port_t  kLcdControlPort;
    pin_t   kRS_PinNum;             //IGNORE-STYLE-CHECK[B004]
    pin_t   kRW_PinNum;             //IGNORE-STYLE-CHECK[B004]
    pin_t   kEN_PinNum;             //IGNORE-STYLE-CHECK[B004]
    uint8_t kLcd_4bitDataPin;       //IGNORE-STYLE-CHECK[B004]

               }lcd_t;

error_t LCD_Init(lcd_t *pLcdConfig);
error_t LCD_ClearScreen(lcd_t *pLcdConfig);
error_t LCD_SendChar(lcd_t *pLcdConfig, char character);
error_t LCD_SendString(lcd_t *pLcdConfig, char str[]);
error_t LCD_StoreCustomChar(lcd_t *pLcdConfig, char pChar_Arr[],
                                                    uint8_t location);

error_t LCD_SendCustomChar(lcd_t *pLcdConfig, uint8_t location,
                                        uint8_t kRowNum, uint8_t kColumnNum);
/**
 * @brief             :this function used to set cursor position
 *                      to display your data in s specific position
 *
 * @param kRowNum     :kRowNum    --> [LCD_ROW_1 , LCD_ROW_2]
 * @param kColumnNum  :kColumnNum --> [LCD_COL_1 , LCD_COL_2 ... LCD_COL_16]
 */
error_t LCD_SetPosition(lcd_t *pLcdConfig, uint8_t kRowNum, uint8_t kColumnNum);

error_t LCD_SendNumber(lcd_t *pLcdConfig, sint16 number);
error_t LCD_SendFloat(lcd_t *pLcdConfig, f32_t number);

error_t LCD_EnableCursor(lcd_t *pLcdConfig);
error_t LCD_DisableCursor(lcd_t *pLcdConfig);

error_t LCD_ShiftRight(lcd_t *pLcdConfig);
error_t LCD_ShiftLeft(lcd_t *pLcdConfig);

error_t LCD_Display_On(lcd_t *pLcdConfig);
error_t LCD_Display_Off(lcd_t *pLcdConfig);

error_t LCD_Blink_On(lcd_t *pLcdConfig);
error_t LCD_Blink_Off(lcd_t *pLcdConfig);


#endif /* HAL_LCD_INTERFACE_H_ */
