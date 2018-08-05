// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#ifndef _REPORTING_H_
#define _REPORTING_H_

#include <sys/types.h>

void reporting_setup();

// Implementation

uint32_t getClock();

// ==================== module debug (write on serial) ========================================

void reporting_debug_loop();

// Implementation

void reporting_debug_impl_setup();
void reporting_debug_print(const char *);
const char *reporting_debug_readCommand();

#endif // _REPORTING_H_
