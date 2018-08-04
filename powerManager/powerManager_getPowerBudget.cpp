#include "powerManager.h"

volatile int8_t mppt_direction = 2; // start by increasing

power_t power = 0;

volatile uint16_t powerBudget = 0; // in PWM units

// aka MPPT

void powerManager_getPowerBudget(uint8_t voltage, uint8_t current) {
  if (voltage < 75) {
    powerBudget = power = 0;
    mppt_direction = 2;
    return;
  }
  if (!powerBudget) {
    powerBudget = mppt_direction = 2;
    power = 0;
    return;
  }
  // if (current < 0.1Amp) {
  //   // Powered by capacitor, we decrease consumption until PV voltage balance capacitor voltage
  //   powerDirection = -2;
  //   return;
  // }

  power_t newPower = voltage * current; // in W / 100
  // 280 mW hysteresis to start reducing power / immediate power increase 
  power_t hysteresis = mppt_direction > 0 ? 280 : 0;
  
  if (newPower + hysteresis < power) mppt_direction = -mppt_direction;
  powerBudget += mppt_direction;
  power = newPower;
}
