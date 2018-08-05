// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#include "main.h"
#include "powerManager.h"
#include "reporting.h"

int main() {
  main_impl_setup();
  reporting_setup();
  powerManager_setup();
  main_impl_loop();
}
