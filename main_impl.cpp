// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#include "ch.h"
#include "hal.h"

#include "wiring.h"

void main_impl_setup() {
  halInit();
  chSysInit();
}

void main_impl_loop() {
  // Blinker
  for(;;) {
    palClearPad(ALMA_LED_PORT, ALMA_LED_LINE);
    chThdSleepMilliseconds(1000);
    palSetPad(ALMA_LED_PORT, ALMA_LED_LINE);
    chThdSleepMilliseconds(300);
  }
}
