// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#include "ch.h"

uint32_t getClock() {
  return ST2S(chVTGetSystemTimeX());
}
