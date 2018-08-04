#include "ch.h"

uint32_t getClock() {
  return ST2S(chVTGetSystemTimeX());
}
