#ifndef CALC_H
#define CALC_H

uint8_t IsHigherPriority(uint8_t op);
sint32_t Calculate(uint8_t op, sint8_t operand1, sint8_t operand2);
void CalcConf(keypad_t *pKeypad, lcd_t *pLcd);
void ClearStack(charStack_t *opStack, sint32_tStack_t *numStack);
void Calculator(charStack_t *opStack,
                sint32_tStack_t *numStack, lcd_t *lcd, uint8_t key);
void IsError(lcd_t *lcd, charStack_t *opStack, sint32_tStack_t *numStack);
#endif
