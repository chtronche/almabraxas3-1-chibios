// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#include <string.h>

#include "hal.h"

#include "reporting.h"
#include "wiring.h"

static SerialConfig _sdConfig = {
  38400,
  0, 0, 0
};

static THD_WORKING_AREA(waReporting_debug, 128);
static THD_FUNCTION(Reporting_debug, arg) {
  (void)arg;
  for(;;) {
    reporting_debug_loop();
    chThdSleepSeconds(1);
  }
}

void reporting_debug_impl_setup() {
  sdStart(&ALMA_DEBUG_PORT, &_sdConfig);
  chThdCreateStatic(waReporting_debug, sizeof(waReporting_debug), NORMALPRIO, Reporting_debug,
		    NULL);
}

void reporting_debug_print(const char *buffer) {
  sdWrite(&ALMA_DEBUG_PORT, (uint8_t *)buffer, strlen(buffer));
}

