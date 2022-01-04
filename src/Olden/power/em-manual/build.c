











#include <stdlib.h>
#include "power.h"

#pragma CHECKED_SCOPE ON

Root build_tree(void)
{
  int i;
  Root t = 0;
  Lateral l = 0;

  t = calloc<struct root>(1, sizeof(*t));

  for (i=0; i<11; i++) {

    l = build_lateral(i*21,21);
    t->feeders[i]=l;
  }
  t->theta_R = 0.8;
  t->theta_I = 0.16;
  return t;
}

Lateral build_lateral(int i, int num)
{
  Lateral l = 0;
  Branch b = 0;
  Lateral next = 0;

  if (num == 0) return ((void*)0);
  l = calloc<struct lateral>(1, sizeof(*l));

  next = build_lateral(i,num-1);
  b = build_branch(i*6,(num-1)*6,
    6);

  l->next_lateral = next;
  l->branch = b;
  l->R = 1/300000.0;
  l->X = 0.000001;
  l->alpha = 0.0;
  l->beta = 0.0;
  return l;
}

Branch build_branch(int i, int j, int num)
{
  Leaf l = 0;
  Branch b = 0;

  if (num == 0) return ((void*)0);

  b = calloc<struct branch>(1, sizeof(*b));


  b->next_branch= build_branch(i,j,num-1);

  for (i=0; i<12; i++) {
    l = build_leaf();
    b->leaves[i] = l;
  }


  b->R = 0.0001;
  b->X = 0.00002;
  b->alpha = 0.0;
  b->beta = 0.0;
  return b;
}

Leaf build_leaf(void) {
  Leaf l = 0;

  l = calloc<struct leaf>(1, sizeof(*l));
  l->D.P = 1.0;
  l->D.Q = 1.0;
  return l;
}
