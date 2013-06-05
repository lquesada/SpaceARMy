#include "counter.h"

void counter_initialize(counter *e) {
  e->count = 0;
}
char counter_check(counter *e,unsigned int limit) {
  e->count++;
  if (e->count > limit) {
    e->count = 0;
    return 1;
  }
  return 0;
}

void counter_tic(counter *e,unsigned int limit) {
  if (e->count <= limit)
    e->count++;
}

void counter_force(counter *e,unsigned int limit) {
  e->count = limit+1;
}



