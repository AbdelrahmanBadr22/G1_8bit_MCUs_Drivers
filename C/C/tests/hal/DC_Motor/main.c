#include <util/delay.h>
#include "common/Types.h"
#include "common/Utils.h"
#include "hal/DC_Motor/DC_Motor.h"
int main(void)
{

  DcMotor_t dcMotor={kPORTA, kPIN0, kPIN1};
  DcMotor_Init(&dcMotor);
  while (1)
  {
      DcMotor_ClockWise(&dcMotor);
      Delay_ms(2000);
      DcMotor_Stop(&dcMotor);
      Delay_ms(500);
      DcMotor_AntiClockWise(&dcMotor);
      Delay_ms(2000);
      DcMotor_Stop(&dcMotor);
      Delay_ms(500);
  }
}
