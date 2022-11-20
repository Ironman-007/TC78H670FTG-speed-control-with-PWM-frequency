#pragma once

#include <Arduino.h>

//  Setting options for controlMode
#define PRODRIVER_MODE_CLOCKIN          0 
#define PRODRIVER_MODE_SERIAL           1

#define PWM_RESOLUTION                 13

#define SERIAL_MODE                     0

// variable mode
#define STEP_RESOLUTION_VARIABLE_1_2    1
#define STEP_RESOLUTION_VARIABLE_1_4    2
#define STEP_RESOLUTION_VARIABLE_1_8    3
#define STEP_RESOLUTION_VARIABLE_1_16   4
#define STEP_RESOLUTION_VARIABLE_1_32   5
#define STEP_RESOLUTION_VARIABLE_1_64   6
#define STEP_RESOLUTION_VARIABLE_1_128  7
// fixed mode
#define STEP_RESOLUTION_FIXED_FULL      8
#define STEP_RESOLUTION_FIXED_1_2       9
#define STEP_RESOLUTION_FIXED_1_4      10
#define STEP_RESOLUTION_FIXED_1_8      11
#define STEP_RESOLUTION_FIXED_1_16     12 // Default mode
#define STEP_RESOLUTION_FIXED_1_32     13
#define STEP_RESOLUTION_FIXED_1_64     14
#define STEP_RESOLUTION_FIXED_1_128    15

#define SPEED_1_1   PWM_PRESCALER_PRESCALER_DIV_1
#define SPEED_1_2   PWM_PRESCALER_PRESCALER_DIV_2
#define SPEED_1_4   PWM_PRESCALER_PRESCALER_DIV_4

class TC78H670 {
private:
    uint32_t MODE_0_pin;
    uint32_t MODE_1_pin;
    uint32_t MODE_2_pin; // CLK
    uint32_t MODE_3_pin; // CW-CCW
    uint32_t STBY_pin;
    uint32_t EN_pin;
    uint32_t ERR_pin;

    HardwarePWM* _hwpwm;

public:
    // constructors:
    TC78H670(uint32_t MODE_0_pin, uint32_t MODE_1_pin,
             uint32_t MODE_2_pin, uint32_t MODE_3_pin,
             uint32_t STBY_pin,   uint32_t EN_pin,
             uint32_t ERR_pin,    HardwarePWM* _hwpwm);

    void begin(void);
    void driver_setup(void);
    void enable_driver(void);
    void disable_driver(void);
    void check_pwm(void);
    void set_speed(int8_t speed);
    void set_direction(int8_t direction);
    void run_motor(int8_t speed, uint32_t direction = 1);
    void set_driver_mode(uint8_t step_mode = STEP_RESOLUTION_FIXED_1_16);
};

