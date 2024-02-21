#include "../../../common/Types.h"
#include "../../../common/Utils.h"
#include "../../../common/Config.h"
#include "../../../common/Registes.h"

#define SPECIAL_OUTPUT_PORT (*((volatile char *)0x20))
#define SPECIAL_INPUT_PORT  (*((volatile char *)0x22))

void print_str(const char *str)
{
    const char *c;
    for (c = str; *c != NULL ; c++)
    {
        SPECIAL_OUTPUT_PORT = *c;
    }
}

void print_num(int num)
{
    char str[15];
    int i = 0;
    while (num != 0)
    {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    for (int j = i - 1 ; j >= 0 ; j--)
    {
        SPECIAL_OUTPUT_PORT = str[j];
    }
}

static void SET_BIT_Test(uint8_t* var)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        SET_BIT(*var, i);
    }
}

static void CLR_BIT_Test(uint8_t* var)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        CLR_BIT(*var, i);
    }
}

static void TOG_BIT_Test(uint8_t* var)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        TOG_BIT(*var, i);
    }
}

int main()
{
    uint8_t var = 0b11110000;
    
    SET_BIT_Test(&var);         // Now var = 0b11111111 = 255
    print_str("After 'SET_BIT' var = ");
    print_num(var);
    print_str("\n");
    
    CLR_BIT_Test(&var);         // Now var = 0b11110000 = 240
    print_str("After 'CLR_BIT' var = ");
    print_num(var);
    print_str("\n");
    
    TOG_BIT_Test(&var);         // Now var = 0b00001111 = 15
    print_str("After 'TOG_BIT' var = ");
    print_num(var);
    print_str("\n");

}
