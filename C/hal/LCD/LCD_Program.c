#include "Config.h"
#if MCU_TYPE == _AVR
#include <util/delay.h>
#endif

#include "../../common/Types.h"
#include "../../mcal/GPIO/GPIO.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"


error_t LCD_Init(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		/* SET Direction for LCD control  pins --> OUTPUT */
		GPIO_SetPinDirection(pLcdConfig->kLcdControlPort,
										pLcdConfig->kRS_PinNum, kOutput);

		GPIO_SetPinDirection(pLcdConfig->kLcdControlPort,
										pLcdConfig->kRW_PinNum, kOutput);

		GPIO_SetPinDirection(pLcdConfig->kLcdControlPort,
										pLcdConfig->kEN_PinNum, kOutput);

		if (pLcdConfig->kLcdMode == LCD_8Bit)
		{
			/* SET Direction for LCD data  pins --> OUTPUT */
			GPIO_SetPortDirection(pLcdConfig->kLcdDataPort, kOutput_PORT);

			Delay_ms(50);
			/* Function Set */
			LCD_SendCommand(pLcdConfig, LCD_FUNCTION_SET_8_BIT);
			Delay_ms(1);
			/*   Display ON/OFF Control */
			LCD_SendCommand(pLcdConfig, LCD_DISPLAY_ON_CURSOR_OFF);
			Delay_ms(1);
			/*  Clear Screen */
			LCD_SendCommand(pLcdConfig, LCD_CLEAR_SCREEN);
			Delay_ms(5);
			/* Entry mode set */
			LCD_SendCommand(pLcdConfig, LCD_ENTRY_MODE_INC_SHIFT_OFF);
			Delay_ms(1);
		}
		else if (pLcdConfig->kLcdMode == LCD_4Bit)
		{
			/* SET Direction for LCD data  pins --> OUTPUT */
			if (pLcdConfig->kLcd_4bitDataPin == LCD_HIGH_NIBBLE )
			{
				GPIO_SetHighNibbleDirection(pLcdConfig->kLcdDataPort, kOutput_PORT);
			}
			else if (pLcdConfig->kLcd_4bitDataPin == LCD_LOW_NIBBLE )
			{
				GPIO_SetLowNibbleDirection(pLcdConfig->kLcdDataPort, kOutput_PORT);

			}
			LCD_SendCommand(pLcdConfig, LCD_RETURN_HOME);
			Delay_ms(50);
			/* Function Set */
			LCD_SendCommand(pLcdConfig, LCD_FUNCTION_SET_4_BIT);
			Delay_ms(1);
			/*   Display ON/OFF Control */
			LCD_SendCommand(pLcdConfig, LCD_DISPLAY_ON_CURSOR_OFF);
			Delay_ms(1);
			/*  Clear Screen */
			LCD_SendCommand(pLcdConfig, LCD_CLEAR_SCREEN);
			Delay_ms(5);
			/* Entry mode set */
			LCD_SendCommand(pLcdConfig, LCD_ENTRY_MODE_INC_SHIFT_OFF);
			Delay_ms(5);
		}

	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;

}


static error_t LCD_SendData(lcd_t *pLcdConfig, uint8_t data)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		/* Set RS to 1 and RW to 0  */
		GPIO_SetPinValue(pLcdConfig->kLcdControlPort, pLcdConfig->kRS_PinNum, kHigh );
		GPIO_SetPinValue(pLcdConfig->kLcdControlPort, pLcdConfig->kRW_PinNum, kLow  );

		if (pLcdConfig->kLcdMode == LCD_8Bit)
		{
			/* Send data to the LCD Port */
			GPIO_SetPortValue(pLcdConfig->kLcdDataPort, data);
			LCD_SendFallingEndgPulse(pLcdConfig);
		}
		else if (pLcdConfig->kLcdMode == LCD_4Bit)
		{
			if (pLcdConfig->kLcd_4bitDataPin == LCD_HIGH_NIBBLE )
			{
				GPIO_SetHighNibbleValue(pLcdConfig->kLcdDataPort, data);
				LCD_SendFallingEndgPulse(pLcdConfig);
				GPIO_SetHighNibbleValue(pLcdConfig->kLcdDataPort, (data<<4) );
				LCD_SendFallingEndgPulse(pLcdConfig);
			}
			else if (pLcdConfig->kLcd_4bitDataPin == LCD_LOW_NIBBLE )
			{
				GPIO_SetLowNibbleValue(pLcdConfig->kLcdDataPort, (data>>4) );
				LCD_SendFallingEndgPulse(pLcdConfig);
				GPIO_SetLowNibbleValue(pLcdConfig->kLcdDataPort, data);
				LCD_SendFallingEndgPulse(pLcdConfig);
			}
		}

	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}
