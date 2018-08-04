#include <stdio.h>

#include "powerManager.h"
#include "reporting.h"

extern power_t power;
extern power_t newPower;

static char buffer[256];

extern volatile uint16_t currentReading;

void reporting_debug_loop() {
  sprintf(buffer, "%ld V=%d I=%d %d P=%d MPPT=%d L=%d R=%d %d\n", getClock(), voltage, current,
	  currentReading,
	  powerBudget, mppt_direction, leftPower, rightPower, power);
  reporting_debug_print(buffer);
}
