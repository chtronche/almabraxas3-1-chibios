// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#include <stdio.h>
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

static char command[64];
static char *commandP;
static bool clearBuffer = true;

const char *reporting_debug_readCommand() {
  if (clearBuffer) {
    commandP = command;
    clearBuffer = false;
  }
  int commandRoomAvailable = 63 - (commandP - command);
  for(;;) {
    
    if (sdGetWouldBlock(&ALMA_DEBUG_PORT)) return NULL;
    if (!commandRoomAvailable) {
      // discard command line too long
      clearBuffer = true;
      return NULL;
    }
    char c = sdGet(&ALMA_DEBUG_PORT);
    if (c == '\r') continue;
    if (c == '\n') {
      *commandP = '\0';
      clearBuffer = true;
      return command;
    }
    *commandP++ = c;
    --commandRoomAvailable;
  }
}
