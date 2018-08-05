// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#include <stdio.h>

#include "powerManager.h"
#include "reporting.h"

extern power_t peakPower;

static char buffer[256];

extern volatile uint16_t currentReading;

void reporting_debug_loop() {
  sprintf(buffer, "%ld V=%d I=%d %d P=%d MPPT=%d L=%d R=%d %d %d\n", getClock(), voltage, current,
	  currentReading,
	  powerBudget, mppt_direction, leftPower, rightPower, voltage * current, peakPower);
  reporting_debug_print(buffer);
}
