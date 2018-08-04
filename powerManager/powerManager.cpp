#include "powerManager.h"

volatile uint8_t voltage; // in V/10
volatile uint8_t current; // in A/10
volatile int16_t leftPower = 0, rightPower = 0;

static int n = 0;

void powerManager_loop(uint8_t v, uint8_t i) {
  voltage = v;
  current = i;
  if (++n < 150) return; // check only every ~1s during debug
  n = 0;
  powerManager_getPowerBudget(v, i);
  int16_t l, r;
  powerManager_dispatchPower(powerBudget, 0, 0, l, r);
  leftPower = l;
  rightPower = r;
  //  powerSetMotor(l, r);
}

void powerManager_setup() {
  powerManager_impl_setup();
}
