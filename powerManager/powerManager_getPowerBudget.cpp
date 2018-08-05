#include "powerManager.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

volatile int8_t mppt_direction = 2; // start by increasing

power_t peakPower = 0;

volatile uint16_t powerBudget = 0; // in PWM units

// aka MPPT

#define HYSTERESIS (200) // mW

void powerManager_getPowerBudget(uint8_t voltage, uint8_t current) {
  if (voltage < 75) {
    powerBudget = peakPower = 0;
    mppt_direction = 2;
    return;
  }
  if (!powerBudget) {
    powerBudget = mppt_direction = 2;
    peakPower = 0;
    return;
  }
  // if (current < 0.1Amp) {
  //   // Powered by capacitor, we decrease consumption until PV voltage balance capacitor voltage
  //   powerDirection = -2;
  //   return;
  // }

  power_t power = voltage * current; // in W / 100
  if (mppt_direction > 0) {
    // Climbing
    uint16_t hysteresis = MAX(50, voltage + voltage / 2);
    if (power > peakPower - hysteresis) { // That is 1 reading unit of current (100 mA) 
      if (power > peakPower) peakPower = power;
      // Go on
    } else {
      mppt_direction = -mppt_direction;
      if (peakPower >= 100) 
	peakPower -= 100; // mW
      else
	peakPower = 0;
    }
  } else {
    // Descending
    if (power > peakPower) {
      peakPower = power;
      mppt_direction = -mppt_direction;
    } else {
      if (peakPower >= 100) 
	peakPower -= 100;
      else
	peakPower = 0;
    }
  }
  powerBudget += mppt_direction;
}
