// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#include "powerManager.h"

void powerManager_dispatchPower(
    uint16_t powerBudget, uint8_t heading, uint8_t targetHeading, 
    int16_t &leftPower, int16_t &rightPower) {
  (void)heading;
  (void)targetHeading;
  leftPower = powerBudget;
  rightPower = 0;
}
