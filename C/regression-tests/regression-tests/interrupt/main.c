#include "../../../common/Types.h"
#include "../../../common/test.h"
#include "../../../common/Utils.h"
#include "../../../common/Config.h"
#include "../../../common/Registes.h"
#include "../../../mcal/GPIO/GPIOPrivate.h"
#include "../../../mcal/GPIO/GPIO.h"
#include "../../../mcal/GIC/GIC_Interface.h"
#include "../../../mcal/EXTI/EXTI_Interface.h"
int main()
{   print_str("SREG_REG: ");
    print_num(SREG);
    print_str("\n");
    GIC_voidGlobalInterruptControl(GLOBAL_INTERRUPT_ENABLE);
    print_str("SREG_REG: ");
    print_num(SREG);
    print_str("\n");
    GPIO_SetPinDirection(kPORTD, kPIN2, kInput);
    print_str("DDRD_REG: ");
    print_num(DDRD_REG);
    print_str("\n");
    EXTI_InterruptEnable(EXTI_INT0);
    print_str("GICR_REG: ");
    print_num(GICR_REG);
    print_str("\n");
    EXTI_InterruptDisable(EXTI_INT0);
    print_str("GICR_REG: ");
    print_num(GICR_REG);
    print_str("\n");
    EXTI_InterruptEnable(EXTI_INT0);
    print_str("GICR_REG: ");
    print_num(GICR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT0, EXTI_LOW_LEVEL);
    print_str("MCUCR_REG: ");
    print_num(MCUCR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT0, EXTI_ON_CHANGE);
    print_str("MCUCR_REG: ");
    print_num(MCUCR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT0, EXTI_FALLING_EDGE);
    print_str("MCUCR_REG: ");
    print_num(MCUCR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT0, EXTI_RISING_EDGE);
    print_str("MCUCR_REG: ");
    print_num(MCUCR_REG);
    print_str("\n");
    GPIO_SetPinDirection(kPORTD, kPIN3, kInput);
    print_str("DDRD_REG: ");
    print_num(DDRD_REG);
    print_str("\n");
    EXTI_InterruptEnable(EXTI_INT1);
    print_str("GICR_REG: ");
    print_num(GICR_REG);
    print_str("\n");
    EXTI_InterruptDisable(EXTI_INT1);
    print_str("GICR_REG: ");
    print_num(GICR_REG);
    print_str("\n");
    EXTI_InterruptEnable(EXTI_INT1);
    print_str("GICR_REG: ");
    print_num(GICR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT1, EXTI_LOW_LEVEL);
    print_str("MCUCR_REG: ");
    print_num(MCUCR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT1, EXTI_ON_CHANGE);
    print_str("MCUCR_REG: ");
    print_num(MCUCR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT1, EXTI_FALLING_EDGE);
    print_str("MCUCR_REG: ");
    print_num(MCUCR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT1, EXTI_RISING_EDGE);
    print_str("MCUCR_REG: ");
    print_num(MCUCR_REG);
    print_str("\n");
    GPIO_SetPinDirection(kPORTB, kPIN2, kInput);
    print_str("DDRB_REG: ");
    print_num(DDRB_REG);
    print_str("\n");
    EXTI_InterruptEnable(EXTI_INT2);
    print_str("GICR_REG: ");
    print_num(GICR_REG);
    print_str("\n");
    EXTI_InterruptDisable(EXTI_INT2);
    print_str("GICR_REG: ");
    print_num(GICR_REG);
    print_str("\n");
    EXTI_InterruptEnable(EXTI_INT2);
    print_str("GICR_REG: ");
    print_num(GICR_REG);
    print_str("\n");
    print_str("MCUCSR_REG: ");
    print_num(MCUCSR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT2, EXTI_FALLING_EDGE);
    print_str("MCUCSR_REG: ");
    print_num(MCUCSR_REG);
    print_str("\n");
    EXTI_SetSenseControl(EXTI_INT2, EXTI_RISING_EDGE);
    print_str("MCUCSR_REG: ");
    print_num(MCUCSR_REG);
    print_str("\n");
    GIC_voidGlobalInterruptControl(GLOBAL_INTERRUPT_DISABLE);
    print_str("SREG_REG: ");
    print_num(SREG);
    print_str("\n");
}
