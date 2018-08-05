// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#include "hal.h"

static PWMConfig _pwmConfig = {
  1000000, // 1 MHz base clock
  20000, // 50 Hz periode
  NULL, 
  {
    { PWM_OUTPUT_ACTIVE_HIGH, NULL },
    { PWM_OUTPUT_DISABLED, NULL },
    { PWM_OUTPUT_DISABLED, NULL },
    { PWM_OUTPUT_DISABLED, NULL },
    },
  0,
  0
};

void powerManager_setMotorPower_setup() {
  palSetPadMode(GPIOA, 0, PAL_MODE_ALTERNATE(2)); // TIM5_CH1 is AF2 on PA0
  pwmStart(&PWMD5, &_pwmConfig);
}

void powerManager_setMotorPower(bool left, int16_t power) {
  (void)left;
  pwmEnableChannel(&PWMD5, 0, 590 + power);
}
