






#include <stdio.h>
#include <stdlib.h>
#include "health.h"

void addList(struct List *list, struct Patient *patient) {
  struct List *b;

  while (list != ((void*)0)) {
    b = list;
    list = list->forward; }

  list = (struct List *)malloc(sizeof(struct List));
  list->patient = patient;
  list->forward = ((void*)0);
  list->back = b;
  b->forward = list;
}

void removeList(struct List *list, struct Patient *patient) {
  struct List *l1;
  struct List *l2;
  struct Patient *p;

  p = list->patient;
  while(p != patient) {
      list = list->forward;
      p = list->patient;
  }

  l1 = list->back;
  l2 = list->forward;
  l1->forward = l2;
  if (list->forward != ((void*)0)) {
    l1 = list->forward;
    l2 = list->back;
    l1->back = l2;
  }

}

