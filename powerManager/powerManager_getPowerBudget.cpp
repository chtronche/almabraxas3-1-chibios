#include "powerManager.h"

volatile int8_t mppt_direction = 2; // start by increasing

typedef uint16_t power_t; // 255 W max, use uint16_t if more

static power_t power = 0;

volatile uint16_t powerBudget = 0; // in PWM units

void powerManager_getPowerBudget(uint8_t voltage, uint8_t current) {
  if (voltage < 75) {
    power = powerBudget = 0;
    mppt_direction = 2;
    return;
  }

  // if (current < 0.1Amp) {
  //   // Powered by capacitor, we decrease consumption until PV voltage balance capacitor voltage
  //   powerDirection = -2;
  //   return;
  // }

  power_t newPower = voltage * current; // in W / 100
  // 200 mW hysteresis
  if (newPower + 1 < power) mppt_direction = -mppt_direction;
  powerBudget += mppt_direction;
  power = newPower;
}
