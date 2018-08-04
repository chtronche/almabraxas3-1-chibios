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

#endif // _REPORTING_H_
