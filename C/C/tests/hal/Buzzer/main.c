#include <util/delay.h>
#include "common/Types.h"
#include "common/Utils.h"
#include "hal/Buzzer/Buzzer.h"

void TEST_buzzerActiveHigh(Buzzer_t *pBuzzer);
void TEST_buzzerActiveLow(Buzzer_t *pBuzzer);

int main()
{
  Buzzer_t buzzer1 =  {kPORTD, kPIN0, kBuzzerActiveHigh};
  Buzzer_t buzzer2 = {kPORTD, kPIN1, kBuzzerActiveLow};

  Buzzer_Init(&buzzer1);
  Buzzer_Init(&buzzer2);
  while (1)
  {
    TEST_buzzerActiveHigh(&buzzer1);
    Delay_ms(1000);
    TEST_buzzerActiveLow(&buzzer2);
  }
}
void TEST_buzzerActiveHigh(Buzzer_t *pBuzzer)
{
  Buzzer_TurnOn(pBuzzer);
  Delay_ms(1000);
  Buzzer_TurnOff(pBuzzer);
  Delay_ms(1000);
}
void TEST_buzzerActiveLow(Buzzer_t *pBuzzer)
{
  Buzzer_TurnOn(pBuzzer);
  Delay_ms(1000);
  Buzzer_TurnOff(pBuzzer);
  Delay_ms(5000);
}
/*
#include <util/delay.h>
#include "common/Types.h"
#include "common/Utils.h"
int main()
{
  while (1)
  {

  }
} */
