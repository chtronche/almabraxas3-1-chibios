#include "reporting.h"

#include <string.h>

#include "commander.h"

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

  ++badCommand;
}

void commander_setup() {
  strcpy((char *)comment, "--");
  ((char *)comment)[16] = '\0';
}
