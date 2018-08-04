#include <stdio.h>

#include "powerManager.h"
#include "reporting.h"

static char buffer[256];

extern volatile uint16_t currentReading;

void reporting_debug_loop() {
  sprintf(buffer, "%ld V=%d I=%d P=%d MPPT=%d L=%d R=%d\n", getClock(), voltage, current,
	  powerBudget, mppt_direction, leftPower, rightPower);
  reporting_debug_print(buffer);
}
