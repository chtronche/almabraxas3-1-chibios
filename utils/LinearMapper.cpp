#include "LinearMapper.h"

LinearMapper::LinearMapper(int from0, float to0, int from1, float to1) {
  a = (to1 - to0) / (from1 - from0);
  b = to0 - a * from0;
}
