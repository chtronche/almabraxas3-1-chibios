#include "main.h"
#include "powerManager.h"
#include "reporting.h"

int main() {
  main_impl_setup();
  reporting_setup();
  powerManager_setup();
  main_impl_loop();
}
