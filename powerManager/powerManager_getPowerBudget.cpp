// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#include "powerManager.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

volatile int8_t mppt_direction = 2; // start by increasing

power_t peakPower = 0;

volatile uint16_t powerBudget = 0; // in PWM units

bool mpptOn = true;

static void decreasePeakPower() {
  if (peakPower >= 100) 
    peakPower -= 100; // = 1 W
  else
    peakPower = 0;
}

// aka MPPT

void powerManager_getPowerBudget(uint8_t voltage, uint8_t current) {
  if (!mpptOn) return;
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
      decreasePeakPower();
    }
  } else {
    // Descending
    if (power > peakPower) {
      peakPower = power;
      mppt_direction = -mppt_direction;
    } else {
      decreasePeakPower();
    }
  }
  powerBudget += mppt_direction;
}