static error_t LCD_SendCommand(lcd_t *pLcdConfig, uint8_t command)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		/* Set RS to 0 and RW to 0  */
		GPIO_SetPinValue(pLcdConfig->kLcdControlPort, pLcdConfig->kRS_PinNum, kLow );
		GPIO_SetPinValue(pLcdConfig->kLcdControlPort, pLcdConfig->kRW_PinNum, kLow );

		if (pLcdConfig->kLcdMode == LCD_8Bit)
		{
			/* Send command to the LCD Port */
			GPIO_SetPortValue(pLcdConfig->kLcdDataPort, command);
			LCD_SendFallingEndgPulse(pLcdConfig);
		}
		else if (pLcdConfig->kLcdMode == LCD_4Bit)
		{
			if (pLcdConfig->kLcd_4bitDataPin == LCD_HIGH_NIBBLE )
			{
				GPIO_SetHighNibbleValue(pLcdConfig->kLcdDataPort, command);
				LCD_SendFallingEndgPulse(pLcdConfig);
				GPIO_SetHighNibbleValue(pLcdConfig->kLcdDataPort, (command<<4));
				LCD_SendFallingEndgPulse(pLcdConfig);
			}
			else if (pLcdConfig->kLcd_4bitDataPin == LCD_LOW_NIBBLE )
			{
				GPIO_SetLowNibbleValue(pLcdConfig->kLcdDataPort, (command>>4) );
				LCD_SendFallingEndgPulse(pLcdConfig);
				GPIO_SetLowNibbleValue(pLcdConfig->kLcdDataPort, command);
				LCD_SendFallingEndgPulse(pLcdConfig);
			}
		}
		
	}
	else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
	
}
static error_t LCD_SendFallingEndgPulse(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		GPIO_SetPinValue(pLcdConfig->kLcdControlPort, pLcdConfig->kEN_PinNum, kHigh );
		Delay_ms(1);
		GPIO_SetPinValue(pLcdConfig->kLcdControlPort, pLcdConfig->kEN_PinNum, kLow );
		Delay_ms(1);

	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;

}
error_t LCD_ClearScreen(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendCommand(pLcdConfig, LCD_CLEAR_SCREEN);
		Delay_ms(1);

	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}

error_t LCD_SendChar(lcd_t *pLcdConfig, char character)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendData(pLcdConfig, character);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}

error_t LCD_SendString(lcd_t *pLcdConfig, char str[])
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		uint8_t iterator1 =  0;
		while (str[iterator1]!= '\0')
		{
			LCD_SendData(pLcdConfig, str[iterator1++]);
		}
		
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}

error_t LCD_SetPosition(lcd_t *pLcdConfig, uint8_t kRowNum, uint8_t kColumnNum)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		uint8_t command;
		/* if the user enter invalid location AC will point to
			the first place in DDRAM (0, 0 )  */
		if (kRowNum>LCD_ROW_2 || kRowNum<LCD_ROW_1||
										kColumnNum>LCD_COL_16 || kColumnNum<LCD_COL_1)
		{
			command =  LCD_DDRAM_START;
		}
		else if (kRowNum == LCD_ROW_1 )
		{
			command = LCD_DDRAM_START + kColumnNum -1;
		}
		else if (kRowNum == LCD_ROW_2 )
		{
			command = LCD_DDRAM_START + 64 +  kColumnNum -1;
		}
		LCD_SendCommand(pLcdConfig, command);
		Delay_ms(1);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}
