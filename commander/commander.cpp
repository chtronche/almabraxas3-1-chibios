#include <stdlib.h>
#include <string.h>

#include "commander.h"
#include "powerManager.h"
#include "reporting.h"

uint32_t badCommand = 0;

static const char *startswith(const char *searched, const char *buffer) {
  for(;;) {
    if (!*searched) return buffer;
    if (!*searched) return buffer;
    if (*searched != *buffer) return NULL;
    ++searched;
    ++buffer;
  }
}

char comment[17];

void processCommand(const char *command) {
  if (!command) return;
  reporting_debug_print(">");
  reporting_debug_print(command);
  reporting_debug_print("\n");

  const char *_next;

  if ((_next = startswith("comment ", command))) {
    strncpy((char *)comment, _next, 16);
    return;
  }

  if ((_next = startswith("reset budget", command))) {
    mpptOn = true;
  }

  if ((_next = startswith("set budget ", command))) {
    mpptOn = false;
    powerBudget = atoi(_next);
    return;
  }

  ++badCommand;
}

void commander_setup() {
  strcpy((char *)comment, "--");
  ((char *)comment)[16] = '\0';
}
