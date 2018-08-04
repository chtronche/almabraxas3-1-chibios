#ifndef _POWER_MANAGER_H_
#define _POWER_MANAGER_H_

#include <sys/types.h>

extern volatile uint8_t voltage; // in V/10
extern volatile uint8_t current; // in A/10
extern volatile int8_t mppt_direction; // +2 if increasing, -2 if decreasing
extern volatile uint16_t powerBudget;
extern volatile int16_t leftPower, rightPower;

void powerManager_setup();
void powerManager_loop(uint8_t v, uint8_t i);

// Implementation

void powerManager_impl_setup();

// ==================== module getPowerBudget ========================================

void powerManager_getPowerBudget(uint8_t v, uint8_t i);

// ==================== module dispatchPower =========================================

void powerManager_dispatchPower(
    uint16_t powerBudget, uint8_t heading, uint8_t targetHeading, 
    int16_t &leftPower, int16_t &rightPower);

// ==================== module motorControl ==========================================

void powerManager_setMotorPower(int16_t leftPower, int16_t rightPower);

// Implementation

void setPower(bool left, int16_t power);

#endif // _POWER_MANAGER_H_
