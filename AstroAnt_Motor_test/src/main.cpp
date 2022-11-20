#include <Arduino.h>
#include <Adafruit_TinyUSB.h> // for Serial

#include "TC78H670FTG.h"

#define Serial_debug 0

TC78H670 motor_L(10, 11, 12, 13, 5, 9, 6, &HwPWM0);
// TC78H670 motor_R;

/**************************************************************************/
/*!
    @brief  The setup function runs once when reset the board
*/
/**************************************************************************/
void setup()
{
  Serial.begin(115200);
  while (!Serial) delay(10);

  motor_L.driver_setup();
  motor_L.set_driver_mode(STEP_RESOLUTION_FIXED_1_16);
  motor_L.begin();
}

/**************************************************************************/
/*!
    @brief  The loop function runs over and over again forever
*/
/**************************************************************************/
void loop()
{
  Serial.println("run motor");
  motor_L.enable_driver();
  motor_L.run_motor(SPEED_1_1);
  delay(2000);
  motor_L.set_direction(0);
  delay(2000);
  motor_L.run_motor(SPEED_1_2);
  delay(2000);
  motor_L.set_direction(0);
  delay(2000);
  motor_L.disable_driver();
  delay(2000);
}




