#include <Arduino.h>
#include "TC78H670FTG.h"

// #ifdef __cplusplus
// extern "C"
// {
// #endif // __cplusplus

TC78H670::TC78H670(uint32_t MODE_0_pin, uint32_t MODE_1_pin,
                   uint32_t MODE_2_pin, uint32_t MODE_3_pin,
                   uint32_t STBY_pin,   uint32_t EN_pin,
                   uint32_t ERR_pin,    HardwarePWM* _hwpwm)
{
    this-> MODE_0_pin = MODE_0_pin;
    this-> MODE_1_pin = MODE_1_pin;
    this-> MODE_2_pin = MODE_2_pin;
    this-> MODE_3_pin = MODE_3_pin;
    this-> STBY_pin   = STBY_pin;
    this-> EN_pin     = EN_pin;
    this-> ERR_pin    = ERR_pin;
    this-> _hwpwm     = _hwpwm;

    pinMode(this-> MODE_0_pin, OUTPUT);
    pinMode(this-> MODE_1_pin, OUTPUT);
    pinMode(this-> MODE_2_pin, OUTPUT);
    pinMode(this-> MODE_3_pin, OUTPUT);
    pinMode(this-> STBY_pin, OUTPUT);
    pinMode(this-> EN_pin, OUTPUT);

    pinMode(this-> ERR_pin, INPUT);
}

void TC78H670::begin(void) {
    this-> _hwpwm->addPin(this-> MODE_2_pin);
    this-> _hwpwm->begin();
    this-> _hwpwm->setResolution(PWM_RESOLUTION);
    // this-> _hwpwm->setMaxValue(10000);
    this-> _hwpwm->setClockDiv(PWM_PRESCALER_PRESCALER_DIV_1); // freq = 16Mhz
}

void TC78H670::driver_setup(void) {
    digitalWrite(this-> MODE_0_pin, LOW);
    digitalWrite(this-> MODE_1_pin, LOW);
    digitalWrite(this-> MODE_2_pin, LOW);
    digitalWrite(this-> MODE_3_pin, LOW);
    digitalWrite(this-> STBY_pin,   LOW);
    digitalWrite(this-> EN_pin,     LOW);
}

/*
Set the step mode.
Default mode is fixed-step 1/16 micro stepping (STEP_RESOLUTION_FIXED_1_16).
*/
void TC78H670::set_driver_mode(uint8_t step_mode) {
    digitalWrite(this-> MODE_0_pin, (step_mode & 0x01));
    digitalWrite(this-> MODE_1_pin, (step_mode & 0x02));
    digitalWrite(this-> MODE_2_pin, (step_mode & 0x04));
    digitalWrite(this-> MODE_3_pin, (step_mode & 0x08));

    delay(10);
    digitalWrite(this-> STBY_pin, HIGH);
    delay(10);
}

void TC78H670::set_speed(int8_t speed) {
    this-> _hwpwm->setClockDiv(speed); // freq = 16Mhz
}
void TC78H670::set_direction(int8_t direction) {
    digitalWrite(this-> MODE_3_pin, direction);
}

void TC78H670::run_motor(int8_t speed, uint32_t direction) {
    digitalWrite(this-> MODE_3_pin, direction);
    this-> _hwpwm->setClockDiv(speed); // freq = 16Mhz

    this-> _hwpwm->writePin(this-> MODE_2_pin, pow(2, PWM_RESOLUTION-1)-1, false);
}

void TC78H670::enable_driver(void) {
    driver_setup();
    set_driver_mode(STEP_RESOLUTION_FIXED_1_16);
    begin();
    digitalWrite(this-> EN_pin, HIGH);
}

void TC78H670::disable_driver(void) {
    digitalWrite(this-> EN_pin, LOW);
    digitalWrite(this-> STBY_pin, LOW);
    this-> _hwpwm->stop();
}

void TC78H670::check_pwm(void) {
    Serial.println(this-> _hwpwm->enabled());
}

// #ifdef __cplusplus
// }
// #endif


