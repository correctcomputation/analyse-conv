







#include <stdio.h>
#include <stdlib.h>
#include "health.h"

void addList(_Ptr<struct List> list, _Ptr<struct Patient> patient) {
  _Ptr<struct List> b = ((void*)0);

  while (list != ((void*)0)) {
    b = list;
    list = list->forward; }

  list = calloc<struct List>(1, sizeof(struct List));
  list->patient = patient;
  list->forward = ((void*)0);
  list->back = b;
  b->forward = list;
}

void removeList(_Ptr<struct List> list, _Ptr<struct Patient> patient) {
  _Ptr<struct List> l1 = ((void*)0);
  _Ptr<struct List> l2 = ((void*)0);
  _Ptr<struct Patient> p = list->patient;

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

