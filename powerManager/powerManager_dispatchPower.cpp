#include "powerManager.h"

void powerManager_dispatchPower(
    uint16_t powerBudget, uint8_t heading, uint8_t targetHeading, 
    int16_t &leftPower, int16_t &rightPower) {
  (void)heading;
  (void)targetHeading;
  leftPower = powerBudget;
  rightPower = 0;
}
