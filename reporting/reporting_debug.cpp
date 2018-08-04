#include <stdio.h>

#include "powerManager.h"
#include "reporting.h"

static char buffer[256];

extern volatile uint16_t currentReading;

void reporting_debug_loop() {
  sprintf(buffer, "%ld V=%d I=%d %d P=%d MPPT=%d\n", getClock(), voltage, current, currentReading,
	  powerBudget, mppt_direction);
  reporting_debug_print(buffer);
}
