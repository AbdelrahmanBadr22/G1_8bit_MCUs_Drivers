#include <util/delay.h>
#include "common/Types.h"
#include "common/Utils.h"
#include "common/Config.h"
#include "mcal/GIC/GIC_Interface.h"
#include "mcal/ADC/ADC_interface.h"
#include "hal/LCD/LCD_Interface.h"
int main()
{
  lcd_t lcd = {LCD_4Bit, kPORTC, kPORTA, kPIN0, kPIN1, kPIN2, LCD_HIGH_NIBBLE};
  uint16 digitalValue = 0;
  uint16 analogValue = 0;
  LCD_Init(&lcd);
  ADC_Init();
  ADC_INTERRUPT_ENABLE();
  ADC_ENABLE();
  GIC_voidGlobalInterruptControl(GLOBAL_INTERRUPT_ENABLE);
  while (1)
  {
    ADC_GetResultSynch(ADC_CHANNEL4, &digitalValue);
    analogValue = (digitalValue * 5000LU) / (1024);
    LCD_SendNumber(&lcd, analogValue);
    _delay_ms(100);
    LCD_ClearScreen(&lcd);
  }
}
