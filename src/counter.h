#ifndef __COUNTER_H__
#define __COUNTER_H__

typedef struct counter {
  unsigned int count;
} counter;

void counter_initialize(counter *e);
void counter_force(counter *e,unsigned int limit);
void counter_tic(counter *e,unsigned int limit);
char counter_check(counter *e,unsigned int limit);

#endif