error_t LCD_SendNumber(lcd_t *pLcdConfig, sint16 number)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
	
		sint16 Loc_Temp = number;
		uint8_t iterator1 = 0;
		uint8_t iterator2 = 0;
		uint8_t negativeFlag = 0;
		char numArr[5] = {0};
		/* Store Number in numArr as a string
			but the number will be stored in reverse order in the array
				so we need to reverse this array again
		 */
		if (number==0)
		{
			LCD_SendChar(pLcdConfig, '0');

		}
		if (number<0)
		{
			number = number * (-1);
			negativeFlag = 1;
		}
		while (number != 0 )
		{
			Loc_Temp = number % 10;
			numArr[iterator1++] = ( Loc_Temp + '0' );
			number = number / 10;
		}
		/* Revers numArr */
		for (iterator2 = 0; iterator2 < iterator1/2; iterator2++)
		{
			char temp = numArr[iterator2];
			numArr[iterator2 ] = numArr[iterator1-iterator2-1];
			numArr[iterator1-iterator2-1] = temp;
		}

		for (iterator2 = 0; iterator2 < iterator1; iterator2++ )
		{
			if (negativeFlag)
			{
				LCD_SendChar(pLcdConfig, '-');
				negativeFlag = 0;
			}
			LCD_SendChar(pLcdConfig, numArr[iterator2]);
		}
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}
error_t LCD_SendFloat(lcd_t *pLcdConfig, f32_t number)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		uint16 Real_Part = (uint16)number;
		uint16 Fraction_Part = (uint16) ( (number - Real_Part)*100);
		if (number < 0)
		{
			Fraction_Part *= -1;
			Real_Part *= -1;
			LCD_SendChar(pLcdConfig, '-');
		}
		LCD_SendNumber(pLcdConfig, Real_Part);
		LCD_SendChar(pLcdConfig, '.');
		LCD_SendNumber(pLcdConfig, (uint16)Fraction_Part);
		
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}
error_t LCD_StoreCustomChar(lcd_t *pLcdConfig, char pChar_Arr[],
														uint8_t location)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		uint8_t iterator1;

		/* 1- Make AC point to CGRAM */
		LCD_SendCommand(pLcdConfig, LCD_CGRAM_START + location*8 );

		/* 2- Copy Character from byte 0 to byte 7
		   To CGRAM and it Automatically will be copied to the DDRAM */
		for (iterator1 = 0; iterator1<8; iterator1++)
		{
			LCD_SendData(pLcdConfig, pChar_Arr[iterator1]);
		}

		/* 2- Back To DDRAM */
		LCD_SendCommand(pLcdConfig, LCD_DDRAM_START);
	}
	else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}
error_t LCD_SendCustomChar(lcd_t *pLcdConfig, uint8_t location,
											uint8_t kRowNum, uint8_t kColumnNum)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SetPosition(pLcdConfig, kRowNum, kColumnNum);
		LCD_SendData(pLcdConfig, location);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;

}


error_t LCD_EnableCursor(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendCommand(pLcdConfig, LCD_DISPLAY_ON_CURSOR_ON);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}

error_t LCD_DisableCursor(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendCommand(pLcdConfig, LCD_DISPLAY_ON_CURSOR_OFF);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
	
}

error_t LCD_ShiftRight(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendCommand(pLcdConfig, LCD_SHIFT_RIGHT);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
	
}
error_t LCD_ShiftLeft(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendCommand(pLcdConfig, LCD_SHIFT_LEFT);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}


error_t LCD_Display_On(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendCommand(pLcdConfig, LCD_DISPLAY_ON_CURSOR_OFF);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}
error_t LCD_Display_Off(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendCommand(pLcdConfig, LCD_DISPLAY_OFF_CURSOR_OFF);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}

error_t LCD_Blink_On(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendCommand(pLcdConfig, LCD_BLINK_ON);
		
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
}

error_t LCD_Blink_Off(lcd_t *pLcdConfig)
{
	error_t kErrorState = kNoError;
	if (pLcdConfig != NULL_PTR)
	{
		LCD_SendCommand(pLcdConfig, LCD_BLINK_OFF);
	}else
	{
		kErrorState = kFunctionParameterError;
	}
	return kErrorState;
	
}
